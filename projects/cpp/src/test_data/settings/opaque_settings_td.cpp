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
#include "dogen/cpp/test_data/settings/odb_settings_td.hpp"
#include "dogen/cpp/test_data/settings/opaque_settings_td.hpp"

namespace dogen {
namespace cpp {
namespace settings {

void opaque_settings_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

opaque_settings_generator::result_type*
opaque_settings_generator::create_ptr(const unsigned int position) {
    return dogen::cpp::settings::odb_settings_generator::create_ptr(position);
}

} } }
