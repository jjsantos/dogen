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
#include "dogen/cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "dogen/cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "dogen/cpp/types/formatters/types/initializer.hpp"
#include "dogen/cpp/types/formatters/hash/initializer.hpp"
#include "dogen/cpp/types/formatters/odb/initializer.hpp"
#include "dogen/cpp/types/formatters/io/initializer.hpp"
#include "dogen/cpp/types/formatters/test_data/initializer.hpp"
#include "dogen/cpp/types/formatters/serialization/initializer.hpp"
#include "dogen/cpp/types/formatters/initializer.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

void initializer::initialize(registrar& rg) {
    initialise_formatter<include_cmakelists_formatter>(rg);
    initialise_formatter<source_cmakelists_formatter>(rg);

    types::initializer::initialize(rg);
    hash::initializer::initialize(rg);
    odb::initializer::initialize(rg);
    io::initializer::initialize(rg);
    test_data::initializer::initialize(rg);
    serialization::initializer::initialize(rg);
}

} } }
