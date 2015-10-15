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
#include <memory>
#include <algorithm>
#include <forward_list>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/memory_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/yarn/types/all_model_items_traversal.hpp"
#include "dogen/cpp/types/settings/path_settings_factory.hpp"
#include "dogen/cpp/types/formattables/factory.hpp"
#include "dogen/cpp/types/formattables/transformer.hpp"
#include "dogen/cpp/io/formattables/formattable_io.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository_factory.hpp"
#include "dogen/cpp/types/formattables/workflow.hpp"

namespace {

const std::string id("cpp.formattables.workflow");

using namespace dogen::utility::log;
static logger lg(logger_factory(id));

}

namespace dogen {
namespace cpp {
namespace formattables {

namespace {

/**
 * @brief Generates the formattables.
 */
class generator {
public:
    explicit generator(const transformer& t) : transformer_(t) { }

private:
    void add(std::forward_list<std::shared_ptr<formattables::formattable> > f) {
        result_.splice_after(result_.before_begin(), f);
    }

    template<typename Generatable>
    bool ignore(const Generatable& g) const {
        return g.generation_type() == yarn::generation_types::no_generation;
    }

    template<typename Transformable>
    void transform(const Transformable& t) {
        if (!ignore(t))
            add(transformer_.transform(t));
    }

public:
    void operator()(const dogen::yarn::object& o) { transform(o); }
    void operator()(const dogen::yarn::enumeration& e) { transform(e); }
    void operator()(const dogen::yarn::primitive& p) { transform(p); }
    void operator()(const dogen::yarn::module& m) { transform(m); }
    void operator()(const dogen::yarn::concept& c) { transform(c); }

public:
    const std::forward_list<std::shared_ptr<formattables::formattable> >&
    result() { return result_; }

private:
    std::forward_list<std::shared_ptr<formattables::formattable> > result_;
    const transformer& transformer_;
};

}

std::unordered_map<std::string, settings::path_settings>
workflow::create_path_settings_activity(const dynamic::repository& srp,
    const dynamic::object& root_object,
    const formatters::container& fc) const {

    BOOST_LOG_SEV(lg, debug) << "Creating path settings for root object.";
    settings::path_settings_factory f(srp, fc.all_external_formatters());
    const auto r(f.make(root_object));
    BOOST_LOG_SEV(lg, debug) << "Created path settings for root object.";
    return r;
}

path_derivatives_repository workflow::
create_path_derivatives_repository(const config::cpp_options& opts,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const yarn::model& m) const {
    path_derivatives_repository_factory f;
    return f.make(opts, ps, m);
}

formatter_properties_repository workflow::
create_formatter_properties(const dynamic::repository& srp,
    const dynamic::object& root_object,
    const settings::bundle_repository& brp,
    const path_derivatives_repository& pdrp,
    const formatters::container& fc,
    const yarn::model& m) const {

    formatter_properties_repository_factory f;
    return f.make(srp, root_object, brp, pdrp, fc, m);
}

std::forward_list<std::shared_ptr<formattables::formattable> >
workflow::from_transformer_activity(
    const settings::opaque_settings_builder& osb,
    const settings::bundle_repository& brp,
    const formatter_properties_repository& fprp,
    const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming formattables.";

    const transformer t(osb, brp, fprp, m);
    generator g(t);
    all_model_items_traversal(m, g);

    BOOST_LOG_SEV(lg, debug) << "Finished transforming formattables.";
    return g.result();
}

std::forward_list<std::shared_ptr<formattables::formattable> >
workflow::from_factory_activity(const config::cpp_options& opts,
    const dynamic::repository& drp,
    const dynamic::object& root_object,
    const dogen::formatters::general_settings_factory& gsf,
    const settings::bundle_repository& brp,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formattables::path_derivatives_repository& pdrp,
    const formatter_properties_repository& fprp,
    const formatters::container& fc,
    const yarn::model& m) const {

    const auto& formatters(fc.all_formatters());
    std::forward_list<std::shared_ptr<formattables::formattable> > r;
    factory f;
    const auto& ro(root_object);
    const auto ri(f.make_registrar_info(opts, drp, ro, gsf, brp, ps, fprp, m));
    if (ri)
        r.push_front(ri);

    r.splice_after(r.before_begin(),
        f.make_includers(opts, ro, gsf, ps, pdrp, formatters, fprp, m));
    r.splice_after(r.before_begin(),
        f.make_cmakelists(opts, ro, gsf, ps, fprp, m));

    const auto oi(f.make_odb_options(opts, ro, gsf, ps, fprp, m));
    if (oi)
        r.push_front(oi);

    BOOST_LOG_SEV(lg, debug) << "Factory formattables: " << r;
    return r;
}

std::forward_list<std::shared_ptr<formattables::formattable> >
workflow::execute(const config::cpp_options& opts,
    const dynamic::repository& drp,
    const dynamic::object& root_object,
    const dogen::formatters::general_settings_factory& gsf,
    const formatters::container& fc,
    const settings::opaque_settings_builder& osb,
    const settings::bundle_repository& brp,
    const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Started creating formattables.";

    const auto& ro(root_object);
    const auto ps(create_path_settings_activity(drp, ro, fc));
    const auto pdrp(create_path_derivatives_repository(opts, ps, m));
    const auto fprp(create_formatter_properties(drp, ro, brp, pdrp, fc, m));

    auto r(from_transformer_activity(osb, brp, fprp, m));
    r.splice_after(r.before_begin(),
        from_factory_activity(opts, drp, ro, gsf, brp, ps, pdrp, fprp, fc, m));
    BOOST_LOG_SEV(lg, debug) << "Formattables: " << r;

    BOOST_LOG_SEV(lg, debug) << "Finished creating formattables.";

    return r;
}

} } }
