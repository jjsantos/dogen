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
#ifndef DOGEN_YARN_TYPES_ALL_MODEL_ITEMS_TRAVERSAL_HPP
#define DOGEN_YARN_TYPES_ALL_MODEL_ITEMS_TRAVERSAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/model.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/module.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Performs a traversal across all types in a domain model.
 */
/**@{*/
template<typename TraversalVisitor> inline
void all_model_items_traversal(const model& m, const TraversalVisitor& v) {
    for (const auto& pair : m.modules())
        v(pair.second);

    for (const auto& pair : m.concepts())
        v(pair.second);

    for (const auto& pair : m.primitives())
        v(pair.second);

    for (const auto& pair : m.enumerations())
        v(pair.second);

    for (const auto& pair : m.objects())
        v(pair.second);
}

template<typename TraversalVisitor> inline
void all_model_items_traversal(const model& m, TraversalVisitor& v) {
    for (auto& pair : m.modules())
        v(pair.second);

    for (auto& pair : m.concepts())
        v(pair.second);

    for (auto& pair : m.primitives())
        v(pair.second);

    for (auto& pair : m.enumerations())
        v(pair.second);

    for (auto& pair : m.objects())
        v(pair.second);
}

template<typename TraversalVisitor> inline
void all_model_items_traversal(model& m, TraversalVisitor& v) {
    for (auto& pair : m.modules())
        v(pair.second);

    for (auto& pair : m.concepts())
        v(pair.second);

    for (auto& pair : m.primitives())
        v(pair.second);

    for (auto& pair : m.enumerations())
        v(pair.second);

    for (auto& pair : m.objects())
        v(pair.second);
}

/**@}*/

} }

#endif
