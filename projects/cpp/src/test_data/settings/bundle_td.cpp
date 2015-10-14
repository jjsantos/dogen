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
#include "dogen/cpp/test_data/settings/bundle_td.hpp"
#include "dogen/formatters/test_data/general_settings_td.hpp"
#include "dogen/cpp/test_data/settings/aspect_settings_td.hpp"
#include "dogen/cpp/test_data/settings/opaque_settings_td.hpp"

namespace {

dogen::formatters::general_settings
create_dogen_formatters_general_settings(const unsigned int position) {
    return dogen::formatters::general_settings_generator::create(position);
}

boost::optional<dogen::formatters::general_settings>
create_boost_optional_dogen_formatters_general_settings(unsigned int position) {
    boost::optional<dogen::formatters::general_settings> r(
        create_dogen_formatters_general_settings(position));
    return r;
}

dogen::cpp::settings::aspect_settings
create_dogen_cpp_settings_aspect_settings(const unsigned int position) {
    return dogen::cpp::settings::aspect_settings_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::settings::opaque_settings*
create_dogen_cpp_settings_opaque_settings_ptr(const unsigned int position) {
    return dogen::cpp::settings::opaque_settings_generator::create_ptr(position);
}

boost::shared_ptr<dogen::cpp::settings::opaque_settings>
create_boost_shared_ptr_dogen_cpp_settings_opaque_settings(unsigned int position) {
    boost::shared_ptr<dogen::cpp::settings::opaque_settings> r(
        create_dogen_cpp_settings_opaque_settings_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_cpp_settings_opaque_settings_(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_cpp_settings_opaque_settings(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace settings {

bundle_generator::bundle_generator() : position_(0) { }

void bundle_generator::
populate(const unsigned int position, result_type& v) {
    v.general_settings(create_boost_optional_dogen_formatters_general_settings(position + 0));
    v.aspect_settings(create_dogen_cpp_settings_aspect_settings(position + 1));
    v.opaque_settings(create_std_unordered_map_std_string_boost_shared_ptr_dogen_cpp_settings_opaque_settings_(position + 2));
}

bundle_generator::result_type
bundle_generator::create(const unsigned int position) {
    bundle r;
    bundle_generator::populate(position, r);
    return r;
}

bundle_generator::result_type*
bundle_generator::create_ptr(const unsigned int position) {
    bundle* p = new bundle();
    bundle_generator::populate(position, *p);
    return p;
}

bundle_generator::result_type
bundle_generator::operator()() {
    return create(position_++);
}

} } }
