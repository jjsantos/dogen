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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_DESCENDANT1_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_INHERITANCE_TYPES_DESCENDANT1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/test_models/trivial_inheritance/types/base.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/descendant1_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace trivial_inheritance {

class descendant1 : public dogen::test_models::trivial_inheritance::base {
public:
    descendant1() = default;
    descendant1(const descendant1&) = default;
    descendant1(descendant1&&) = default;
    descendant1& operator=(const descendant1&) = default;

    virtual ~descendant1() noexcept = 0;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const descendant1& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, descendant1& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

protected:
    bool compare(const descendant1& rhs) const;
public:
    virtual bool equals(const dogen::test_models::trivial_inheritance::base& other) const = 0;

protected:
    void swap(descendant1& other) noexcept;

};

inline descendant1::~descendant1() noexcept { }

inline bool operator==(const descendant1& lhs, const descendant1& rhs) {
    return lhs.equals(rhs);
}

} } }

#endif
