/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/dynamic/types/repository_workflow.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/config/types/knitting_options_validator.hpp"
#include "dogen/config/io/knitting_options_io.hpp"
#include "dogen/knit/types/frontend_to_middle_end_workflow.hpp"
#include "dogen/knit/types/middle_end_to_backend_workflow.hpp"
#include "dogen/backend/types/workflow.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/knit/types/workflow.hpp"

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.workflow"));

const std::string fields_dir("fields");
const std::string incorrect_stdout_config(
    "Configuration for output to stdout is incorrect");
const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace knit {

workflow::workflow(workflow&& rhs)
    : knitting_options_(std::move(rhs.knitting_options_)) { }

workflow::
workflow(const config::knitting_options& o) : knitting_options_(o) {
    config::knitting_options_validator v;
    v.validate(knitting_options_);
}

bool workflow::housekeeping_required() const {
    return knitting_options_.output().delete_extra_files();
}

std::forward_list<dynamic::ownership_hierarchy> workflow::
obtain_ownership_hierarchy_activity() const {
    const auto rg(backend::workflow::registrar());
    std::forward_list<dynamic::ownership_hierarchy> r;
    for (const auto b : rg.backends())
        r.splice_after(r.before_begin(), b->ownership_hierarchy());

    return r;
}

dynamic::repository workflow::setup_dynamic_repository_activity(
    const std::forward_list<dynamic::ownership_hierarchy>& oh) const {
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / fields_dir);
    dynamic::repository_workflow w;
    return w.execute(oh, std::forward_list<boost::filesystem::path> { dir });
}

void workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Workflow started.";
    BOOST_LOG_SEV(lg, debug) << "Knitting options: " << knitting_options_;

    try {
        const auto oh(obtain_ownership_hierarchy_activity());
        const auto rp(setup_dynamic_repository_activity(oh));

        frontend_to_middle_end_workflow fmw(knitting_options_, rp);
        const auto m(fmw.execute());

        if (!m.has_generatable_types()) {
            BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
            return;
        }

        const auto& ko(knitting_options_);
        middle_end_to_backend_workflow mbw(ko, rp, housekeeping_required());
        mbw.execute(m);
    } catch(const dogen::formatters::formatting_error& e) {
        BOOST_THROW_EXCEPTION(workflow_error(e.what()));
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Workflow finished.";
}

} }
