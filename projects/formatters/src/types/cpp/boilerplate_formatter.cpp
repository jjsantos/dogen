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
#include <ostream>
#include "dogen/formatters/types/annotation_formatter.hpp"
#include "dogen/formatters/types/cpp/include_formatter.hpp"
#include "dogen/formatters/types/cpp/header_guard_formatter.hpp"
#include "dogen/formatters/types/cpp/boilerplate_formatter.hpp"

namespace dogen {
namespace formatters {
namespace cpp {

boilerplate_formatter::boilerplate_formatter(
    const bool generate_preamble, const bool generate_header_guards)
    : generate_preamble_(generate_preamble),
      generate_header_guards_(generate_header_guards) { }

void boilerplate_formatter::
format_preamble(std::ostream& s, const annotation& a) const {
    if (!generate_preamble_)
        return;

    annotation_formatter af;
    af.format_preamble(s, comment_styles::cpp_style/*single line*/,
        comment_styles::c_style/*multi-line*/, a);
}

void boilerplate_formatter::
format_guards_begin(std::ostream& s, const std::string& header_guard) const {
    if (!generate_header_guards_)
        return;

    header_guard_formatter f;
    f.format_begin(s, header_guard);

    if (!header_guard.empty())
        s << std::endl;
}

void boilerplate_formatter::
format_guards_end(std::ostream& s, const std::string& header_guard) const {
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

void boilerplate_formatter::
format_postamble(std::ostream& s, const annotation& a) const {
    annotation_formatter af;
    af.format_postamble(s, comment_styles::c_style, a);
}

void boilerplate_formatter::
format_end(std::ostream& s, const annotation& a,
    const std::string& header_guard) const {
    format_postamble(s, a);
    format_guards_end(s, header_guard);
}

} } }
