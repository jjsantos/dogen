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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/formatters/types/comment_formatter.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("formatters");
const std::string test_suite("comment_formatter_spec");

const std::string c_style_empty(R"(/*
 *
 */
)");

const std::string doxygen_c_style_empty(R"(/**
 *
 */
)");

const std::string licence_c_style(R"(/* -*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 *
 */
)");

const std::string licence_shell_style(R"(# -*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
#
)");

const std::string modeline_shell_style(R"(# -*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
)");

const std::string function_doxygen(R"(/**
 * @brief Ends the comment block.
 */
)");
const std::string doxygen_brief("Ends the comment block.");

const std::string modeline(
    "-*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-");
const std::string licence(R"(Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>

This program is free software; you can redistribute it and/or modify)");

const std::string doxgen_multi_line(R"(OM is the Output Model.

@section om_0 Objective

OM was designed to model the contents of the files to output with only the
required level of flexibility needed by Dogen. Thus it does not aim to model
)");

const std::string multi_line_doxygen_c_style(R"(/**
 * @brief OM is the Output Model.
 *
 * @section om_0 Objective
 *
 * OM was designed to model the contents of the files to output with only the
 * required level of flexibility needed by Dogen. Thus it does not aim to model
 *
 */
)");

const std::string multi_line_text(R"(use extensions similar to the dogen ones
--ixx-suffix .ipp
--hxx-suffix .hpp
)");

const std::string multi_line_text_shell_style(R"(# use extensions similar to the dogen ones
# --ixx-suffix .ipp
# --hxx-suffix .hpp
)");

const std::string enumeration("Represents an uninitialised enum");
const std::string enumeration_doxygen(R"(///< Represents an uninitialised enum)");

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

template<typename Content>
std::string format(const dogen::formatters::comment_formatter& f,
    const Content& c, const bool line_between) {
    std::ostringstream s;
    f.format(s, c, line_between);
    return s.str();
}

template<typename Content>
std::string format(const dogen::formatters::comment_formatter& f,
    const Content& c) {
    std::ostringstream s;
    f.format(s, c);
    return s.str();
}

}

using namespace dogen::utility::test;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(comment_formatter)

BOOST_AUTO_TEST_CASE(formatting_empty_string_as_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_empty_string_as_c_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f;
    const auto r(format(f, empty));
    BOOST_CHECK(asserter::assert_equals_marker(c_style_empty, r));
}

BOOST_AUTO_TEST_CASE(formatting_empty_string_as_doxygen_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_empty_string_as_doxygen_c_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::c_style,
        !last_line_is_blank);

    const auto r(format(f, empty));
    BOOST_CHECK(asserter::assert_equals_marker(doxygen_c_style_empty, r));
}

BOOST_AUTO_TEST_CASE(formatting_licence_as_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_licence_as_c_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::c_style,
        last_line_is_blank);

    std::list<std::string> content { modeline, licence };
    const auto r(format(f, content, line_between_blocks));
    BOOST_CHECK(asserter::assert_equals_marker(licence_c_style, r));
}

BOOST_AUTO_TEST_CASE(formatting_licence_as_shell_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_licence_as_shell_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::shell_style,
        last_line_is_blank);

    std::list<std::string> content { modeline, licence };
    const auto r(format(f, content, line_between_blocks));
    BOOST_CHECK(asserter::assert_equals_marker(licence_shell_style, r));
}

BOOST_AUTO_TEST_CASE(formatting_modeline_as_shell_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_modeline_as_shell_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::shell_style,
        !last_line_is_blank);

    const auto r(format(f, modeline));
    BOOST_CHECK(asserter::assert_equals_marker(modeline_shell_style, r));
}

BOOST_AUTO_TEST_CASE(formatting_one_line_as_doxygen_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_one_line_as_doxygen_c_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::c_style,
        !last_line_is_blank);

    const auto r(format(f, doxygen_brief));
    BOOST_CHECK(asserter::assert_equals_marker(function_doxygen, r));
}

BOOST_AUTO_TEST_CASE(formatting_multi_line_as_doxygen_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_multi_line_as_doxygen_c_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::c_style,
        last_line_is_blank);

    const auto r(format(f, doxgen_multi_line));
    BOOST_CHECK(asserter::assert_equals_marker(multi_line_doxygen_c_style, r));
}

BOOST_AUTO_TEST_CASE(formatting_one_line_as_doxygen_cpp_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_one_line_as_doxygen_cpp_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        dogen::formatters::comment_styles::cpp_style,
        !last_line_is_blank);

    const auto r(format(f, enumeration));
    BOOST_CHECK(asserter::assert_equals_marker(enumeration_doxygen, r));
}

BOOST_AUTO_TEST_CASE(formatting_multi_line_text_as_shell_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_multi_line_text_as_shell_style_comment_produces_expected_output");

    dogen::formatters::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::formatters::comment_styles::shell_style,
        !last_line_is_blank);

    const auto r(format(f, multi_line_text));
    BOOST_CHECK(asserter::assert_equals_marker(multi_line_text_shell_style, r));
}

BOOST_AUTO_TEST_SUITE_END()
