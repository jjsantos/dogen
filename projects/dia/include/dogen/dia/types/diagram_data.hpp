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
#ifndef DOGEN_DIA_TYPES_DIAGRAM_DATA_HPP
#define DOGEN_DIA_TYPES_DIAGRAM_DATA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <algorithm>
#include "dogen/dia/types/attribute.hpp"
#include "dogen/dia/serialization/diagram_data_fwd_ser.hpp"

namespace dogen {
namespace dia {

/**
 * @brief Represents a all the data associated with a diagram.
 */
class diagram_data final {
public:
    diagram_data() = default;
    diagram_data(const diagram_data&) = default;
    diagram_data(diagram_data&&) = default;
    ~diagram_data() = default;

public:
    explicit diagram_data(const std::vector<dogen::dia::attribute>& attributes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const diagram_data& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, diagram_data& v, unsigned int version);

public:
    /**
     * @brief All attributes associated with the diagram data.
     */
    /**@{*/
    const std::vector<dogen::dia::attribute>& attributes() const;
    std::vector<dogen::dia::attribute>& attributes();
    void attributes(const std::vector<dogen::dia::attribute>& v);
    void attributes(const std::vector<dogen::dia::attribute>&& v);
    /**@}*/

public:
    bool operator==(const diagram_data& rhs) const;
    bool operator!=(const diagram_data& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(diagram_data& other) noexcept;
    diagram_data& operator=(diagram_data other);

private:
    std::vector<dogen::dia::attribute> attributes_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia::diagram_data& lhs,
    dogen::dia::diagram_data& rhs) {
    lhs.swap(rhs);
}

}

#endif
