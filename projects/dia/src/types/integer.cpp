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
#include "dogen/dia/types/integer.hpp"

namespace dogen {
namespace dia {

integer::integer(const std::string& value)
    : value_(value) { }

void integer::swap(integer& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

bool integer::operator==(const integer& rhs) const {
    return value_ == rhs.value_;
}

integer& integer::operator=(integer other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& integer::value() const {
    return value_;
}

std::string& integer::value() {
    return value_;
}

void integer::value(const std::string& v) {
    value_ = v;
}

void integer::value(const std::string&& v) {
    value_ = std::move(v);
}

} }
