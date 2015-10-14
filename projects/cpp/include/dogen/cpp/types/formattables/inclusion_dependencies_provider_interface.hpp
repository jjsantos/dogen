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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_PROVIDER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_INCLUSION_DEPENDENCIES_PROVIDER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Provides all inclusion dependencies for a given Tack element.
 */
template<typename Element>
class inclusion_dependencies_provider_interface {
public:
    inclusion_dependencies_provider_interface() = default;
    inclusion_dependencies_provider_interface(
        const inclusion_dependencies_provider_interface&) = delete;
    inclusion_dependencies_provider_interface(
        inclusion_dependencies_provider_interface&&) = default;
    virtual ~inclusion_dependencies_provider_interface() noexcept = 0;

public:
    /**
     * @brief Name of the formatter for which we are providing the
     * dependencies.
     */
    virtual std::string formatter_name() const = 0;

    /**
     * @brief Provide the inclusion dependencies.
     */
    virtual boost::optional<std::list<std::string> >
    provide(const inclusion_dependencies_builder_factory& f,
        const Element& e) const = 0;
};

template<typename Element>
inclusion_dependencies_provider_interface<Element>::
~inclusion_dependencies_provider_interface() noexcept { }

} } }

#endif
