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
#include "dogen/yarn_dia/test_data/object_types_td.hpp"
#include "dogen/yarn_dia/test_data/processed_object_td.hpp"
#include "dogen/yarn_dia/test_data/processed_comment_td.hpp"
#include "dogen/yarn_dia/test_data/processed_property_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn_dia::object_types
create_dogen_yarn_dia_object_types(const unsigned int position) {
    return dogen::yarn_dia::object_types_generator::create(position);
}

dogen::yarn_dia::processed_comment
create_dogen_yarn_dia_processed_comment(const unsigned int position) {
    return dogen::yarn_dia::processed_comment_generator::create(position);
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

boost::optional<std::pair<std::string, std::string> >
create_boost_optional_std_pair_std_string_std_string_(unsigned int position) {
    boost::optional<std::pair<std::string, std::string> > r(
        create_std_pair_std_string_std_string(position));
    return r;
}

dogen::yarn_dia::processed_property
create_dogen_yarn_dia_processed_property(const unsigned int position) {
    return dogen::yarn_dia::processed_property_generator::create(position);
}

std::list<dogen::yarn_dia::processed_property> create_std_list_dogen_yarn_dia_processed_property(unsigned int position) {
    std::list<dogen::yarn_dia::processed_property> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_dia_processed_property(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn_dia {

processed_object_generator::processed_object_generator() : position_(0) { }

void processed_object_generator::
populate(const unsigned int position, result_type& v) {
    v.id(create_std_string(position + 0));
    v.name(create_std_string(position + 1));
    v.object_type(create_dogen_yarn_dia_object_types(position + 2));
    v.stereotype(create_std_string(position + 3));
    v.comment(create_dogen_yarn_dia_processed_comment(position + 4));
    v.child_node_id(create_std_string(position + 5));
    v.connection(create_boost_optional_std_pair_std_string_std_string_(position + 6));
    v.properties(create_std_list_dogen_yarn_dia_processed_property(position + 7));
}

processed_object_generator::result_type
processed_object_generator::create(const unsigned int position) {
    processed_object r;
    processed_object_generator::populate(position, r);
    return r;
}

processed_object_generator::result_type*
processed_object_generator::create_ptr(const unsigned int position) {
    processed_object* p = new processed_object();
    processed_object_generator::populate(position, *p);
    return p;
}

processed_object_generator::result_type
processed_object_generator::operator()() {
    return create(position_++);
}

} }
