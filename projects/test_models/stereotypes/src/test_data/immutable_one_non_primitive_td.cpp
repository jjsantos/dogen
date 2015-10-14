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
#include "dogen/test_models/stereotypes/test_data/immutable_one_non_primitive_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace test_models {
namespace stereotypes {

immutable_one_non_primitive_generator::immutable_one_non_primitive_generator() : position_(0) { }

immutable_one_non_primitive_generator::result_type
immutable_one_non_primitive_generator::create(const unsigned int position) {
    return immutable_one_non_primitive(
        create_std_string(position + 0)
        );
}

immutable_one_non_primitive_generator::result_type*
immutable_one_non_primitive_generator::create_ptr(const unsigned int position) {
    return new immutable_one_non_primitive(create(position));
}

immutable_one_non_primitive_generator::result_type
immutable_one_non_primitive_generator::operator()() {
    return create(position_++);
}

} } }
