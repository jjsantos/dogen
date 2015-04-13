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
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/types/forward_declarations_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

dynamic::schema::ownership_hierarchy
forward_declarations_formatter::ownership_hierarchy() const {
    static dynamic::schema::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            traits::forward_declarations_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types forward_declarations_formatter::file_type() const {
    return file_types::cpp_header;
}

void forward_declarations_formatter::register_inclusion_dependencies_provider(
    expansion::registrar& /*rg*/) const {
}

dogen::formatters::file forward_declarations_formatter::
format(const formattables::forward_declarations_info& /*fd*/) const {
    dogen::formatters::file r;
    return r;
}

} } } }