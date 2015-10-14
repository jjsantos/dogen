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
#ifndef DOGEN_TEST_MODELS_STEREOTYPES_TYPES_IMMUTABLE_ZERO_HPP
#define DOGEN_TEST_MODELS_STEREOTYPES_TYPES_IMMUTABLE_ZERO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/stereotypes/serialization/immutable_zero_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

/**
 * @brief Immutable class with no properties.
 */
class immutable_zero final {
public:
    immutable_zero() = default;
    immutable_zero(const immutable_zero&) = default;
    immutable_zero(immutable_zero&&) = default;
    ~immutable_zero() = default;
    immutable_zero& operator=(const immutable_zero&) = delete;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const immutable_zero& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, immutable_zero& v, unsigned int version);

public:
    bool operator==(const immutable_zero& rhs) const;
    bool operator!=(const immutable_zero& rhs) const {
        return !this->operator==(rhs);
    }

};

} } }

#endif
