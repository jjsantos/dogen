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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/test_models/std_model/types/all.hpp"
#include "dogen/test_models/std_model/io/all_io.hpp"
#include "dogen/test_models/std_model/serialization/all_ser.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"
#include "dogen/test_models/std_model/test_data/all_td.hpp"
#include "dogen/test_models/std_model/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("std_model");

}

using namespace dogen::test_models::std_model;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(std_model)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<class_a_generator>();
    test_equality<class_b_generator>();
    test_equality<class_d_generator>();
    test_equality<class_e_generator>();
    test_equality<class_f_generator>();
    test_equality<class_g_generator>();
    test_equality<class_h_generator>();
    test_equality<class_j_generator>();
    test_equality<primitives_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<class_a_generator>();
    roundtrip_type<class_b_generator>();
    roundtrip_type<class_d_generator>();
    roundtrip_type<class_e_generator>();
    roundtrip_type<class_f_generator>();
    roundtrip_type<class_g_generator>();
    roundtrip_type<class_h_generator>();
    roundtrip_type<class_j_generator>();
    roundtrip_type<primitives_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<class_a_generator>();
    test_hashing<class_b_generator>();
    test_hashing<class_d_generator>();
    test_hashing<class_e_generator>();
    test_hashing<class_f_generator>();
    test_hashing<class_g_generator>();
    test_hashing<class_h_generator>();
    test_hashing<class_j_generator>();
    test_hashing<primitives_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_hashing");
    test_swap<class_a_generator>();
    test_swap<class_b_generator>();
    test_swap<class_d_generator>();
    test_swap<class_e_generator>();
    test_swap<class_f_generator>();
    test_swap<class_g_generator>();
    test_swap<class_h_generator>();
    test_swap<class_j_generator>();
    test_swap<primitives_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<class_a_generator>();
    test_io<class_b_generator>();
    test_io<class_d_generator>();
    test_io<class_e_generator>();
    test_io<class_f_generator>();
    test_io<class_g_generator>();
    test_io<class_h_generator>();
    test_io<class_j_generator>();
    test_io<primitives_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    test_move_assignment_copy<class_a_generator>();
    test_move_assignment_copy<class_b_generator>();
    test_move_assignment_copy<class_d_generator>();
    test_move_assignment_copy<class_e_generator>();
    test_move_assignment_copy<class_f_generator>();
    test_move_assignment_copy<class_g_generator>();
    test_move_assignment_copy<class_h_generator>();
    test_move_assignment_copy<class_j_generator>();
    test_move_assignment_copy<primitives_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
