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
#ifndef DOGEN_TACK_TYPES_MODULE_HPP
#define DOGEN_TACK_TYPES_MODULE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/tack/types/name.hpp"
#include "dogen/dynamic/types/object.hpp"
#include "dogen/tack/types/origin_types.hpp"
#include "dogen/tack/types/generation_types.hpp"
#include "dogen/tack/serialization/module_fwd_ser.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Packaging unit.
 *
 * Aggregates a group of logically related types into a unit.
 */
class module final {
public:
    module(const module&) = default;
    ~module() = default;

public:
    module();

public:
    module(module&& rhs);

public:
    module(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::tack::name& name,
        const dogen::tack::generation_types generation_type,
        const dogen::tack::origin_types origin_type,
        const boost::optional<dogen::tack::name>& containing_module,
        const std::list<dogen::tack::name>& members);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const module& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, module& v, unsigned int version);

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
    const dogen::tack::name& name() const;
    dogen::tack::name& name();
    void name(const dogen::tack::name& v);
    void name(const dogen::tack::name&& v);
    /**@}*/

    /**
     * @brief What to do with this type in terms of code generation.
     */
    /**@{*/
    dogen::tack::generation_types generation_type() const;
    void generation_type(const dogen::tack::generation_types v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::tack::origin_types origin_type() const;
    void origin_type(const dogen::tack::origin_types v);
    /**@}*/

    /**
     * @brief Name of the module in which we are contained.
     */
    /**@{*/
    const boost::optional<dogen::tack::name>& containing_module() const;
    boost::optional<dogen::tack::name>& containing_module();
    void containing_module(const boost::optional<dogen::tack::name>& v);
    void containing_module(const boost::optional<dogen::tack::name>&& v);
    /**@}*/

    /**
     * @brief All the model elements contained in this module.
     */
    /**@{*/
    const std::list<dogen::tack::name>& members() const;
    std::list<dogen::tack::name>& members();
    void members(const std::list<dogen::tack::name>& v);
    void members(const std::list<dogen::tack::name>&& v);
    /**@}*/

public:
    bool operator==(const module& rhs) const;
    bool operator!=(const module& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(module& other) noexcept;
    module& operator=(module other);

private:
    std::string documentation_;
    dogen::dynamic::object extensions_;
    dogen::tack::name name_;
    dogen::tack::generation_types generation_type_;
    dogen::tack::origin_types origin_type_;
    boost::optional<dogen::tack::name> containing_module_;
    std::list<dogen::tack::name> members_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::tack::module& lhs,
    dogen::tack::module& rhs) {
    lhs.swap(rhs);
}

}

#endif
