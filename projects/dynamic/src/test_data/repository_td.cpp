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
#include "dogen/dynamic/test_data/repository_td.hpp"
#include "dogen/dynamic/test_data/field_definition_td.hpp"

namespace {

dogen::dynamic::field_definition
create_dogen_dynamic_field_definition(const unsigned int position) {
    return dogen::dynamic::field_definition_generator::create(position);
}

std::list<dogen::dynamic::field_definition> create_std_list_dogen_dynamic_field_definition(unsigned int position) {
    std::list<dogen::dynamic::field_definition> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_dynamic_field_definition(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, dogen::dynamic::field_definition> create_std_unordered_map_std_string_dogen_dynamic_field_definition(unsigned int position) {
    std::unordered_map<std::string, dogen::dynamic::field_definition> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_dynamic_field_definition(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> > create_std_unordered_map_std_string_std_list_dogen_dynamic_field_definition_(unsigned int position) {
    std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_list_dogen_dynamic_field_definition(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace dynamic {

repository_generator::repository_generator() : position_(0) { }

void repository_generator::
populate(const unsigned int position, result_type& v) {
    v.all_field_definitions(create_std_list_dogen_dynamic_field_definition(position + 0));
    v.field_definitions_by_name(create_std_unordered_map_std_string_dogen_dynamic_field_definition(position + 1));
    v.field_definitions_by_facet_name(create_std_unordered_map_std_string_std_list_dogen_dynamic_field_definition_(position + 2));
    v.field_definitions_by_formatter_name(create_std_unordered_map_std_string_std_list_dogen_dynamic_field_definition_(position + 3));
    v.field_definitions_by_model_name(create_std_unordered_map_std_string_std_list_dogen_dynamic_field_definition_(position + 4));
}

repository_generator::result_type
repository_generator::create(const unsigned int position) {
    repository r;
    repository_generator::populate(position, r);
    return r;
}

repository_generator::result_type*
repository_generator::create_ptr(const unsigned int position) {
    repository* p = new repository();
    repository_generator::populate(position, *p);
    return p;
}

repository_generator::result_type
repository_generator::operator()() {
    return create(position_++);
}

} }
