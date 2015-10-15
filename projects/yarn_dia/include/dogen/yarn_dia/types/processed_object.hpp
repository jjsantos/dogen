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
#ifndef DOGEN_YARN_DIA_TYPES_PROCESSED_OBJECT_HPP
#define DOGEN_YARN_DIA_TYPES_PROCESSED_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn_dia/types/object_types.hpp"
#include "dogen/yarn_dia/types/processed_comment.hpp"
#include "dogen/yarn_dia/types/processed_property.hpp"
#include "dogen/yarn_dia/serialization/processed_object_fwd_ser.hpp"

namespace dogen {
namespace yarn_dia {

/**
 * @brief Representation of a dia object after first stage processing.
 */
class processed_object final {
public:
    processed_object(const processed_object&) = default;
    ~processed_object() = default;

public:
    processed_object();

public:
    processed_object(processed_object&& rhs);

public:
    processed_object(
        const std::string& id,
        const std::string& name,
        const dogen::yarn_dia::object_types object_type,
        const std::string& stereotype,
        const dogen::yarn_dia::processed_comment& comment,
        const std::string& child_node_id,
        const boost::optional<std::pair<std::string, std::string> >& connection,
        const std::list<dogen::yarn_dia::processed_property>& properties);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const processed_object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, processed_object& v, unsigned int version);

public:
    /**
     * @brief Dia object id.
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the object in dia format.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Type of the dia object.
     */
    /**@{*/
    dogen::yarn_dia::object_types object_type() const;
    void object_type(const dogen::yarn_dia::object_types v);
    /**@}*/

    /**
     * @brief CSV list of stereotypes.
     */
    /**@{*/
    const std::string& stereotype() const;
    std::string& stereotype();
    void stereotype(const std::string& v);
    void stereotype(const std::string&& v);
    /**@}*/

    /**
     * @brief Any comments associated with the object.
     *
     * On the case of a UML note, represents the text of the note.
     */
    /**@{*/
    const dogen::yarn_dia::processed_comment& comment() const;
    dogen::yarn_dia::processed_comment& comment();
    void comment(const dogen::yarn_dia::processed_comment& v);
    void comment(const dogen::yarn_dia::processed_comment&& v);
    /**@}*/

    /**
     * @brief If the object is contained in another object, its node id.
     */
    /**@{*/
    const std::string& child_node_id() const;
    std::string& child_node_id();
    void child_node_id(const std::string& v);
    void child_node_id(const std::string&& v);
    /**@}*/

    /**
     * @brief Connections this object may have with other objects.
     */
    /**@{*/
    const boost::optional<std::pair<std::string, std::string> >& connection() const;
    boost::optional<std::pair<std::string, std::string> >& connection();
    void connection(const boost::optional<std::pair<std::string, std::string> >& v);
    void connection(const boost::optional<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief All properties associated with dia object.
     */
    /**@{*/
    const std::list<dogen::yarn_dia::processed_property>& properties() const;
    std::list<dogen::yarn_dia::processed_property>& properties();
    void properties(const std::list<dogen::yarn_dia::processed_property>& v);
    void properties(const std::list<dogen::yarn_dia::processed_property>&& v);
    /**@}*/

public:
    bool operator==(const processed_object& rhs) const;
    bool operator!=(const processed_object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(processed_object& other) noexcept;
    processed_object& operator=(processed_object other);

private:
    std::string id_;
    std::string name_;
    dogen::yarn_dia::object_types object_type_;
    std::string stereotype_;
    dogen::yarn_dia::processed_comment comment_;
    std::string child_node_id_;
    boost::optional<std::pair<std::string, std::string> > connection_;
    std::list<dogen::yarn_dia::processed_property> properties_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn_dia::processed_object& lhs,
    dogen::yarn_dia::processed_object& rhs) {
    lhs.swap(rhs);
}

}

#endif
