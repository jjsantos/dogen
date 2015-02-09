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
#include <boost/algorithm/string.hpp>
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/cpp/io/settings/cpp_settings_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {
namespace settings {

std::ostream& operator<<(std::ostream& s, const cpp_settings& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::settings::cpp_settings\"" << ", "
      << "\"enabled\": " << v.enabled() << ", "
      << "\"split_project\": " << v.split_project() << ", "
      << "\"project_directory\": " << "\"" << tidy_up_string(v.project_directory()) << "\"" << ", "
      << "\"source_directory\": " << "\"" << tidy_up_string(v.source_directory()) << "\"" << ", "
      << "\"include_directory\": " << "\"" << tidy_up_string(v.include_directory()) << "\"" << ", "
      << "\"header_file_extension\": " << "\"" << tidy_up_string(v.header_file_extension()) << "\"" << ", "
      << "\"implementation_file_extension\": " << "\"" << tidy_up_string(v.implementation_file_extension()) << "\"" << ", "
      << "\"enable_facet_folders\": " << v.enable_facet_folders() << ", "
      << "\"enable_unique_file_names\": " << v.enable_unique_file_names()
      << " }";
    return(s);
}

} } }