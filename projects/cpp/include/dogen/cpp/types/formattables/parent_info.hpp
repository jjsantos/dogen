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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_PARENT_INFO_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_PARENT_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/cpp/types/formattables/property_info.hpp"
#include "dogen/cpp/serialization/formattables/parent_info_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Represents the details for a parent class.
 */
class parent_info final {
public:
    parent_info() = default;
    parent_info(const parent_info&) = default;
    parent_info(parent_info&&) = default;
    ~parent_info() = default;

public:
    parent_info(
        const std::string& name,
        const std::string& qualified_name,
        const std::list<std::string>& namespaces,
        const std::list<dogen::cpp::formattables::property_info>& properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const parent_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, parent_info& v, unsigned int version);

public:
    /**
     * @brief Name of the entity.
     *
     * Must be valid according to the rules for C++ names.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Fully qualified name of the entity.
     */
    /**@{*/
    const std::string& qualified_name() const;
    std::string& qualified_name();
    void qualified_name(const std::string& v);
    void qualified_name(const std::string&& v);
    /**@}*/

    /**
     * @brief List of all namespaces containing the class.
     */
    /**@{*/
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Properties of the class.
     */
    /**@{*/
    const std::list<dogen::cpp::formattables::property_info>& properties() const;
    std::list<dogen::cpp::formattables::property_info>& properties();
    void properties(const std::list<dogen::cpp::formattables::property_info>& v);
    void properties(const std::list<dogen::cpp::formattables::property_info>&& v);
    /**@}*/

public:
    bool operator==(const parent_info& rhs) const;
    bool operator!=(const parent_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(parent_info& other) noexcept;
    parent_info& operator=(parent_info other);

private:
    std::string name_;
    std::string qualified_name_;
    std::list<std::string> namespaces_;
    std::list<dogen::cpp::formattables::property_info> properties_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::formattables::parent_info& lhs,
    dogen::cpp::formattables::parent_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
