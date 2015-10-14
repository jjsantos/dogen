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
#ifndef DOGEN_DYNAMIC_TEST_MOCK_FIELD_DEFINITION_FACTORY_HPP
#define DOGEN_DYNAMIC_TEST_MOCK_FIELD_DEFINITION_FACTORY_HPP

#include <list>
#include "dogen/dynamic/types/value_types.hpp"
#include "dogen/dynamic/types/field_definition.hpp"

namespace dogen {
namespace dynamic {
namespace test {

/**
 * @brief Generates field definitions.
 */
class mock_field_definition_factory {
private:
    /**
     * @brief Creat the containing namespaces field.
     */
    field_definition containing_namespaces() const;

    /**
     * @brief Creat the copyright notice field.
     */
    field_definition copyright_notice() const;

    /**
     * @brief Create the licence name field.
     */
    field_definition licence_name() const;

    /**
     * @brief Create the comment field.
     */
    field_definition create_comment() const;

    /**
     * @brief Create the identity attribute field.
     */
    field_definition create_identity_attribute() const;

public:
    /**
     * @brief Creates a set of canned field definitions, needed for
     * testing.
     */
    std::list<field_definition> make_canned_field_definitions() const;

    /**
     * @brief Creates a field definition with most values set to
     * sensible defaults.
     */
    field_definition make_field_definition(const std::string n,
        value_types vt = value_types::text) const;
};

} } }

#endif
