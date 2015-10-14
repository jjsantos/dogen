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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INTEGRATED_FACETS_REPOSITORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INTEGRATED_FACETS_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/cpp/serialization/formattables/integrated_facets_repository_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class integrated_facets_repository final {
public:
    integrated_facets_repository() = default;
    integrated_facets_repository(const integrated_facets_repository&) = default;
    integrated_facets_repository(integrated_facets_repository&&) = default;
    ~integrated_facets_repository() = default;

public:
    explicit integrated_facets_repository(const std::unordered_map<std::string, std::unordered_set<std::string> >& integrated_facets_by_formatter_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const integrated_facets_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, integrated_facets_repository& v, unsigned int version);

public:
    const std::unordered_map<std::string, std::unordered_set<std::string> >& integrated_facets_by_formatter_name() const;
    std::unordered_map<std::string, std::unordered_set<std::string> >& integrated_facets_by_formatter_name();
    void integrated_facets_by_formatter_name(const std::unordered_map<std::string, std::unordered_set<std::string> >& v);
    void integrated_facets_by_formatter_name(const std::unordered_map<std::string, std::unordered_set<std::string> >&& v);

public:
    bool operator==(const integrated_facets_repository& rhs) const;
    bool operator!=(const integrated_facets_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(integrated_facets_repository& other) noexcept;
    integrated_facets_repository& operator=(integrated_facets_repository other);

private:
    std::unordered_map<std::string, std::unordered_set<std::string> > integrated_facets_by_formatter_name_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::integrated_facets_repository& lhs,
    dogen::cpp::formattables::integrated_facets_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
