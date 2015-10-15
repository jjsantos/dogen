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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn_dia/types/processing_error.hpp"
#include "dogen/yarn_dia/io/processed_comment_io.hpp"
#include "dogen/yarn_dia/types/comment_processor.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("yarn_dia");
const std::string test_suite("comment_processor_spec");

const std::string line_1("line 1");
const std::string line_2("line 2");
const std::string line_3("line 3");

const std::string instruction_1("#DOGEN KEY=VALUE");
const std::string key_1("KEY");
const std::string value_1("VALUE");

const std::string instruction_2(
    "#DOGEN a strange key = some really complicated value 1234");
const std::string key_2("a strange key ");
const std::string value_2(" some really complicated value 1234");

const std::string instruction_3("#DOGEN KEY3=VALUE3");
const std::string key_3("KEY3");
const std::string value_3("VALUE3");

const std::string instruction_with_no_key(
    "#DOGEN some really complicated value 1234");
const std::string instruction_with_no_value("#DOGEN KEY=");
const std::string unknown_marker("#UNKNOWN a=b");
const std::string marker_without_space("#DOGENa=b");
const std::string marker_with_leading_space(" #DOGEN a=b");
const std::string marker_in_lower_case("dogen a=b");
const std::string empty_instruction("#DOGEN ");

const std::string no_sep_msg("Expected separator");

}

using dogen::yarn_dia::processing_error;

BOOST_AUTO_TEST_SUITE(comment_processor)

BOOST_AUTO_TEST_CASE(empty_comments_result_in_empty_documentation_and_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("empty_comments_result_in_empty_documentation_and_key_value_pairs");
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(empty));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.documentation().empty());
    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_CHECK(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(single_line_comment_without_end_line_results_in_expected_documentation_and_emtpy_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("single_line_comment_without_end_line_results_in_expected_documentation_and_emtpy_key_value_pairs");

    BOOST_LOG_SEV(lg, info) << "input: " << line_1;
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(line_1));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::istringstream is(r.documentation());
    std::string line;

    std::getline(is, line);
    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == line_1);

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_CHECK(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(single_line_comment_with_end_line_results_in_expected_documentation_and_emtpy_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("single_line_comment_with_end_line_results_in_expected_documentation_and_emtpy_key_value_pairs");

    std::ostringstream os;
    os << line_1 << std::endl;
    BOOST_LOG_SEV(lg, info) << "input: " << os.str();

    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::istringstream is(r.documentation());
    std::string line;

    std::getline(is, line);
    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == line_1);

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_CHECK(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(multi_line_comment_results_in_expected_documentation_and_emtpy_key_value_pair) {
    SETUP_TEST_LOG_SOURCE("multi_line_comment_results_in_expected_documentation_and_emtpy_key_value_pair");

    std::ostringstream os;
    os << line_1 << std::endl
       << line_2 << std::endl << std::endl
       << line_3 << std::endl;

    BOOST_LOG_SEV(lg, info) << "input: " << os.str();
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(!r.documentation().empty());

    std::istringstream is(r.documentation());
    std::string line;

    std::getline(is, line);
    BOOST_CHECK(line == line_1);

    std::getline(is, line);
    BOOST_CHECK(line == line_2);

    std::getline(is, line);
    BOOST_CHECK(line.empty());

    std::getline(is, line);
    BOOST_CHECK(line == line_3);

    BOOST_CHECK(!std::getline(is, line));

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_CHECK(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(comment_with_valid_instruction_and_no_end_line_results_in_empty_documentation_and_expected_key_value_pair) {
    SETUP_TEST_LOG_SOURCE("comment_with_valid_instruction_and_no_end_line_results_in_empty_documentation_and_expected_key_value_pair");

    BOOST_LOG_SEV(lg, info) << "input: " << instruction_1;
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(instruction_1));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.documentation().empty());
    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().size() == 1);

    const auto& pair(*r.key_value_pairs().begin());
    BOOST_CHECK(pair.first == key_1);
    BOOST_CHECK(pair.second == value_1);
}

BOOST_AUTO_TEST_CASE(comment_with_valid_instruction_and_end_line_results_in_empty_documentation_and_expected_key_value_pair) {
    SETUP_TEST_LOG_SOURCE("comment_with_valid_instruction_and_end_line_results_in_empty_documentation_and_expected_key_value_pair");

    std::ostringstream os;
    os << instruction_1 << std::endl;
    BOOST_LOG_SEV(lg, info) << "input: " << os.str();

    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.documentation().empty());
    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().size() == 1);

    const auto& pair(*r.key_value_pairs().begin());
    BOOST_CHECK(pair.first == key_1);
    BOOST_CHECK(pair.second == value_1);
}

BOOST_AUTO_TEST_CASE(comment_with_instruction_with_no_key_throws) {
    SETUP_TEST_LOG_SOURCE("comment_with_instruction_with_no_key_throws");

    BOOST_LOG_SEV(lg, info) << "input: " << instruction_with_no_key;
    dogen::yarn_dia::comment_processor cp;
    BOOST_CHECK_THROW(cp.process(instruction_with_no_key), processing_error);
}

BOOST_AUTO_TEST_CASE(comment_with_instruction_with_no_value_throws) {
    SETUP_TEST_LOG_SOURCE("comment_with_instruction_with_no_value_throws");

    BOOST_LOG_SEV(lg, info) << "input: " << instruction_with_no_value;
    dogen::yarn_dia::comment_processor cp;
    BOOST_CHECK_THROW(cp.process(instruction_with_no_key), processing_error);
}

BOOST_AUTO_TEST_CASE(comment_with_instruction_marker_but_no_key_value_pair_throws) {
    SETUP_TEST_LOG_SOURCE("comment_with_instruction_marker_but_no_key_value_pair_throws");

    BOOST_LOG_SEV(lg, info) << "input: " << empty_instruction;
    dogen::yarn_dia::comment_processor cp;
    BOOST_CHECK_THROW(cp.process(empty_instruction), processing_error);
}

BOOST_AUTO_TEST_CASE(comment_with_instruction_marker_glued_to_key_and_value_creates_documentation_and_empty_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("comment_with_instruction_marker_glued_to_key_and_value_creates_documentation_and_empty_key_value_pairs");

    BOOST_LOG_SEV(lg, info) << "input: " << marker_without_space;
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(marker_without_space));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.documentation());
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == marker_without_space);

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(comment_with_instruction_marker_preceded_by_leading_space_creates_documentation_and_empty_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("comment_with_instruction_marker_preceded_by_leading_space_creates_documentation_and_empty_key_value_pairs");

    BOOST_LOG_SEV(lg, info) << "input: " << marker_with_leading_space;
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(marker_with_leading_space));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.documentation());
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == marker_with_leading_space);

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(comment_with_instruction_marker_in_lower_case_creates_documentation_and_empty_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("comment_with_instruction_marker_in_lower_case_creates_documentation_and_empty_key_value_pairs");

    BOOST_LOG_SEV(lg, info) << "input: " << marker_in_lower_case;
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(marker_in_lower_case));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.documentation());
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == marker_in_lower_case);

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(comment_with_unknown_marker_creates_documentation_and_empty_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("comment_with_unknown_marker_creates_documentation_and_empty_key_value_pairs");

    BOOST_LOG_SEV(lg, info) << "input: " << unknown_marker;
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(unknown_marker));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.documentation());
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == unknown_marker);

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().empty());
}

BOOST_AUTO_TEST_CASE(multi_line_comment_with_instruction_results_in_expected_documentation_and_expected_key_value_pair) {
    SETUP_TEST_LOG_SOURCE("multi_line_comment_with_instruction_results_in_expected_documentation_and_expected_key_value_pair");

    std::ostringstream os;
    os << line_1 << std::endl
       << instruction_1 << std::endl << std::endl
       << line_3 << std::endl;

    BOOST_LOG_SEV(lg, info) << "input: " << os.str();
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(!r.documentation().empty());

    std::istringstream is(r.documentation());
    std::string line;

    std::getline(is, line);
    BOOST_CHECK(line == line_1);

    std::getline(is, line);
    BOOST_CHECK(line.empty());

    std::getline(is, line);
    BOOST_CHECK(line == line_3);

    BOOST_CHECK(!std::getline(is, line));

    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().size() == 1);
    const auto& pair(*r.key_value_pairs().begin());
    BOOST_CHECK(pair.first == key_1);
    BOOST_CHECK(pair.second == value_1);
}

BOOST_AUTO_TEST_CASE(comment_with_multiple_instructions_results_in_empty_documentation_and_expected_key_value_pairs) {
    SETUP_TEST_LOG_SOURCE("comment_with_multiple_instructions_results_in_empty_documentation_and_expected_key_value_pairs");

    std::ostringstream os;
    os << instruction_1 << std::endl << instruction_2 << std::endl
       << instruction_3 << std::endl << instruction_1 << std::endl;

    BOOST_LOG_SEV(lg, info) << "input: " << os.str();
    dogen::yarn_dia::comment_processor cp;
    const auto r(cp.process(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.documentation().empty());
    BOOST_CHECK(!r.applicable_to_parent_object());
    BOOST_REQUIRE(r.key_value_pairs().size() == 4);

    auto i(r.key_value_pairs().begin());
    BOOST_CHECK(i->first == key_1);
    BOOST_CHECK(i->second == value_1);

    BOOST_CHECK((++i)->first == key_2);
    BOOST_CHECK(i->second == value_2);

    BOOST_CHECK((++i)->first == key_3);
    BOOST_CHECK(i->second == value_3);

    // test duplicate keys
    BOOST_CHECK((++i)->first == key_1);
    BOOST_CHECK(i->second == value_1);
}

BOOST_AUTO_TEST_SUITE_END()
