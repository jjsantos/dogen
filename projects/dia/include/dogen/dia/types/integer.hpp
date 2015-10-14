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
#ifndef DOGEN_DIA_TYPES_INTEGER_HPP
#define DOGEN_DIA_TYPES_INTEGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/dia/serialization/integer_fwd_ser.hpp"

namespace dogen {
namespace dia {

/**
 * @brief Represents an integer value.
 */
class integer final {
public:
    integer() = default;
    integer(const integer&) = default;
    integer(integer&&) = default;
    ~integer() = default;

public:
    explicit integer(const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const integer& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, integer& v, unsigned int version);

public:
    /**
     * @brief Text representation of an integer value.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const integer& rhs) const;
    bool operator!=(const integer& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(integer& other) noexcept;
    integer& operator=(integer other);

private:
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia::integer& lhs,
    dogen::dia::integer& rhs) {
    lhs.swap(rhs);
}

}

#endif
