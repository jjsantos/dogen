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
#include <list>
#include <boost/test/unit_test.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/tack_dia/io/processed_object_io.hpp"
#include "dogen/tack_dia/test/mock_processed_object_factory.hpp"
#include "dogen/tack_dia/types/graphing_error.hpp"
#include "dogen/tack_dia/types/grapher.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using namespace dogen::tack_dia;
using dogen::utility::test::asserter;
using dogen::utility::test::contains_checker;
using dogen::tack_dia::test::mock_processed_object_factory;

namespace  {

const std::string test_module("tack_dia");
const std::string test_suite("grapher_spec");
const std::string graph_generated("Graph has already been generated");
const std::string graph_not_generated("Graph has not yet been generated");
const std::string graph_has_cycle("Graph has a cycle");

bool is_root_id(const std::string id) {
    return id == dogen::tack_dia::grapher::root_id();
}

class visitor : public boost::default_dfs_visitor {
public:
    explicit visitor(std::list<dogen::tack_dia::processed_object>& o)
        : objects_(o) {}

public:
    template<typename Vertex, typename Graph>
    void finish_vertex(const Vertex& u, const Graph& g) {
        objects_.push_back(g[u]);
    }

private:
    std::list<dogen::tack_dia::processed_object>& objects_;
};

}

using dogen::utility::test::contains_checker;
using dogen::tack_dia::graphing_error;

BOOST_AUTO_TEST_SUITE(grapher)

BOOST_AUTO_TEST_CASE(not_adding_objects_to_graph_produces_only_root_object) {
    SETUP_TEST_LOG_SOURCE("not_adding_objects_to_graph_produces_only_root_object");

    std::list<dogen::tack_dia::processed_object> o;
    visitor v(o);

    dogen::tack_dia::grapher g;
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 1);
    BOOST_CHECK(is_root_id(o.back().id()));
}

BOOST_AUTO_TEST_CASE(adding_unrelated_objects_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_unrelated_objects_produces_expected_order");
    dogen::tack_dia::grapher g;
    g.add(mock_processed_object_factory::make_large_package(0));
    g.add(mock_processed_object_factory::make_class(1));
    g.add(mock_processed_object_factory::make_class(2));

    std::list<dogen::tack_dia::processed_object> o;
    visitor v(o);
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 4);

    auto i(o.begin());
    BOOST_CHECK(i->id() == mock_processed_object_factory::to_oject_id(0));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(adding_generalization_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_generalization_produces_expected_order");

    dogen::tack_dia::grapher g;
    g.add(mock_processed_object_factory::make_generalization(0));

    std::list<dogen::tack_dia::processed_object> o;
    visitor v(o);
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 3);

    auto i(o.begin());
    BOOST_CHECK(i->id() == mock_processed_object_factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(adding_generalization_inside_package_produces_expected_order) {
    SETUP_TEST_LOG_SOURCE("adding_generalization_inside_package_produces_expected_order");

    dogen::tack_dia::grapher g;
    g.add(mock_processed_object_factory::
        make_generalization_inside_large_package(0));

    std::list<dogen::tack_dia::processed_object> o;
    visitor v(o);
    g.generate();
    boost::depth_first_search(g.graph(), boost::visitor(v));
    BOOST_LOG_SEV(lg, debug) << o;

    BOOST_REQUIRE(o.size() == 4);

    auto i(o.begin());
    BOOST_CHECK(i->id() == mock_processed_object_factory::to_oject_id(0));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(1));
    BOOST_CHECK((++i)->id() == mock_processed_object_factory::to_oject_id(2));
    BOOST_CHECK(is_root_id((++i)->id()));
}

BOOST_AUTO_TEST_CASE(generating_after_graph_has_been_generated_throws) {
    SETUP_TEST_LOG("generating_after_graph_has_been_generated_throws");

    dogen::tack_dia::grapher g;
    g.generate();
    const auto o(mock_processed_object_factory::make_class(0));
    contains_checker<graphing_error> c(graph_generated);
    BOOST_CHECK_EXCEPTION(g.generate(), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(adding_object_after_graph_has_been_generated_throws) {
    SETUP_TEST_LOG("adding_object_after_graph_has_been_generated_throws");

    dogen::tack_dia::grapher g1;
    g1.generate();
    const auto o(mock_processed_object_factory::make_class(0));
    contains_checker<graphing_error> c(graph_generated);
    BOOST_CHECK_EXCEPTION(g1.add(o), graphing_error, c);

    dogen::tack_dia::grapher g2;
    g2.add(o);
    g2.generate();
    BOOST_CHECK_EXCEPTION(g2.add(o), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(querying_state_before_generating_throws) {
    SETUP_TEST_LOG("querying_state_before_generating_throws");

    dogen::tack_dia::grapher g;
    const auto o(mock_processed_object_factory::make_class(0));
    contains_checker<graphing_error> c(graph_not_generated);
    BOOST_CHECK_EXCEPTION(g.graph(), graphing_error, c);
    BOOST_CHECK_EXCEPTION(g.child_id_to_parent_ids(), graphing_error, c);
    BOOST_CHECK_EXCEPTION(g.parent_ids(), graphing_error, c);
    BOOST_CHECK_EXCEPTION(g.top_level_module_names(), graphing_error, c);
}

BOOST_AUTO_TEST_CASE(generating_graph_with_first_degree_cycle_throws) {
    SETUP_TEST_LOG("generating_graph_with_first_degree_cycle_throws");

    dogen::tack_dia::grapher g;
    g.add(mock_processed_object_factory::make_first_degree_cycle(0));
    contains_checker<graphing_error> c(graph_has_cycle);
    BOOST_CHECK_EXCEPTION(g.generate(), graphing_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
