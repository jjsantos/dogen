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
#include <sstream>
#include "dogen/cpp/test_data/formatters/file_types_td.hpp"
#include "dogen/cpp/test_data/settings/path_settings_td.hpp"

namespace {

dogen::cpp::formatters::file_types
create_dogen_cpp_formatters_file_types(const unsigned int position) {
    return dogen::cpp::formatters::file_types_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {
namespace settings {

path_settings_generator::path_settings_generator() : position_(0) { }

void path_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.file_type(create_dogen_cpp_formatters_file_types(position + 0));
    v.facet_directory(create_std_string(position + 1));
    v.facet_postfix(create_std_string(position + 2));
    v.formatter_postfix(create_std_string(position + 3));
    v.include_directory_name(create_std_string(position + 4));
    v.source_directory_name(create_std_string(position + 5));
    v.disable_facet_directories(create_bool(position + 6));
    v.header_file_extension(create_std_string(position + 7));
    v.implementation_file_extension(create_std_string(position + 8));
}

path_settings_generator::result_type
path_settings_generator::create(const unsigned int position) {
    path_settings r;
    path_settings_generator::populate(position, r);
    return r;
}

path_settings_generator::result_type*
path_settings_generator::create_ptr(const unsigned int position) {
    path_settings* p = new path_settings();
    path_settings_generator::populate(position, *p);
    return p;
}

path_settings_generator::result_type
path_settings_generator::operator()() {
    return create(position_++);
}

} } }
