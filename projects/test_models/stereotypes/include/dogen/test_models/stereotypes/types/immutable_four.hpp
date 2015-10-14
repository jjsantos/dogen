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
#ifndef DOGEN_TEST_MODELS_STEREOTYPES_TYPES_IMMUTABLE_FOUR_HPP
#define DOGEN_TEST_MODELS_STEREOTYPES_TYPES_IMMUTABLE_FOUR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/stereotypes/types/value.hpp"
#include "dogen/test_models/stereotypes/types/immutable_one_primitive.hpp"
#include "dogen/test_models/stereotypes/serialization/immutable_four_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

/**
 * @brief Immutable class with non-immutable and immutable pods as properties.
 */
class immutable_four final {
public:
    immutable_four(const immutable_four&) = default;
    immutable_four(immutable_four&&) = default;
    ~immutable_four() = default;
    immutable_four& operator=(const immutable_four&) = delete;

public:
    immutable_four();

public:
    immutable_four(
        const bool prop_0,
        const std::string& prop_1,
        const dogen::test_models::stereotypes::value& prop_2,
        const dogen::test_models::stereotypes::immutable_one_primitive& prop_3);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const immutable_four& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, immutable_four& v, unsigned int version);

public:
    bool prop_0() const;

    const std::string& prop_1() const;

    const dogen::test_models::stereotypes::value& prop_2() const;

    const dogen::test_models::stereotypes::immutable_one_primitive& prop_3() const;

public:
    bool operator==(const immutable_four& rhs) const;
    bool operator!=(const immutable_four& rhs) const {
        return !this->operator==(rhs);
    }

private:
    bool prop_0_;
    std::string prop_1_;
    dogen::test_models::stereotypes::value prop_2_;
    dogen::test_models::stereotypes::immutable_one_primitive prop_3_;
};

} } }

#endif
