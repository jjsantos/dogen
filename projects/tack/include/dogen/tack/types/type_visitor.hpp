/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_TACK_TYPES_TYPE_VISITOR_HPP
#define DOGEN_TACK_TYPES_TYPE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/tack/types/object_fwd.hpp"
#include "dogen/tack/types/primitive_fwd.hpp"
#include "dogen/tack/types/enumeration_fwd.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Visitor for type
 */
class type_visitor {
public:
    virtual ~type_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::tack::enumeration
     */
    /**@{*/
    virtual void visit(const dogen::tack::enumeration&) const { }
    virtual void visit(const dogen::tack::enumeration&) { }
    virtual void visit(dogen::tack::enumeration&) const { }
    virtual void visit(dogen::tack::enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::tack::object
     */
    /**@{*/
    virtual void visit(const dogen::tack::object&) const { }
    virtual void visit(const dogen::tack::object&) { }
    virtual void visit(dogen::tack::object&) const { }
    virtual void visit(dogen::tack::object&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::tack::primitive
     */
    /**@{*/
    virtual void visit(const dogen::tack::primitive&) const { }
    virtual void visit(const dogen::tack::primitive&) { }
    virtual void visit(dogen::tack::primitive&) const { }
    virtual void visit(dogen::tack::primitive&) { }
    /**@}*/
};

inline type_visitor::~type_visitor() noexcept { }

} }

#endif
