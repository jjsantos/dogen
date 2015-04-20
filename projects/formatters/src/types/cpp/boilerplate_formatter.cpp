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
#include <sstream>
#include <ostream>
#include "dogen/formatters/types/modeline_formatter.hpp"
#include "dogen/formatters/types/comment_formatter.hpp"
#include "dogen/formatters/types/cpp/include_formatter.hpp"
#include "dogen/formatters/types/cpp/header_guard_formatter.hpp"
#include "dogen/formatters/types/cpp/boilerplate_formatter.hpp"

namespace {

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

}

namespace dogen {
namespace formatters {
namespace cpp {

boilerplate_formatter::boilerplate_formatter(
    const bool generate_preamble, const bool generate_header_guards)
    : generate_preamble_(generate_preamble),
      generate_header_guards_(generate_header_guards) { }

void boilerplate_formatter::
add_modeline(std::list<std::string>& content, const modeline& m) const {
    std::ostringstream s;
    modeline_formatter f;
    f.format(s, m);
    content.push_back(s.str());
}

void boilerplate_formatter::
add_marker(std::list<std::string>& content,
    const std::string& marker) const {
    if (marker.empty())
        return;

    content.push_back(marker);
}

void boilerplate_formatter::
add_licence(std::list<std::string>& content, const licence& l) const {
    std::ostringstream s;
    for (const auto h : l.copyright_notices())
        s << h << std::endl;

    const auto notices(s.str());
    if (!notices.empty())
        content.push_back(notices);

    if (!l.text().empty())
        content.push_back(l.text());
}

void boilerplate_formatter::
format_preamble(std::ostream& s, const annotation& a) const {
    if (!generate_preamble_)
        return;

    bool is_top(false);
    const auto top(modeline_locations::top);
    bool has_modeline(a.modeline() != nullptr);
    std::list<std::string> content;
    if (has_modeline) {
        is_top = a.modeline()->location() == top;

        if (is_top)
            add_modeline(content, *a.modeline());
    }

    add_marker(content, a.code_generation_marker());
    if (a.licence())
        add_licence(content, *a.licence());

    if (content.empty())
        return;

    if (has_modeline && is_top && content.size() == 1) {
        comment_formatter cf(
            start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            comment_styles::cpp_style,
            !last_line_is_blank);

        cf.format(s, content, !line_between_blocks);
    } else {
        comment_formatter cf(
            is_top ? start_on_first_line : !start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            comment_styles::c_style,
            last_line_is_blank);

        cf.format(s, content, line_between_blocks);
    }
}

void boilerplate_formatter::format_guards_begin(std::ostream& s,
    const std::string& header_guard) const {
    if (!generate_header_guards_)
        return;

    header_guard_formatter f;
    f.format_begin(s, header_guard);

    if (!header_guard.empty())
        s << std::endl;
}

void boilerplate_formatter::format_guards_end(std::ostream& s,
    const std::string& header_guard) const {
    if (!generate_header_guards_)
        return;

    header_guard_formatter f;
    f.format_end(s, header_guard);
}

void boilerplate_formatter::
format_includes(std::ostream& s, const std::list<std::string>& includes) const {
    include_formatter f;
    f.format(s, includes);
}

void boilerplate_formatter::
format_begin(std::ostream& s, const annotation& a,
    const std::list<std::string>& includes,
    const std::string& header_guard) const {

    format_preamble(s, a);
    format_guards_begin(s, header_guard);
    format_includes(s, includes);
}

void boilerplate_formatter::format_postamble(std::ostream& s,
    const annotation& a) const {
    if (!a.modeline())
        return;

    const auto m(*a.modeline());
    if (m.location() == modeline_locations::bottom) {
        std::list<std::string> content;
        add_modeline(content, m);

        comment_formatter cf(
            !start_on_first_line,
            !use_documentation_tool_markup,
            !documenting_previous_identifier,
            comment_styles::c_style,
            !last_line_is_blank);

        cf.format(s, content);
    }
}

void boilerplate_formatter::
format_end(std::ostream& s, const annotation& a,
    const std::string& header_guard) const {
    format_postamble(s, a);
    format_guards_end(s, header_guard);
}

} } }