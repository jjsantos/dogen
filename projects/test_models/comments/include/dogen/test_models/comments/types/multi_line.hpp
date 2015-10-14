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
#ifndef DOGEN_TEST_MODELS_COMMENTS_TYPES_MULTI_LINE_HPP
#define DOGEN_TEST_MODELS_COMMENTS_TYPES_MULTI_LINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/comments/serialization/multi_line_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace comments {

/**
 * @brief first line
 *
 * second line
 * third line with "quote"
 */
class multi_line final {
public:
    multi_line() = default;
    multi_line(const multi_line&) = default;
    multi_line(multi_line&&) = default;
    ~multi_line() = default;
    multi_line& operator=(const multi_line&) = default;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const multi_line& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, multi_line& v, unsigned int version);

public:
    bool operator==(const multi_line& rhs) const;
    bool operator!=(const multi_line& rhs) const {
        return !this->operator==(rhs);
    }

};

} } }

#endif
