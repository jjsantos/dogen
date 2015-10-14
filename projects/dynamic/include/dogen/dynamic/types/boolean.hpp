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
#ifndef DOGEN_DYNAMIC_TYPES_BOOLEAN_HPP
#define DOGEN_DYNAMIC_TYPES_BOOLEAN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/dynamic/types/value.hpp"
#include "dogen/dynamic/serialization/boolean_fwd_ser.hpp"

namespace dogen {
namespace dynamic {

/**
 * @brief Field can hold a Boolean value.
 */
class boolean final : public dogen::dynamic::value {
public:
    boolean(const boolean&) = default;
    boolean(boolean&&) = default;

public:
    boolean();

    virtual ~boolean() noexcept { }

public:
    explicit boolean(const bool content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const boolean& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, boolean& v, unsigned int version);

public:
    virtual void accept(const value_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(value_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const value_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(value_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    bool content() const;
    void content(const bool v);

public:
    bool operator==(const boolean& rhs) const;
    bool operator!=(const boolean& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::dynamic::value& other) const override;

public:
    void swap(boolean& other) noexcept;
    boolean& operator=(boolean other);

private:
    bool content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::boolean& lhs,
    dogen::dynamic::boolean& rhs) {
    lhs.swap(rhs);
}

}

#endif
