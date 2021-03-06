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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/cpp/types/all.hpp"
#include "dogen/cpp/io/all_io.hpp"
#include "dogen/cpp/test_data/all_td.hpp"

namespace {

const std::string empty;
const std::string test_module("cpp");
const std::string test_suite("io_spec");

}

using namespace dogen::cpp;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(io)

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");

    test_io<formattables::class_info_generator>();
    test_io<formattables::cmakelists_info_generator>();
    test_io<formattables::enum_info_generator>();
    test_io<formattables::enumerator_info_generator>();
    test_io<formattables::exception_info_generator>();
    test_io<formattables::namespace_info_generator>();
    test_io<formattables::nested_type_info_generator>();
    test_io<formattables::odb_options_info_generator>();
    test_io<formattables::parent_info_generator>();
    test_io<formattables::property_info_generator>();
    test_io<formattables::registrar_info_generator>();
    test_io<formattables::visitor_info_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
