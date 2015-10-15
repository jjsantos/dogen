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
#ifndef DOGEN_YARN_TYPES_RESOLVER_HPP
#define DOGEN_YARN_TYPES_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/concept.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Resolves type references within a model.
 *
 * Properties may come in from transformation missing information in
 * their names - such as the model name, etc. The resolver fills in
 * the missing gaps.
 *
 * The resolver is also responsible for making sure that all
 * references to types (e.g. names) can be resolved to a type in the
 * model.
 */
class resolver {
public:
    resolver() = delete;
    resolver(const resolver&) = default;
    ~resolver() = default;
    resolver(resolver&&) = default;
    resolver& operator=(const resolver&) = default;

public:
    /**
     * @brief Initialises resolver to resolve model m.
     *
     * @param model to resolve.
     *
     * @pre Model must continue to live until resolution has been
     * completed.
     */
    explicit resolver(model& m);

private:
    /**
     * @brief Resolves a partially formed name into a full name.
     */
    name resolve_partial_type(const name& n) const;

    /**
     * @brief Resolves all references contained in a nested name.
     */
    void resolve_partial_type(nested_name& nn) const;

    /**
     * @brief Resolves all references to types in the supplied properties.
     */
    void resolve_properties(const name& owner, std::list<property>& p) const;

    /**
     * @brief Validates the inheritance graph for the object.
     *
     * @note should really be moved to validator.
     */
    void validate_inheritance_graph(const object& ao) const;

    /**
     * @brief Ensures that all concepts refined by the current concept
     * are defined in the model.
     *
     * @note should really be moved to validator.
     */
    void validate_refinements(const concept& c) const;

    /**
     * @brief Resolution must not yet have taken place.
     */
    void require_not_has_resolved() const;

    /**
     * @brief Resolve all concepts.
     */
    void resolve_concepts();

    /**
     * @brief Resolve all objects.
     */
    void resolve_objects();

public:
    /**
     * @brief Returns true if resolution has already been performed,
     * false otherwise.
     */
    bool has_resolved() const { return has_resolved_; }

    /**
     * @brief Resolve all references to types within model.
     *
     * @pre Resolution has not been performed yet.
     */
    void resolve();

private:
    model& model_;
    bool has_resolved_;
};

} }

#endif
