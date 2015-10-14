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
#include "dogen/dia/test_data/integer_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace dia {

integer_generator::integer_generator() : position_(0) { }

void integer_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_std_string(position + 0));
}

integer_generator::result_type
integer_generator::create(const unsigned int position) {
    integer r;
    integer_generator::populate(position, r);
    return r;
}

integer_generator::result_type*
integer_generator::create_ptr(const unsigned int position) {
    integer* p = new integer();
    integer_generator::populate(position, *p);
    return p;
}

integer_generator::result_type
integer_generator::operator()() {
    return create(position_++);
}

} }
