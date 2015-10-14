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
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/formatters/types/modeline_group_hydrator.hpp"
#include "dogen/formatters/io/modeline_group_io.hpp"
#include "dogen/formatters/types/hydration_error.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("formatters");
const std::string test_suite("modeline_group_hydrator_spec");

const std::string duplicate_group("Duplicate modeline group");
const std::string invalid_dir("INVALID_DIRECTORY__");
const std::string dir_not_found_message("Could not find directory");
const std::string not_a_dir_message("Not a directory");
const std::string invalid_file_message("Failed to parse JSON file");
const std::string emacs_modeline_group("modeline_groups/emacs.json");
const std::string invalid_json_file("NOTJSONTFILE");

const std::string no_editor(R"(
{
    "group_name" : "emacs",
    "modelines" : [
        {
            "modeline_name" : "cpp",
            "location" : "top",
            "fields" : [
                {
                    "name" : "mode",
                    "value" : "c++"
                }
            ]
        }
    ]
})");
const std::string no_editor_message("No such node (editor)");

const std::string unsupported_editor(R"(
{
    "group_name" : "emacs",
    "modelines" : [
        {
            "modeline_name" : "cpp",
            "editor" : "gedit",
            "location" : "top",
            "fields" : [
                {
                    "name" : "mode",
                    "value" : "c++"
                }
            ]
        }
    ]
})");
const std::string unsupported_editor_message("Invalid or unsupported editor");

const std::string no_location(R"(
{
    "group_name" : "emacs",
    "modelines" : [
        {
            "modeline_name" : "cpp",
            "editor" : "emacs",
            "fields" : [
                {
                    "name" : "mode",
                    "value" : "c++"
                }
            ]
        }
    ]
})");

const std::string invalid_location(R"(
{
    "group_name" : "emacs",
    "modelines" : [
        {
            "modeline_name" : "cpp",
            "editor" : "emacs",
            "location" : "middle",
            "fields" : [
                {
                    "name" : "mode",
                    "value" : "c++"
                }
            ]
        }
    ]
})");
const std::string invalid_location_message("Invalid or unsupported modeline location");

const std::string no_fields(R"(
{
    "group_name" : "emacs",
    "modelines" : [
        {
            "modeline_name" : "cpp",
            "editor" : "emacs",
            "location" : "top"
        }
   ]
})");
const std::string no_fields_message("Modeline must have at least");

}

using namespace dogen::formatters;
using namespace dogen::utility::test;
using dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(modeline_group_hydrator)

BOOST_AUTO_TEST_CASE(hydrating_emacs_modeline_group_results_in_expected_modelines) {
    SETUP_TEST_LOG_SOURCE("hydrating_emacs_modeline_group_results_in_expected_modelines");
    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / emacs_modeline_group);
    boost::filesystem::ifstream s(p);
    dogen::formatters::modeline_group_hydrator h;
    const auto r(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "modeline group: " << r;
    BOOST_CHECK(!r.modelines().empty());
    for (const auto& pair : r.modelines()) {
        BOOST_CHECK(!pair.first.empty());

        const auto& modeline(pair.second);
        BOOST_CHECK(!modeline.fields().empty());
        BOOST_CHECK(modeline.editor() == dogen::formatters::editors::emacs);
        BOOST_CHECK(modeline.location() == dogen::formatters::modeline_locations::top);

        // value  may be empty so nothing can be said about it.
        for (const auto& fields : modeline.fields())
            BOOST_CHECK(!fields.name().empty());
    }
}

BOOST_AUTO_TEST_CASE(supplying_invalid_json_file_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_json_file_throws");

    std::istringstream s(invalid_json_file);
    using namespace dogen::utility::filesystem;

    dogen::formatters::modeline_group_hydrator h;
    contains_checker<dogen::formatters::hydration_error> c(invalid_file_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::formatters::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(not_supplying_editor_throws) {
    SETUP_TEST_LOG_SOURCE("not_supplying_editor_throws");

    std::istringstream s(no_editor);
    using namespace dogen::utility::filesystem;

    dogen::formatters::modeline_group_hydrator h;
    contains_checker<dogen::formatters::hydration_error> c(no_editor_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::formatters::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(supplying_unsupported_editor_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_unsupported_editor_throws");

    std::istringstream s(unsupported_editor);
    dogen::formatters::modeline_group_hydrator h;
    contains_checker<dogen::formatters::hydration_error> c(unsupported_editor_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::formatters::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(not_supplying_location_results_in_a_valid_location) {
    SETUP_TEST_LOG_SOURCE("not_supplying_location_results_in_a_valid_location");

    std::istringstream s(no_location);
    dogen::formatters::modeline_group_hydrator h;
    const auto r(h.hydrate(s));

    BOOST_LOG_SEV(lg, debug) << "modeline group: " << r;
    BOOST_CHECK(r.modelines().size() == 1);
    const auto& ml(r.modelines().begin()->second);
    BOOST_CHECK(ml.location() !=
       dogen::formatters::modeline_locations::invalid);
}

BOOST_AUTO_TEST_CASE(supplying_invalid_location_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_location_throws");

    std::istringstream s(invalid_location);
    dogen::formatters::modeline_group_hydrator h;
    contains_checker<dogen::formatters::hydration_error> c(invalid_location_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::formatters::hydration_error, c);
}

BOOST_AUTO_TEST_CASE(supplying_no_fields_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_no_fields_throws");

    std::istringstream s(no_fields);
    dogen::formatters::modeline_group_hydrator h;
    contains_checker<dogen::formatters::hydration_error> c(no_fields_message);
    BOOST_CHECK_EXCEPTION(h.hydrate(s), dogen::formatters::hydration_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
