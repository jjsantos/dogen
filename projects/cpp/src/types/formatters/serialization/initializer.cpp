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
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/includers_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/enum_header_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/registrar_header_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/registrar_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/forward_declarations_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/initializer.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

void initializer::initialize(registrar& rg) {
    initialise_formatter<includers_formatter>(rg, traits::facet_name());
    initialise_formatter<class_header_formatter>(rg);
    initialise_formatter<class_implementation_formatter>(rg);
    initialise_formatter<enum_header_formatter>(rg);
    initialise_formatter<registrar_header_formatter>(rg);
    initialise_formatter<registrar_implementation_formatter>(rg);
    initialise_formatter<forward_declarations_formatter>(rg);
}

} } } }
