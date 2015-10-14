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
#include "dogen/tack/test_data/name_td.hpp"
#include "dogen/cpp/test_data/formattables/inclusion_directives_repository_td.hpp"

namespace {

dogen::tack::name
create_dogen_tack_name(const unsigned int position) {
    return dogen::tack::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> > create_std_unordered_map_dogen_tack_name_std_unordered_map_std_string_std_string_(unsigned int position) {
    std::unordered_map<dogen::tack::name, std::unordered_map<std::string, std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_tack_name(position + i), create_std_unordered_map_std_string_std_string(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_directives_repository_generator::inclusion_directives_repository_generator() : position_(0) { }

void inclusion_directives_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.inclusion_directives_by_name(create_std_unordered_map_dogen_tack_name_std_unordered_map_std_string_std_string_(position + 0));
}

inclusion_directives_repository_generator::result_type
inclusion_directives_repository_generator::create(const unsigned int position) {
    inclusion_directives_repository r;
    inclusion_directives_repository_generator::populate(position, r);
    return r;
}

inclusion_directives_repository_generator::result_type*
inclusion_directives_repository_generator::create_ptr(const unsigned int position) {
    inclusion_directives_repository* p = new inclusion_directives_repository();
    inclusion_directives_repository_generator::populate(position, *p);
    return p;
}

inclusion_directives_repository_generator::result_type
inclusion_directives_repository_generator::operator()() {
    return create(position_++);
}

} } }
