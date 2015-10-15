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
#ifndef DOGEN_YARN_TYPES_TYPE_HPP
#define DOGEN_YARN_TYPES_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/type_visitor.hpp"
#include "dogen/yarn/types/generation_types.hpp"
#include "dogen/yarn/serialization/type_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Represents a type within the type system.
 */
class type {
public:
    type(const type&) = default;

public:
    type();

    virtual ~type() noexcept = 0;

public:
    type(type&& rhs);

public:
    type(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& containing_module);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const type& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, type& v, unsigned int version);

public:
    virtual void accept(const type_visitor& v) const = 0;
    virtual void accept(type_visitor& v) const = 0;
    virtual void accept(const type_visitor& v) = 0;
    virtual void accept(type_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

public:
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

protected:
    bool compare(const type& rhs) const;
public:
    virtual bool equals(const type& other) const = 0;

protected:
    void swap(type& other) noexcept;

private:
    std::string documentation_;
    dogen::dynamic::object extensions_;
    dogen::yarn::name name_;
    dogen::yarn::generation_types generation_type_;
    dogen::yarn::origin_types origin_type_;
    boost::optional<dogen::yarn::name> containing_module_;
};

inline type::~type() noexcept { }

inline bool operator==(const type& lhs, const type& rhs) {
    return lhs.equals(rhs);
}

} }

#endif
