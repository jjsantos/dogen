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
#include "dogen/yarn/test_data/location_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

location_generator::location_generator() : position_(0) { }

void location_generator::
populate(const unsigned int position, result_type& v) {
    v.original_model_name(create_std_string(position + 0));
    v.external_module_path(create_std_list_std_string(position + 1));
    v.model_module_path(create_std_list_std_string(position + 2));
    v.internal_module_path(create_std_list_std_string(position + 3));
}

location_generator::result_type
location_generator::create(const unsigned int position) {
    location r;
    location_generator::populate(position, r);
    return r;
}

location_generator::result_type*
location_generator::create_ptr(const unsigned int position) {
    location* p = new location();
    location_generator::populate(position, *p);
    return p;
}

location_generator::result_type
location_generator::operator()() {
    return create(position_++);
}

} }
