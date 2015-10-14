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
#include "dogen/config/test_data/cpp_options_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace config {

cpp_options_generator::cpp_options_generator() : position_(0) { }

void cpp_options_generator::
populate(const unsigned int position, result_type& v) {
    v.project_directory_path(create_boost_filesystem_path(position + 0));
    v.disable_cmakelists(create_bool(position + 1));
}

cpp_options_generator::result_type
cpp_options_generator::create(const unsigned int position) {
    cpp_options r;
    cpp_options_generator::populate(position, r);
    return r;
}

cpp_options_generator::result_type*
cpp_options_generator::create_ptr(const unsigned int position) {
    cpp_options* p = new cpp_options();
    cpp_options_generator::populate(position, *p);
    return p;
}

cpp_options_generator::result_type
cpp_options_generator::operator()() {
    return create(position_++);
}

} }
