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
#ifndef DOGEN_YARN_TYPES_CONCEPT_HPP
#define DOGEN_YARN_TYPES_CONCEPT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/property.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/generation_types.hpp"
#include "dogen/yarn/serialization/concept_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Represents a concept, similar to the C++ definition.
 */
class concept final {
public:
    concept(const concept&) = default;
    ~concept() = default;

public:
    concept();

public:
    concept(concept&& rhs);

public:
    concept(
        const std::list<dogen::yarn::property>& all_properties,
        const std::list<dogen::yarn::property>& local_properties,
        const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties,
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& containing_module,
        const std::list<dogen::yarn::name>& refines,
        const bool is_parent,
        const bool is_child);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const concept& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, concept& v, unsigned int version);

public:
    /**
     * @brief All the properties associated with this type.
     *
     * This is a union of the following sets:
     *
     * @li the set of all properies obtained via inheritance relationships;
     * @li the set of all properies obtained via modeling of concepts, including any refinements;
     * @li the set of all properies directly associated with the type (local).
     *
     * The first and third sets are cached in this object. The second isn't as we do
     * not have a need for it.
     */
    /**@{*/
    const std::list<dogen::yarn::property>& all_properties() const;
    std::list<dogen::yarn::property>& all_properties();
    void all_properties(const std::list<dogen::yarn::property>& v);
    void all_properties(const std::list<dogen::yarn::property>&& v);
    /**@}*/

    /**
     * @brief The set of all properies directly associated with the type.
     */
    /**@{*/
    const std::list<dogen::yarn::property>& local_properties() const;
    std::list<dogen::yarn::property>& local_properties();
    void local_properties(const std::list<dogen::yarn::property>& v);
    void local_properties(const std::list<dogen::yarn::property>&& v);
    /**@}*/

    /**
     * @brief The set of all properies obtained via inheritance, by parent name.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties() const;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties();
    void inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& v);
    void inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >&& v);
    /**@}*/

    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Dynamic extensions for this element.
     */
    /**@{*/
    const dogen::dynamic::object& extensions() const;
    dogen::dynamic::object& extensions();
    void extensions(const dogen::dynamic::object& v);
    void extensions(const dogen::dynamic::object&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     *
     */
    /**@{*/
    const dogen::yarn::name& name() const;
    dogen::yarn::name& name();
    void name(const dogen::yarn::name& v);
    void name(const dogen::yarn::name&& v);
    /**@}*/

    /**
     * @brief What to do with this type in terms of code generation.
     */
    /**@{*/
    dogen::yarn::generation_types generation_type() const;
    void generation_type(const dogen::yarn::generation_types v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::yarn::origin_types origin_type() const;
    void origin_type(const dogen::yarn::origin_types v);
    /**@}*/

    /**
     * @brief Name of the module in which we are contained.
     */
    /**@{*/
    const boost::optional<dogen::yarn::name>& containing_module() const;
    boost::optional<dogen::yarn::name>& containing_module();
    void containing_module(const boost::optional<dogen::yarn::name>& v);
    void containing_module(const boost::optional<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief List of concepts that this concept is a refinement of.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& refines() const;
    std::list<dogen::yarn::name>& refines();
    void refines(const std::list<dogen::yarn::name>& v);
    void refines(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief True if this concept is the parent of one or more concepts, false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief If true, the concept has at least one parent.
     */
    /**@{*/
    bool is_child() const;
    void is_child(const bool v);
    /**@}*/

public:
    bool operator==(const concept& rhs) const;
    bool operator!=(const concept& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(concept& other) noexcept;
    concept& operator=(concept other);

private:
    std::list<dogen::yarn::property> all_properties_;
    std::list<dogen::yarn::property> local_properties_;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> > inherited_properties_;
    std::string documentation_;
    dogen::dynamic::object extensions_;
    dogen::yarn::name name_;
    dogen::yarn::generation_types generation_type_;
    dogen::yarn::origin_types origin_type_;
    boost::optional<dogen::yarn::name> containing_module_;
    std::list<dogen::yarn::name> refines_;
    bool is_parent_;
    bool is_child_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::concept& lhs,
    dogen::yarn::concept& rhs) {
    lhs.swap(rhs);
}

}

#endif
