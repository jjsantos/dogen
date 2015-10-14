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
#include "dogen/test_models/stereotypes/test_data/value_td.hpp"
#include "dogen/test_models/stereotypes/test_data/immutable_four_td.hpp"
#include "dogen/test_models/stereotypes/test_data/immutable_one_primitive_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::test_models::stereotypes::value
create_dogen_test_models_stereotypes_value(const unsigned int position) {
    return dogen::test_models::stereotypes::value_generator::create(position);
}

dogen::test_models::stereotypes::immutable_one_primitive
create_dogen_test_models_stereotypes_immutable_one_primitive(const unsigned int position) {
    return dogen::test_models::stereotypes::immutable_one_primitive_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace stereotypes {

immutable_four_generator::immutable_four_generator() : position_(0) { }

immutable_four_generator::result_type
immutable_four_generator::create(const unsigned int position) {
    return immutable_four(
        create_bool(position + 0),
        create_std_string(position + 1),
        create_dogen_test_models_stereotypes_value(position + 2),
        create_dogen_test_models_stereotypes_immutable_one_primitive(position + 3)
        );
}

immutable_four_generator::result_type*
immutable_four_generator::create_ptr(const unsigned int position) {
    return new immutable_four(create(position));
}

immutable_four_generator::result_type
immutable_four_generator::operator()() {
    return create(position_++);
}

} } }
