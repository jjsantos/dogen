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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_TRAITS_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>

namespace dogen {
namespace cpp {
namespace formatters {

struct traits {
    /**
     * @brief Name of this model.
     */
    static std::string model_name();

    /**
     * @brief Name of the header formatter group.
     */
    static std::string header_formatter_group_name();

    /**
     * @brief Name of the header formatter group.
     */
    static std::string implementation_formatter_group_name();

    /**
     * @brief Name of the includers formatter.
     */
    static std::string includers_formatter_name(const std::string& facet_name);

    static std::string include_cmakelists_formatter_name();
    static std::string source_cmakelists_formatter_name();

    /**
     * @brief Name of the class header formatter.
     */
    static std::string class_header_formatter_name(
        const std::string& facet_name);
};

} } }

#endif
