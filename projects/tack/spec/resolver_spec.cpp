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
#include <array>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/merging_error.hpp"
#include "dogen/tack/types/resolution_error.hpp"
#include "dogen/tack/types/merger.hpp"
#include "dogen/tack/types/resolver.hpp"
#include "dogen/tack/io/model_io.hpp"
#include "dogen/tack/io/property_io.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/tack/test/mock_model_factory.hpp"

namespace {

const std::string test_module("tack");
const std::string test_suite("resolver_spec");

using dogen::tack::test::mock_model_factory;

/*
 * FIXME: we need to update the mock factory to generate merged
 * models. for now as a quick hack, we just  used the merger.
 *
 * FIXME: all properties have model name set and need to be manually
 * unset.
 *
 * Flag was added but does nothing yet.
 */
const mock_model_factory::flags flags(false/*tagged*/, false/*resolved*/,
    true/*merged*/, false/*concepts_indexed*/, false/*properties_indexed*/);

const mock_model_factory factory(flags);

const std::string incorrect_model("Object does not belong to this model");
const std::string inconsistent_kvp("Inconsistency between key and value");
const std::string missing_target("No target model found");
const std::string too_many_targets("Only one target expected.");
const std::string undefined_type("Object has property with undefined type");
const std::string missing_parent("Object's parent could not be located");
const std::string incorrect_meta_type("Object has incorrect meta_type");

bool has_one_parent(const dogen::tack::object& o) {
    using dogen::tack::relationship_types;
    const auto i(o.relationships().find(relationship_types::parents));
    if (i == o.relationships().end() || i->second.empty() ||
        i->second.size() > 1)
        return false;

    return true;
}

dogen::tack::name get_parent_name(const dogen::tack::object& o) {
    using dogen::tack::relationship_types;
    const auto i(o.relationships().find(relationship_types::parents));
    if (i == o.relationships().end() || i->second.empty() ||
        i->second.size() > 1)
        BOOST_FAIL("Object has got one parent");

    return i->second.front();
}

}

using dogen::utility::test::contains_checker;
using dogen::tack::resolution_error;

BOOST_AUTO_TEST_SUITE(resolver)

BOOST_AUTO_TEST_CASE(object_with_property_type_in_the_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_property_type_in_the_same_model_resolves_successfully");
    auto m(factory.object_with_property());
    BOOST_CHECK(m.objects().size() == 2);
    BOOST_CHECK(m.primitives().empty());

    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        BOOST_CHECK(o.local_properties().size() == 1 ||
            o.local_properties().empty());
        if (o.local_properties().size() == 1)
            o.local_properties().begin()->type().
                type().location().original_model_name("");
    }
    const auto original(m);
    BOOST_LOG_SEV(lg, debug) << "original: " << original;

    dogen::tack::resolver res(m);
    BOOST_CHECK(!res.has_resolved());
    res.resolve();
    BOOST_CHECK(res.has_resolved());
    BOOST_LOG_SEV(lg, debug) << "resolved: " << m;
    // FIXME: fails for some reason. checked equals operator and looks ok
    // BOOST_CHECK(m != original);

    bool found(false);
    for (const auto pair : m.objects()) {
        const auto& n(pair.first);
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified();
            found = true;

            const auto& o(pair.second);
            BOOST_CHECK(o.local_properties().size() == 1);
            const auto& prop(o.local_properties().front());
            BOOST_LOG_SEV(lg, debug) << "property: " << prop;
            BOOST_CHECK(factory.is_type_name_n(1, prop.type().type()));
            BOOST_CHECK(factory.is_model_n(0, prop.type().type()));
            BOOST_CHECK(o.object_type() ==
                dogen::tack::object_types::user_defined_value_object);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_property_type_in_different_model_results_in_successful_merge) {
    SETUP_TEST_LOG_SOURCE("object_with_property_type_in_different_model_results_in_successful_merge");

    auto m(factory.object_with_property_type_in_different_model());
    m[0].is_target(true);

    dogen::tack::merger mg;
    mg.add(m[0]);
    mg.add(m[1]);

    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    dogen::tack::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.first);
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified();
            found = true;

            const auto& o(pair.second);
            BOOST_CHECK(o.local_properties().size() == 1);
            const auto& prop(o.local_properties().front());
            BOOST_LOG_SEV(lg, debug) << "property: " << prop;

            BOOST_CHECK(factory.is_type_name_n(1, prop.type().type()));
            BOOST_CHECK(factory.is_model_n(1, prop.type().type()));
            BOOST_CHECK(o.object_type() ==
                dogen::tack::object_types::user_defined_value_object);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_property_type_throws) {
    SETUP_TEST_LOG("object_with_missing_property_type_throws");

    auto m(factory.object_with_missing_property_type());
    dogen::tack::resolver res(m);
    contains_checker<resolution_error> c(undefined_type);
    BOOST_CHECK_EXCEPTION(res.resolve(), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_the_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_the_same_model_resolves_successfully");
    dogen::tack::merger mg;
    auto m(factory.object_with_parent_in_the_same_model());
    m.is_target(true);
    mg.add(m);
    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    dogen::tack::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.first);
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified();
            found = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(has_one_parent(o));
            const auto pn(get_parent_name(o));
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
            BOOST_CHECK(o.object_type() ==
                dogen::tack::object_types::user_defined_value_object);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_parent_in_different_models_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_parent_in_different_models_resolves_successfully");

    auto m(factory.object_with_parent_in_different_models());
    m[0].is_target(true);

    dogen::tack::merger mg;
    mg.add(m[0]);
    mg.add(m[1]);
    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 2);
    BOOST_CHECK(combined.primitives().empty());

    dogen::tack::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.first);
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified();
            found = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(has_one_parent(o));
            const auto pn(get_parent_name(o));
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(1, pn));
            BOOST_CHECK(o.object_type() ==
                dogen::tack::object_types::user_defined_value_object);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_same_model_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_same_model_resolves_successfully");
    auto m(factory.object_with_third_degree_parent_in_same_model());
    m.is_target(true);

    dogen::tack::merger mg;
    mg.add(m);

    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    dogen::tack::resolver res(combined);
    res.resolve();

    bool found_one(false);
    bool found_two(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.first);
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified();
            found_one = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(has_one_parent(o));
            const auto pn(get_parent_name(o));
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
            BOOST_CHECK(o.object_type() ==
                dogen::tack::object_types::user_defined_value_object);
        } else if (factory.is_type_name_n(1, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified();
            found_two = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(has_one_parent(o));
            const auto pn(get_parent_name(o));
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified();
            BOOST_CHECK(factory.is_type_name_n(2, pn));
            BOOST_CHECK(factory.is_model_n(0, pn));
            BOOST_CHECK(o.object_type() ==
                dogen::tack::object_types::user_defined_value_object);
        }
    }
    BOOST_CHECK(found_one);
    BOOST_CHECK(found_two);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_missing_within_single_model_throws) {
    SETUP_TEST_LOG("object_with_third_degree_parent_missing_within_single_model_throws");
    dogen::tack::merger mg;
    auto m(factory.object_with_third_degree_parent_missing());
    m.is_target(true);
    mg.add(m);
    mg.merge();

    contains_checker<resolution_error> c(missing_parent);
    dogen::tack::resolver res(m);
    BOOST_CHECK_EXCEPTION(res.resolve(), resolution_error, c);
}

BOOST_AUTO_TEST_CASE(object_with_third_degree_parent_in_different_models_resolves_successfully) {
    SETUP_TEST_LOG_SOURCE("object_with_third_degree_parent_in_different_models_resolves_successfully");

    auto a(factory.object_with_third_degree_parent_in_different_models());
    a[0].is_target(true);

    dogen::tack::merger mg;
    mg.add(a[0]);
    mg.add(a[1]);
    mg.add(a[2]);
    mg.add(a[3]);

    auto combined(mg.merge());
    BOOST_CHECK(combined.objects().size() == 4);
    BOOST_CHECK(combined.primitives().empty());

    dogen::tack::resolver res(combined);
    res.resolve();

    bool found(false);
    for (const auto pair : combined.objects()) {
        const auto& n(pair.first);
        if (factory.is_type_name_n(0, n)) {
            BOOST_LOG_SEV(lg, debug) << "found object: " << n.qualified();
            found = true;

            const auto& o(pair.second);
            BOOST_REQUIRE(has_one_parent(o));
            const auto pn(get_parent_name(o));
            BOOST_LOG_SEV(lg, debug) << "parent: " << pn.qualified();
            BOOST_CHECK(factory.is_type_name_n(1, pn));
            BOOST_CHECK(factory.is_model_n(1, pn));
            BOOST_CHECK(o.object_type() ==
                dogen::tack::object_types::user_defined_value_object);
        }
    }
    BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE(object_with_missing_third_degree_parent_in_different_models_throws) {
    SETUP_TEST_LOG("object_with_missing_third_degree_parent_in_different_models_throws");
    dogen::tack::merger mg;
    auto a(
        factory.object_with_missing_third_degree_parent_in_different_models());
    a[0].is_target(true);
    mg.add(a[0]);
    mg.add(a[1]);
    mg.add(a[2]);

    auto combined(mg.merge());
    dogen::tack::resolver res(combined);

    contains_checker<resolution_error> c(missing_parent);
    BOOST_CHECK_EXCEPTION(res.resolve(), resolution_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
