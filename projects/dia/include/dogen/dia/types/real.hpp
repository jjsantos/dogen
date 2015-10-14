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
#ifndef DOGEN_DIA_TYPES_REAL_HPP
#define DOGEN_DIA_TYPES_REAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/dia/serialization/real_fwd_ser.hpp"

namespace dogen {
namespace dia {

/**
 * @brief Represents a real value.
 */
class real final {
public:
    real() = default;
    real(const real&) = default;
    real(real&&) = default;
    ~real() = default;

public:
    explicit real(const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const real& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, real& v, unsigned int version);

public:
    /**
     * @brief Text representation of a real value.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const real& rhs) const;
    bool operator!=(const real& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(real& other) noexcept;
    real& operator=(real other);

private:
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia::real& lhs,
    dogen::dia::real& rhs) {
    lhs.swap(rhs);
}

}

#endif
