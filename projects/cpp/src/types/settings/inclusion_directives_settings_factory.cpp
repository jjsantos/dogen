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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/inclusion_directives_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.settings.inclusion_directives_settings_factory"));

const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace cpp {
namespace settings {

inclusion_directives_settings_factory::
inclusion_directives_settings_factory(const dynamic::repository& rp,
    const formatters::container& fc)
    : field_definitions_(make_field_definitions(rp, fc)),
      inclusion_required_(get_top_level_inclusion_required_field(rp)) {}

inclusion_directives_settings_factory::field_definitions
inclusion_directives_settings_factory::make_field_definitions(
    const dynamic::repository& rp, const std::string& formatter_name) const {

    field_definitions r;
    const dynamic::repository_selector s(rp);
    const auto& id(traits::inclusion_directive());
    r.inclusion_directive = s.select_field_by_name(formatter_name, id);

    const auto& ir(traits::inclusion_required());
    r.inclusion_required = s.select_field_by_name(formatter_name, ir);

    return r;
}

std::unordered_map<
    std::string,
    inclusion_directives_settings_factory::field_definitions
    >
inclusion_directives_settings_factory::
make_field_definitions(const dynamic::repository& rp,
    const formatters::container& fc) const {
    std::unordered_map<std::string, field_definitions> r;

    for (const auto f : fc.all_external_formatters()) {
        const auto& oh(f->ownership_hierarchy());
        const auto fn(oh.formatter_name());

        if (fn.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }

        if (f->file_type() != formatters::file_types::cpp_header) {
            BOOST_LOG_SEV(lg, debug) << "Skipping formatter: " << fn;
            continue;
        }

        r[oh.formatter_name()] = make_field_definitions(rp, fn);
    }
    return r;
}

dynamic::field_definition inclusion_directives_settings_factory::
get_top_level_inclusion_required_field(
    const dynamic::repository& rp) const {
    const dynamic::repository_selector s(rp);
    return s.select_field_by_name(traits::cpp::inclusion_required());
}

boost::optional<std::string> inclusion_directives_settings_factory::
obtain_inclusion_directive_for_formatter(const field_definitions& fd,
    const dynamic::object& o) const {
    boost::optional<std::string> r;

    using namespace dynamic;
    const field_selector fs(o);
    if (!fs.has_field(fd.inclusion_directive))
        return r;

    r = fs.get_text_content(fd.inclusion_directive);
    return r;
}

bool inclusion_directives_settings_factory::
obtain_inclusion_required_for_formatter(const field_definitions& fd,
    const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    const auto r(fs.get_boolean_content_or_default(fd.inclusion_required));
    return r;
}

bool inclusion_directives_settings_factory::
obtain_top_level_inclusion_required(const dynamic::object& o) const {
    using namespace dynamic;
    const field_selector fs(o);
    return fs.get_boolean_content_or_default(inclusion_required_);
}

inclusion_directives_settings inclusion_directives_settings_factory::make(
    const dynamic::object& o) const {

    inclusion_directives_settings r;
    const auto ir(obtain_top_level_inclusion_required(o));
    r.inclusion_required(ir);

    for (const auto& pair : field_definitions_) {
        const auto& fn(pair.first);
        const auto& fd(pair.second);
        const auto id(obtain_inclusion_directive_for_formatter(fd, o));

        inclusion_directive_settings st;
        st.inclusion_directive(id);

        const auto fir(obtain_inclusion_required_for_formatter(fd, o));
        st.inclusion_required(fir);
        const auto id_pair(std::make_pair(fn, st));
        r.inclusion_directive_settings().insert(id_pair);
    }
    return r;
}

} } }
