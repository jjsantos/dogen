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
#include "dogen/cpp/test_data/formattables/entity_td.hpp"
#include "dogen/cpp/test_data/formattables/concept_info_td.hpp"
#include "dogen/cpp/test_data/formattables/property_info_td.hpp"

namespace {

dogen::cpp::formattables::property_info
create_dogen_cpp_formattables_property_info(const unsigned int position) {
    return dogen::cpp::formattables::property_info_generator::create(position);
}

std::list<dogen::cpp::formattables::property_info> create_std_list_dogen_cpp_formattables_property_info(unsigned int position) {
    std::list<dogen::cpp::formattables::property_info> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_formattables_property_info(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

concept_info_generator::concept_info_generator() : position_(0) { }

void concept_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::formattables::entity_generator::populate(position, v);
    v.properties(create_std_list_dogen_cpp_formattables_property_info(position + 0));
    v.all_properties(create_std_list_dogen_cpp_formattables_property_info(position + 1));
}

concept_info_generator::result_type
concept_info_generator::create(const unsigned int position) {
    concept_info r;
    concept_info_generator::populate(position, r);
    return r;
}

concept_info_generator::result_type*
concept_info_generator::create_ptr(const unsigned int position) {
    concept_info* p = new concept_info();
    concept_info_generator::populate(position, *p);
    return p;
}

concept_info_generator::result_type
concept_info_generator::operator()() {
    return create(position_++);
}

} } }
