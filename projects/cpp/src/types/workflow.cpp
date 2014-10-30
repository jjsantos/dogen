/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formatter_dispatcher.hpp"
#include "dogen/cpp/types/workflow.hpp"

namespace {

const std::string id("cpp.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace cpp {

std::shared_ptr<cpp::registrar> workflow::registrar_;

workflow::~workflow() noexcept { }

cpp::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::registrar>();

    return *registrar_;
}

void workflow::register_formatter(
    std::shared_ptr<formatters::class_formatter_interface> f) {
    registrar().register_formatter(f);
}

std::list<dogen::formatters::file> workflow::generate_entity_activity(
    const settings_bundle& s, const entity& e) const {
    formatter_dispatcher d(*registrar_, s);
    return d.format(e);
}

std::string workflow::id() const {
    return ::id;
}

std::vector<boost::filesystem::path> workflow::managed_directories() const {
    std::vector<boost::filesystem::path> r;
    return r;
}

void workflow::validate() const {
    BOOST_LOG_SEV(lg, debug) << "Validating c++ backend workflow.";

    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Found "
                             << registrar().class_formatters().size()
                             << " registered class formatter(s): ";

    BOOST_LOG_SEV(lg, debug) << "Listing all class formatter.";
    for (const auto& f : registrar().class_formatters())
        BOOST_LOG_SEV(lg, debug) << "Id: '" << f->formatter_id() << "'";

    BOOST_LOG_SEV(lg, debug) << "Finished validating c++ backend workflow.";
}

std::list<dogen::formatters::file> workflow::generate(
    const dogen::formatters::general_settings& /*gs*/,
    const sml::model& /*m*/) const {
    BOOST_LOG_SEV(lg, debug) << "Started C++ backend.";
    settings_bundle b;

    /*
    const auto entities(transform_sml_elements_activity(m, m.modules()));
    const auto files(generate_entity_activity(b));
    */

    std::list<dogen::formatters::file> r;
    BOOST_LOG_SEV(lg, debug) << "Finished C++ backend.";
    return r;
}

} }
