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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/cpp/serialization/formattables/formatter_properties_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

class formatter_properties final {
public:
    formatter_properties(const formatter_properties&) = default;
    ~formatter_properties() = default;

public:
    formatter_properties();

public:
    formatter_properties(formatter_properties&& rhs);

public:
    formatter_properties(
        const bool enabled,
        const boost::filesystem::path& file_path,
        const boost::optional<std::string>& header_guard,
        const std::list<std::string>& inclusion_dependencies,
        const std::unordered_set<std::string>& integrated_facets);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const formatter_properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, formatter_properties& v, unsigned int version);

public:
    bool enabled() const;
    void enabled(const bool v);

    const boost::filesystem::path& file_path() const;
    boost::filesystem::path& file_path();
    void file_path(const boost::filesystem::path& v);
    void file_path(const boost::filesystem::path&& v);

    const boost::optional<std::string>& header_guard() const;
    boost::optional<std::string>& header_guard();
    void header_guard(const boost::optional<std::string>& v);
    void header_guard(const boost::optional<std::string>&& v);

    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);

    const std::unordered_set<std::string>& integrated_facets() const;
    std::unordered_set<std::string>& integrated_facets();
    void integrated_facets(const std::unordered_set<std::string>& v);
    void integrated_facets(const std::unordered_set<std::string>&& v);

public:
    bool operator==(const formatter_properties& rhs) const;
    bool operator!=(const formatter_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formatter_properties& other) noexcept;
    formatter_properties& operator=(formatter_properties other);

private:
    bool enabled_;
    boost::filesystem::path file_path_;
    boost::optional<std::string> header_guard_;
    std::list<std::string> inclusion_dependencies_;
    std::unordered_set<std::string> integrated_facets_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::formatter_properties& lhs,
    dogen::cpp::formattables::formatter_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
