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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_CONCEPT_FORMATTER_INTERFACE_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_CONCEPT_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/formatters/types/file.hpp"
#include "dogen/cpp/types/formattables/concept_info.hpp"
#include "dogen/cpp/types/formatters/formatter_interface.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class concept_formatter_interface : public formatter_interface {
public:
    concept_formatter_interface() = default;
    concept_formatter_interface(const concept_formatter_interface&) = delete;
    concept_formatter_interface(concept_formatter_interface&&) = default;
    virtual ~concept_formatter_interface() noexcept = 0;

public:
    /**
     * @brief Generate a c++ representation for the concept.
     */
    virtual dogen::formatters::file
    format(const formattables::concept_info& c) const = 0;
};

} } }

#endif
