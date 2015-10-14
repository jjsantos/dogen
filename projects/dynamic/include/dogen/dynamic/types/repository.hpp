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
#ifndef DOGEN_DYNAMIC_TYPES_REPOSITORY_HPP
#define DOGEN_DYNAMIC_TYPES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/dynamic/serialization/repository_fwd_ser.hpp"

namespace dogen {
namespace dynamic {

class repository final {
public:
    repository() = default;
    repository(const repository&) = default;
    repository(repository&&) = default;
    ~repository() = default;

public:
    repository(
        const std::list<dogen::dynamic::field_definition>& all_field_definitions,
        const std::unordered_map<std::string, dogen::dynamic::field_definition>& field_definitions_by_name,
        const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_facet_name,
        const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_formatter_name,
        const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_model_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, repository& v, unsigned int version);

public:
    /**
     * @brief All the field definitions available, without categorisation.
     */
    /**@{*/
    const std::list<dogen::dynamic::field_definition>& all_field_definitions() const;
    std::list<dogen::dynamic::field_definition>& all_field_definitions();
    void all_field_definitions(const std::list<dogen::dynamic::field_definition>& v);
    void all_field_definitions(const std::list<dogen::dynamic::field_definition>&& v);
    /**@}*/

    /**
     * @brief All field definitions by qualified field definition name.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::dynamic::field_definition>& field_definitions_by_name() const;
    std::unordered_map<std::string, dogen::dynamic::field_definition>& field_definitions_by_name();
    void field_definitions_by_name(const std::unordered_map<std::string, dogen::dynamic::field_definition>& v);
    void field_definitions_by_name(const std::unordered_map<std::string, dogen::dynamic::field_definition>&& v);
    /**@}*/

    /**
     * @brief All field definitions for all qualified facet names, for all models.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_facet_name() const;
    std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_facet_name();
    void field_definitions_by_facet_name(const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& v);
    void field_definitions_by_facet_name(const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >&& v);
    /**@}*/

    /**
     * @brief All field definitions for all qualified formatter names, for all models.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_formatter_name() const;
    std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_formatter_name();
    void field_definitions_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& v);
    void field_definitions_by_formatter_name(const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >&& v);
    /**@}*/

    const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_model_name() const;
    std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& field_definitions_by_model_name();
    void field_definitions_by_model_name(const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >& v);
    void field_definitions_by_model_name(const std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> >&& v);

public:
    bool operator==(const repository& rhs) const;
    bool operator!=(const repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(repository& other) noexcept;
    repository& operator=(repository other);

private:
    std::list<dogen::dynamic::field_definition> all_field_definitions_;
    std::unordered_map<std::string, dogen::dynamic::field_definition> field_definitions_by_name_;
    std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> > field_definitions_by_facet_name_;
    std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> > field_definitions_by_formatter_name_;
    std::unordered_map<std::string, std::list<dogen::dynamic::field_definition> > field_definitions_by_model_name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::repository& lhs,
    dogen::dynamic::repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
