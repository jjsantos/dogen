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
#include "dogen/formatters/types/indent_filter.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/formatters/types/cpp/header_guard_formatter.hpp"

namespace {

const std::string test_module("formatters");
const std::string test_suite("header_guard_formatter_spec");
const std::string empty;
const std::string empty_guard;
const std::string non_empty_guard("A_FILE_HPP");

const std::string with_guard(R"(#ifndef A_FILE_HPP
#define A_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#endif
)");

}

using namespace dogen::utility::test;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(header_guard_formatter)

BOOST_AUTO_TEST_CASE(non_empty_path_produces_expected_header_guards) {
    SETUP_TEST_LOG_SOURCE("non_empty_path_produces_expected_header_guards");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    dogen::formatters::indent_filter::push(fo, 4);
    fo.push(s);

    dogen::formatters::cpp::header_guard_formatter f;
    f.format_begin(fo, non_empty_guard);
    f.format_end(fo, non_empty_guard);
    const auto r(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(with_guard, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_CASE(empty_path_produces_no_header_guards) {
    SETUP_TEST_LOG_SOURCE("empty_path_produces_no_header_guards");
    BOOST_LOG_SEV(lg, debug) << "Disable modeline top";

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    dogen::formatters::indent_filter::push(fo, 4);
    fo.push(s);

    dogen::formatters::cpp::header_guard_formatter f;
    f.format_begin(s, empty_guard);
    f.format_end(s, empty_guard);
    const auto r(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(empty, r));
    BOOST_LOG_SEV(lg, debug) << "Disable modeline bottom";
}

BOOST_AUTO_TEST_SUITE_END()
