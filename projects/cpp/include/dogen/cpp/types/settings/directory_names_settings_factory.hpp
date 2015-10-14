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
#ifndef DOGEN_CPP_TYPES_SETTINGS_DIRECTORY_NAMES_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_DIRECTORY_NAMES_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/cpp/types/settings/directory_names_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class directory_names_settings_factory {
public:
    explicit directory_names_settings_factory(const dynamic::repository& rp);

private:
    struct fields {
        dynamic::field_definition include_directory_name;
        dynamic::field_definition source_directory_name;
    };

    fields setup_fields(const dynamic::repository& rp) const;

public:
    directory_names_settings make(const dynamic::object& o) const;

private:
    const fields fields_;
};

} } }

#endif
