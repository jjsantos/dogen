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
#ifndef DOGEN_TACK_TYPES_IDENTIFIER_PARSER_HPP
#define DOGEN_TACK_TYPES_IDENTIFIER_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen/tack/types/location.hpp"
#include "dogen/tack/types/nested_name.hpp"

namespace dogen {
namespace tack {

class identifier_parser {
public:
    identifier_parser(const identifier_parser&) = default;
    ~identifier_parser() = default;
    identifier_parser(identifier_parser&&) = default;
    identifier_parser& operator=(const identifier_parser&) = default;

public:
    identifier_parser();

public:
    /**
     * @brief Initialises the parser.
     *
     * @param modules names of all the top-level modules in the
     * current model.
     * @param external_module_path modules external to the current
     * model
     * @param model_name name of the current model
     */
    identifier_parser(const std::unordered_set<std::string>& modules,
        const location& model_location);

public:
    nested_name parse_name(const std::string& s) const;

private:
    const std::unordered_set<std::string> modules_;
    const location model_location_;
};

} }

#endif
