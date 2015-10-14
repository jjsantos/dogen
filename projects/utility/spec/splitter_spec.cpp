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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/string/splitter.hpp"

namespace {

const std::string empty;
const std::string test_module("utility");
const std::string test_suite("splitter_spec");

}

BOOST_AUTO_TEST_SUITE(splitter)

BOOST_AUTO_TEST_CASE(parsing_scoped_string_with_no_scope_operators_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_scoped_string_with_no_scope_operators_produces_expected_result");

    const std::string i("value");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using dogen::utility::string::splitter;
    const auto a(splitter::split_scoped(i));
    BOOST_REQUIRE(a.size() == 1);
    BOOST_CHECK(a.front() == i);
}

BOOST_AUTO_TEST_CASE(parsing_scoped_string_with_many_scope_operators_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_scoped_string_with_many_scope_operators_produces_expected_result");

    const std::string i("a::b::c::d");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using dogen::utility::string::splitter;
    auto a(splitter::split_scoped(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 4);
    BOOST_CHECK(a.front() == "a");
    a.pop_front();

    BOOST_CHECK(a.front() == "b");
    a.pop_front();

    BOOST_CHECK(a.front() == "c");
    a.pop_front();

    BOOST_CHECK(a.front() == "d");
}

BOOST_AUTO_TEST_CASE(parsing_empty_scoped_string_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_empty_scoped_string_produces_expected_result");

    BOOST_LOG_SEV(lg, info) << "input: " << empty;

    using dogen::utility::string::splitter;
    const auto a(splitter::split_scoped(empty));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_scoped_string_with_only_scope_operators_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_scoped_string_with_only_scope_operators_produces_expected_result");

    const std::string i("::::");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using dogen::utility::string::splitter;
    auto a(splitter::split_scoped(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_no_commas_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_no_commas_produces_expected_result");

    const std::string i("value");
    using dogen::utility::string::splitter;
    const auto a(splitter::split_csv(i));

    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.size() == 1);
    BOOST_CHECK(a.front() == i);
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_many_commas_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_many_commas_produces_expected_result");

    const std::string i("a,b,c,d");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using dogen::utility::string::splitter;
    auto a(splitter::split_csv(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 4);
    BOOST_CHECK(a.front() == "a");
    a.pop_front();

    BOOST_CHECK(a.front() == "b");
    a.pop_front();

    BOOST_CHECK(a.front() == "c");
    a.pop_front();

    BOOST_CHECK(a.front() == "d");
}

BOOST_AUTO_TEST_CASE(parsing_empty_csv_string_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_empty_csv_string_produces_expected_result");

    BOOST_LOG_SEV(lg, info) << "input: " << empty;

    using dogen::utility::string::splitter;
    const auto a(splitter::split_csv(empty));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_only_commas_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_only_commas_produces_expected_result");

    const std::string i(",,");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using dogen::utility::string::splitter;
    auto a(splitter::split_csv(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_spaces_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_spaces_produces_expected_result");

    const std::string i(" a, b, c ,d,   e,f   ");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using dogen::utility::string::splitter;
    auto a(splitter::split_csv(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 6);
    BOOST_CHECK(a.front() == "a");
    a.pop_front();

    BOOST_CHECK(a.front() == "b");
    a.pop_front();

    BOOST_CHECK(a.front() == "c");
    a.pop_front();

    BOOST_CHECK(a.front() == "d");
    a.pop_front();

    BOOST_CHECK(a.front() == "e");
    a.pop_front();

    BOOST_CHECK(a.front() == "f");
    a.pop_front();
}

BOOST_AUTO_TEST_SUITE_END()
