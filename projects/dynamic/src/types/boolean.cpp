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
#include <boost/io/ios_state.hpp>
#include "dogen/dynamic/io/value_io.hpp"
#include "dogen/dynamic/types/boolean.hpp"

namespace dogen {
namespace dynamic {

boolean::boolean()
    : content_(static_cast<bool>(0)) { }

boolean::boolean(const bool content)
    : dogen::dynamic::value(),
      content_(content) { }

void boolean::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::dynamic::boolean\"" << ", "
      << "\"__parent_0__\": ";
    value::to_stream(s);
    s << ", "
      << "\"content\": " << content_
      << " }";
}

void boolean::swap(boolean& other) noexcept {
    value::swap(other);

    using std::swap;
    swap(content_, other.content_);
}

bool boolean::equals(const dogen::dynamic::value& other) const {
    const boolean* const p(dynamic_cast<const boolean* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool boolean::operator==(const boolean& rhs) const {
    return value::compare(rhs) &&
        content_ == rhs.content_;
}

boolean& boolean::operator=(boolean other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool boolean::content() const {
    return content_;
}

void boolean::content(const bool v) {
    content_ = v;
}

} }
