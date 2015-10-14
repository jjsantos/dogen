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
#include "dogen/dia/types/all.hpp"
#include "dogen/dia/io/all_io.hpp"
#include "dogen/dia/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("dia");
const std::string test_suite("swap_spec");

}

using namespace dogen::dia;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(swap)

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");

    test_swap<attribute_generator>();
    test_swap<boolean_generator>();
    test_swap<child_node_generator>();
    test_swap<color_generator>();
    test_swap<composite_generator>();
    test_swap<connection_generator>();
    test_swap<diagram_data_generator>();
    test_swap<diagram_generator>();
    test_swap<enumeration_generator>();
    test_swap<font_generator>();
    test_swap<integer_generator>();
    test_swap<layer_generator>();
    test_swap<object_generator>();
    test_swap<point_generator>();
    test_swap<real_generator>();
    test_swap<rectangle_generator>();
    test_swap<string_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
