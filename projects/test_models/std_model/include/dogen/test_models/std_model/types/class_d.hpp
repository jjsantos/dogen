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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_D_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_CLASS_D_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/test_models/std_model/types/class_a.hpp"
#include "dogen/test_models/std_model/types/pkg1/class_c.hpp"
#include "dogen/test_models/std_model/serialization/class_d_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class class_d final {
public:
    class_d() = default;
    class_d(const class_d&) = default;
    class_d(class_d&&) = default;
    ~class_d() = default;

public:
    class_d(
        const std::list<std::string>& prop_0,
        const std::list<dogen::test_models::std_model::class_a>& prop_1,
        const std::list<dogen::test_models::std_model::pkg1::class_c>& prop_2,
        const std::list<unsigned int>& prop_3,
        const std::list<dogen::test_models::std_model::class_a>& prop_4,
        const std::list<std::list<unsigned int> >& prop_5);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_d& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_d& v, unsigned int version);

public:
    const std::list<std::string>& prop_0() const;
    std::list<std::string>& prop_0();
    void prop_0(const std::list<std::string>& v);
    void prop_0(const std::list<std::string>&& v);

    const std::list<dogen::test_models::std_model::class_a>& prop_1() const;
    std::list<dogen::test_models::std_model::class_a>& prop_1();
    void prop_1(const std::list<dogen::test_models::std_model::class_a>& v);
    void prop_1(const std::list<dogen::test_models::std_model::class_a>&& v);

    const std::list<dogen::test_models::std_model::pkg1::class_c>& prop_2() const;
    std::list<dogen::test_models::std_model::pkg1::class_c>& prop_2();
    void prop_2(const std::list<dogen::test_models::std_model::pkg1::class_c>& v);
    void prop_2(const std::list<dogen::test_models::std_model::pkg1::class_c>&& v);

    const std::list<unsigned int>& prop_3() const;
    std::list<unsigned int>& prop_3();
    void prop_3(const std::list<unsigned int>& v);
    void prop_3(const std::list<unsigned int>&& v);

    const std::list<dogen::test_models::std_model::class_a>& prop_4() const;
    std::list<dogen::test_models::std_model::class_a>& prop_4();
    void prop_4(const std::list<dogen::test_models::std_model::class_a>& v);
    void prop_4(const std::list<dogen::test_models::std_model::class_a>&& v);

    const std::list<std::list<unsigned int> >& prop_5() const;
    std::list<std::list<unsigned int> >& prop_5();
    void prop_5(const std::list<std::list<unsigned int> >& v);
    void prop_5(const std::list<std::list<unsigned int> >&& v);

public:
    bool operator==(const class_d& rhs) const;
    bool operator!=(const class_d& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_d& other) noexcept;
    class_d& operator=(class_d other);

private:
    std::list<std::string> prop_0_;
    std::list<dogen::test_models::std_model::class_a> prop_1_;
    std::list<dogen::test_models::std_model::pkg1::class_c> prop_2_;
    std::list<unsigned int> prop_3_;
    std::list<dogen::test_models::std_model::class_a> prop_4_;
    std::list<std::list<unsigned int> > prop_5_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::class_d& lhs,
    dogen::test_models::std_model::class_d& rhs) {
    lhs.swap(rhs);
}

}

#endif
