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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_ASSOCIATION_TYPES_CLASS_B_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_ASSOCIATION_TYPES_CLASS_B_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/trivial_association/types/class_a.hpp"
#include "dogen/test_models/trivial_association/serialization/class_b_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace trivial_association {

class class_b final {
public:
    class_b() = default;
    class_b(const class_b&) = default;
    class_b(class_b&&) = default;
    ~class_b() = default;

public:
    explicit class_b(const dogen::test_models::trivial_association::class_a& prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_b& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_b& v, unsigned int version);

public:
    const dogen::test_models::trivial_association::class_a& prop_0() const;
    dogen::test_models::trivial_association::class_a& prop_0();
    void prop_0(const dogen::test_models::trivial_association::class_a& v);
    void prop_0(const dogen::test_models::trivial_association::class_a&& v);

public:
    bool operator==(const class_b& rhs) const;
    bool operator!=(const class_b& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_b& other) noexcept;
    class_b& operator=(class_b other);

private:
    dogen::test_models::trivial_association::class_a prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::trivial_association::class_b& lhs,
    dogen::test_models::trivial_association::class_b& rhs) {
    lhs.swap(rhs);
}

}

#endif
