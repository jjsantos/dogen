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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/tack/types/all.hpp"
#include "dogen/tack/hash/all_hash.hpp"
#include "dogen/tack/io/all_io.hpp"
#include "dogen/tack/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("tack");
const std::string test_suite("move_copy_assignment_spec");

}

using namespace dogen::tack;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(move_assignment_copy)

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");

    test_move_assignment_copy<generation_types_generator>();
    test_move_assignment_copy<nested_name_generator>();
    test_move_assignment_copy<property_generator>();
    test_move_assignment_copy<name_generator>();
    test_move_assignment_copy<primitive_generator>();
    test_move_assignment_copy<enumerator_generator>();
    test_move_assignment_copy<enumeration_generator>();
    test_move_assignment_copy<module_generator>();
    test_move_assignment_copy<object_generator>();
    test_move_assignment_copy<concept_generator>();
    test_move_assignment_copy<model_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
