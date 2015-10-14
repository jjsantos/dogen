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
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/formatters/types/cpp/header_guard_formatter.hpp"

namespace {

const std::string ifndef("#ifndef ");
const std::string define("#define ");
const std::string endif("#endif");

const std::string msvc_line_1("#if defined(_MSC_VER) && (_MSC_VER >= 1200)");
const std::string msvc_line_2("#pragma once");
const std::string msvc_line_3("#endif");

const std::string empty;
const std::string dot(".");
const std::string separator("_");

}

namespace dogen {
namespace formatters {
namespace cpp {

void header_guard_formatter::
format_begin(std::ostream& s, const std::string& header_guard) {
    if (header_guard.empty())
        return;

    s << ifndef << header_guard;
    s << std::endl << define << header_guard;

    s << std::endl << std::endl
      << msvc_line_1 << std::endl
      << msvc_line_2 << std::endl
      << msvc_line_3 << std::endl
      << dogen::formatters::manage_blank_lines << std::endl;
}

void header_guard_formatter::
format_end(std::ostream& s, const std::string& header_guard) {
    if (header_guard.empty())
        return;

    s << endif << std::endl;
}

} } }
