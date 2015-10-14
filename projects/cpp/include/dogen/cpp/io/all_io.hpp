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
#ifndef DOGEN_CPP_IO_ALL_IO_HPP
#define DOGEN_CPP_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/cpp/io/settings/bundle_io.hpp"
#include "dogen/cpp/io/formattables/entity_io.hpp"
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/io/settings/odb_settings_io.hpp"
#include "dogen/cpp/io/formattables/enum_info_io.hpp"
#include "dogen/cpp/io/settings/path_settings_io.hpp"
#include "dogen/cpp/io/formattables/class_info_io.hpp"
#include "dogen/cpp/io/formattables/formattable_io.hpp"
#include "dogen/cpp/io/formattables/parent_info_io.hpp"
#include "dogen/cpp/io/settings/aspect_settings_io.hpp"
#include "dogen/cpp/io/settings/opaque_settings_io.hpp"
#include "dogen/cpp/io/formattables/concept_info_io.hpp"
#include "dogen/cpp/io/formattables/origin_types_io.hpp"
#include "dogen/cpp/io/formattables/visitor_info_io.hpp"
#include "dogen/cpp/io/formattables/property_info_io.hpp"
#include "dogen/cpp/io/settings/bundle_repository_io.hpp"
#include "dogen/cpp/io/formattables/exception_info_io.hpp"
#include "dogen/cpp/io/formattables/includers_info_io.hpp"
#include "dogen/cpp/io/formattables/namespace_info_io.hpp"
#include "dogen/cpp/io/formattables/primitive_info_io.hpp"
#include "dogen/cpp/io/formattables/registrar_info_io.hpp"
#include "dogen/cpp/io/formattables/cmakelists_info_io.hpp"
#include "dogen/cpp/io/formattables/enumerator_info_io.hpp"
#include "dogen/cpp/io/formattables/nested_type_info_io.hpp"
#include "dogen/cpp/io/formattables/odb_options_info_io.hpp"
#include "dogen/cpp/io/formattables/path_derivatives_io.hpp"
#include "dogen/cpp/io/formattables/visited_type_info_io.hpp"
#include "dogen/cpp/io/formattables/formatter_properties_io.hpp"
#include "dogen/cpp/io/settings/directory_names_settings_io.hpp"
#include "dogen/cpp/io/formattables/enablement_repository_io.hpp"
#include "dogen/cpp/io/settings/inclusion_directive_settings_io.hpp"
#include "dogen/cpp/io/formattables/forward_declarations_info_io.hpp"
#include "dogen/cpp/io/settings/inclusion_directives_settings_io.hpp"
#include "dogen/cpp/io/formattables/path_derivatives_repository_io.hpp"
#include "dogen/cpp/io/formattables/global_enablement_properties_io.hpp"
#include "dogen/cpp/io/formattables/integrated_facets_repository_io.hpp"
#include "dogen/cpp/io/formattables/formatter_properties_repository_io.hpp"
#include "dogen/cpp/io/formattables/inclusion_directives_repository_io.hpp"
#include "dogen/cpp/io/formattables/inclusion_dependencies_repository_io.hpp"

#endif
