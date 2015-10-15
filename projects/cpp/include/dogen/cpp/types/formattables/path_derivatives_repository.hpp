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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_PATH_DERIVATIVES_REPOSITORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_PATH_DERIVATIVES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/cpp/types/formattables/path_derivatives.hpp"
#include "dogen/cpp/serialization/formattables/path_derivatives_repository_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class path_derivatives_repository final {
public:
    path_derivatives_repository() = default;
    path_derivatives_repository(const path_derivatives_repository&) = default;
    path_derivatives_repository(path_derivatives_repository&&) = default;
    ~path_derivatives_repository() = default;

public:
    explicit path_derivatives_repository(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& path_derivatives_by_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const path_derivatives_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, path_derivatives_repository& v, unsigned int version);

public:
    const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& path_derivatives_by_name() const;
    std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& path_derivatives_by_name();
    void path_derivatives_by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >& v);
    void path_derivatives_by_name(const std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> >&& v);

public:
    bool operator==(const path_derivatives_repository& rhs) const;
    bool operator!=(const path_derivatives_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(path_derivatives_repository& other) noexcept;
    path_derivatives_repository& operator=(path_derivatives_repository other);

private:
    std::unordered_map<dogen::yarn::name, std::unordered_map<std::string, dogen::cpp::formattables::path_derivatives> > path_derivatives_by_name_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::path_derivatives_repository& lhs,
    dogen::cpp::formattables::path_derivatives_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
