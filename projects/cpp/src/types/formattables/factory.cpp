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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/settings/aspect_settings_factory.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/odb/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/name_builder.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_factory.hpp"
#include "dogen/cpp/types/formattables/factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formatters.factory"));

const std::string namespace_separator("::");
const std::string registrar_name("registrar");
const std::string includers_name("all");
const std::string cmakelists_name("CMakeLists.txt");
const std::string odb_options_name("options.odb");
const std::string settings_not_found_for_formatter(
    "Settings not found for formatter: ");
const std::string bundle_not_found_for_qname(
    "Settings bundle not found for qname: ");
const std::string derivatives_not_found_for_formatter(
    "Path derivatives not found for formatter: ");
const std::string properties_not_found(
    "Formatter properties not found for: ");
const std::string empty_formatter_name("Formatter name is empty.");
const std::string cmake_modeline_name("cmake");
const std::string odb_modeline_name("odb");
const std::string cpp_modeline_name("cpp");

}

namespace dogen {
namespace cpp {
namespace formattables {

std::unordered_map<std::string, settings::path_settings>
factory::clone_path_settings(
    const std::unordered_map<std::string, settings::path_settings>& source,
    const std::string& source_formatter_name,
    const std::string& destination_formatter_name) const {

    const auto i(source.find(source_formatter_name));
    if (i == source.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << source_formatter_name;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + source_formatter_name));
    }

    std::unordered_map<std::string, settings::path_settings> r;
    r.insert(std::make_pair(destination_formatter_name, i->second));
    return r;
}

sml::qname factory::create_qname(const sml::model& m,
    const std::string& simple_name) const {

    sml::qname r;
    r.simple_name(simple_name);
    r.model_name(m.name().model_name());
    r.external_module_path(m.name().external_module_path());
    return r;
}

path_derivatives factory::create_path_derivatives(
    const config::cpp_options& opts, const sml::model& m,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const sml::qname& qn,
    const std::string& formatter_name) const {

    path_derivatives_factory pdf(opts, m, ps);
    const auto pd(pdf.make(qn));
    const auto i(pd.find(formatter_name));
    if (i == pd.end()) {
        BOOST_LOG_SEV(lg, error) << derivatives_not_found_for_formatter
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(building_error(
                derivatives_not_found_for_formatter + formatter_name));
    }
    return i->second;
}

bool factory::is_enabled(const formatter_properties_repository& fprp,
    const sml::qname& qn, const std::string& formatter_name) const {

    const auto i(fprp.formatter_properties_by_qname().find(qn));
    if (i == fprp.formatter_properties_by_qname().end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << properties_not_found << n;
        BOOST_THROW_EXCEPTION(building_error(properties_not_found + n));
    }

    const auto j(i->second.find(formatter_name));
    if (j == i->second.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + formatter_name));
    }
    return j->second.enabled();
}

std::shared_ptr<formattable> factory::make_registrar_info(
    const config::cpp_options& opts,
    const dynamic::repository& /*drp*/,
    const dynamic::object& /*root_object*/,
    const dogen::formatters::general_settings_factory& /*gsf*/,
    const settings::bundle_repository& brp,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formatter_properties_repository& fprp,
    const sml::model& m) const {

    const auto qn(create_qname(m, registrar_name));
    BOOST_LOG_SEV(lg, debug) << "Making registrar: "
                             << sml::string_converter::convert(qn);

    name_builder b;
    auto r(std::make_shared<registrar_info>());
    r->namespaces(b.namespace_list(m, qn));

    /*
    const auto gs(gsf.make(cpp_modeline_name, root_object));
    settings::bundle sb;
    sb.general_settings(gs);
    settings::aspect_settings_factory f(drp, root_object);
    sb.aspect_settings(f.make());
    r->settings(sb);
    */
    const auto i(brp.bundles_by_qname().find(qn));
    if (i == brp.bundles_by_qname().end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << bundle_not_found_for_qname << n;
        BOOST_THROW_EXCEPTION(building_error(bundle_not_found_for_qname + n));
    }
    r->settings(i->second);

    for (const auto& pair : m.references()) {
        if (pair.second != sml::origin_types::system) {
            const auto l(b.namespace_list(m, pair.first));
            const auto s(boost::algorithm::join(l, namespace_separator));
            r->model_dependencies().push_back(s);
        }
    }

    for (const auto& l : m.leaves())
        r->leaves().push_back(b.qualified_name(m, l));
    r->leaves().sort();

    const auto lambda([&](const std::string& src, const std::string& dst) {
            const auto cloned_ps(clone_path_settings(ps, src, dst));
            const auto pd(create_path_derivatives(opts, m, cloned_ps, qn, dst));

            formatter_properties r;
            r.file_path(pd.file_path());
            r.header_guard(pd.header_guard());
            r.enabled(is_enabled(fprp, m.name(), src));
            return r;
        });

    using formatters::serialization::traits;
    const auto ch_fn(traits::class_header_formatter_name());
    const auto rh_fn(traits::registrar_header_formatter_name());
    const auto fp1(lambda(ch_fn, rh_fn));
    r->formatter_properties().insert(std::make_pair(rh_fn, fp1));

    const auto ci_fn(traits::class_implementation_formatter_name());
    const auto ri_fn(traits::registrar_implementation_formatter_name());
    auto fp2(lambda(ci_fn, ri_fn));

    const auto j(fprp.formatter_properties_by_qname().find(qn));
    if (j == fprp.formatter_properties_by_qname().end()) {
        const auto n(sml::string_converter::convert(qn));
        BOOST_LOG_SEV(lg, error) << properties_not_found << n;
        BOOST_THROW_EXCEPTION(building_error(properties_not_found + n));

    }

    const auto k(j->second.find(ri_fn));
    if (k == j->second.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter << ri_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + ri_fn));
    }
    fp2.inclusion_dependencies(k->second.inclusion_dependencies());

    /*    using ic = formatters::inclusion_constants;
    auto& id(fp2.inclusion_dependencies());

    if (!sb.aspect_settings().disable_xml_serialization()) {
        id.push_back(ic::boost::archive::xml_iarchive());
        id.push_back(ic::boost::archive::xml_oarchive());
    }

    id.push_back(ic::boost::archive::text_iarchive());
    id.push_back(ic::boost::archive::text_oarchive());
    id.push_back(ic::boost::archive::binary_iarchive());
    id.push_back(ic::boost::archive::binary_oarchive());
    id.push_back(ic::boost::archive::polymorphic_iarchive());
    id.push_back(ic::boost::archive::polymorphic_oarchive());

    if (!sb.aspect_settings().disable_eos_serialization()) {
        id.push_back(ic::eos::portable_iarchive());
        id.push_back(ic::eos::portable_oarchive());
        }
    */
    r->formatter_properties().insert(std::make_pair(ri_fn, fp2));

    BOOST_LOG_SEV(lg, debug) << "Made registrar: "
                             << sml::string_converter::convert(qn);
    return r;
}

std::forward_list<std::shared_ptr<formattable> > factory::
make_includers(
    const config::cpp_options& opts,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formattables::path_derivatives_repository& pdrp,
    const std::forward_list<
    std::shared_ptr<formatters::formatter_interface>>& formatters,
    const formatter_properties_repository& fprp,
    const sml::model& m) const {

    const auto qn(create_qname(m, includers_name));
    BOOST_LOG_SEV(lg, debug) << "Making includers: "
                             << sml::string_converter::convert(qn);

    std::unordered_map<std::string, std::list<std::string> >
        includes_by_formatter_name;

    for (const auto& qn_pair : pdrp.path_derivatives_by_qname()) {
        const auto qn(qn_pair.first);

        if (qn.model_name() != m.name().model_name())
            continue;

        for (const auto& fmt_pair : qn_pair.second) {
            const auto fn(fmt_pair.first);
            const auto pd(fmt_pair.second);

            const auto id(pd.inclusion_directive());
            if (id)
                includes_by_formatter_name[fn].push_back(*id);
        }
    }

    std::unordered_map<std::string, std::list<std::string> >
        includes_by_facet_name;
    for(const auto f : formatters) {
        const auto& oh(f->ownership_hierarchy());
        if (oh.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        const auto i(includes_by_formatter_name.find(oh.formatter_name()));
        if (i == includes_by_formatter_name.end())
            continue;

        auto& ifn(includes_by_facet_name[oh.facet_name()]);
        ifn.splice(ifn.begin(), i->second);
    }

    std::forward_list<std::shared_ptr<formattable> > r;
    for(const auto& pair : includes_by_facet_name) {
        const auto& facet_name(pair.first);

        using namespace formatters;
        const auto ch_fn(traits::class_header_formatter_name(facet_name));
        const auto ifn(traits::includers_formatter_name(facet_name));
        const auto cloned_ps(clone_path_settings(ps, ch_fn, ifn));
        const auto pd(create_path_derivatives(opts, m, cloned_ps, qn, ifn));

        formatter_properties p;
        p.file_path(pd.file_path());
        p.header_guard(pd.header_guard());
        p.enabled(is_enabled(fprp, m.name(), ch_fn));

        auto inc(std::make_shared<includers_info>());
        inc->formatter_properties().insert(std::make_pair(ifn, p));
        r.push_front(inc);
    }
    BOOST_LOG_SEV(lg, debug) << "Made includers: "
                             << sml::string_converter::convert(qn);

    return r;
}

std::forward_list<std::shared_ptr<formattable> > factory::
make_cmakelists(const config::cpp_options& opts,
    const dynamic::object& root_object,
    const dogen::formatters::general_settings_factory& gsf,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formatter_properties_repository& fprp,
    const sml::model& m) const
{
    std::forward_list<std::shared_ptr<formattable> > r;
    if (opts.disable_cmakelists()) {
        BOOST_LOG_SEV(lg, info) << "CMakeLists generation disabled.";
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Generating source CMakeLists.";
    auto cm(std::make_shared<cmakelists_info>());
    cm->model_name(m.name().model_name());
    cm->file_name(cmakelists_name);

    const auto gs(gsf.make(cmake_modeline_name, root_object));
    cm->general_settings(gs);

    if (!m.name().external_module_path().empty())
        cm->product_name(m.name().external_module_path().front());

    using namespace formatters::types;
    const auto ch_fn(traits::class_header_formatter_name());
    const auto i(ps.find(ch_fn));
    if (i == ps.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << ch_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + ch_fn));
    }

    if (opts.split_project()) {
        cm->source_file_path(opts.source_directory_path() /
            m.name().model_name() / cmakelists_name);
        cm->include_file_path(opts.include_directory_path() /
            m.name().model_name() / cmakelists_name);
    } else {
        cm->source_file_path(opts.project_directory_path() /
            m.name().model_name() / i->second.source_directory_name() /
            cmakelists_name);
        cm->include_file_path(opts.project_directory_path() /
            m.name().model_name() / cmakelists_name);
    }

    const auto odb_ch_fn(
        formatters::odb::traits::class_header_formatter_name());
    cm->odb_enabled(is_enabled(fprp, m.name(), odb_ch_fn));
    const auto j(ps.find(odb_ch_fn));
    if (j == ps.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << odb_ch_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + odb_ch_fn));
    }
    cm->odb_folder(j->second.facet_directory());

    r.push_front(cm);
    return r;
}

std::shared_ptr<formattable>
factory::make_odb_options(const config::cpp_options& opts,
    const dynamic::object& root_object,
    const dogen::formatters::general_settings_factory& gsf,
    const std::unordered_map<std::string, settings::path_settings>& ps,
    const formatter_properties_repository& fprp,
    const sml::model& m) const {

    using namespace formatters::odb;
    const auto ch_fn(traits::class_header_formatter_name());
    if (!is_enabled(fprp, m.name(), ch_fn)) {
        BOOST_LOG_SEV(lg, info) << "ODB options file generation disabled.";
        return std::shared_ptr<formattable>();
    }

    BOOST_LOG_SEV(lg, debug) << "Generating ODB options.";

    auto r(std::make_shared<odb_options_info>());
    r->file_name(odb_options_name);
    r->model_name(m.name().model_name());

    const auto gs(gsf.make(odb_modeline_name, root_object));
    r->general_settings(gs);

    const auto i(ps.find(ch_fn));
    if (i == ps.end()) {
        BOOST_LOG_SEV(lg, error) << settings_not_found_for_formatter
                                 << ch_fn;
        BOOST_THROW_EXCEPTION(building_error(
                settings_not_found_for_formatter + ch_fn));
    }
    r->odb_folder(i->second.facet_directory());

    boost::filesystem::path fp;
    if (opts.split_project())
        fp = opts.source_directory_path() / m.name().model_name();
    else {
        fp = opts.project_directory_path() / m.name().model_name();
        fp /= i->second.source_directory_name();
    }
    fp /= odb_options_name;
    r->file_path(fp);

    if (!m.name().external_module_path().empty())
        r->product_name(m.name().external_module_path().front());

    return r;
}

} } }
