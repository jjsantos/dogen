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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen/stitch/io/stitching_settings_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<boost::filesystem::path>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << "\"" << (*v).generic_string() << "\"";
    else
        s << "\"data\": ""\"<empty>\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace stitch {

std::ostream& operator<<(std::ostream& s, const stitching_settings& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::stitch::stitching_settings\"" << ", "
      << "\"stream_variable_name\": " << "\"" << tidy_up_string(v.stream_variable_name()) << "\"" << ", "
      << "\"template_path\": " << v.template_path() << ", "
      << "\"output_path\": " << v.output_path() << ", "
      << "\"relative_output_directory\": " << v.relative_output_directory() << ", "
      << "\"inclusion_dependencies\": " << v.inclusion_dependencies() << ", "
      << "\"containing_namespaces\": " << v.containing_namespaces()
      << " }";
    return(s);
}

} }
