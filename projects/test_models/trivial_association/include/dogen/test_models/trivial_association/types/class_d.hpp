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
#ifndef DOGEN_TEST_MODELS_TRIVIAL_ASSOCIATION_TYPES_CLASS_D_HPP
#define DOGEN_TEST_MODELS_TRIVIAL_ASSOCIATION_TYPES_CLASS_D_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/trivial_association/serialization/class_d_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace trivial_association {

class class_d final {
public:
    class_d() = default;
    class_d(const class_d&) = default;
    class_d(class_d&&) = default;
    ~class_d() = default;
    class_d& operator=(const class_d&) = default;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_d& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_d& v, unsigned int version);

public:
    bool operator==(const class_d& rhs) const;
    bool operator!=(const class_d& rhs) const {
        return !this->operator==(rhs);
    }

};

} } }

#endif
