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
#include "dogen/om/test_data/cpp_includes_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::list<boost::filesystem::path> create_std_list_boost_filesystem_path(unsigned int position) {
    std::list<boost::filesystem::path> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_filesystem_path(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {

cpp_includes_generator::cpp_includes_generator() : position_(0) { }

void cpp_includes_generator::
populate(const unsigned int position, result_type& v) {
    v.system(create_std_list_boost_filesystem_path(position + 0));
    v.user(create_std_list_boost_filesystem_path(position + 1));
}

cpp_includes_generator::result_type
cpp_includes_generator::create(const unsigned int position) {
    cpp_includes r;
    cpp_includes_generator::populate(position, r);
    return r;
}
cpp_includes_generator::result_type*
cpp_includes_generator::create_ptr(const unsigned int position) {
    cpp_includes* p = new cpp_includes();
    cpp_includes_generator::populate(position, *p);
    return p;
}

cpp_includes_generator::result_type
cpp_includes_generator::operator()() {
    return create(position_++);
}

} }
