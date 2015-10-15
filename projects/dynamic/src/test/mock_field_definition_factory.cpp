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
#include "dogen/dynamic/test/mock_field_definition_factory.hpp"

namespace dogen {
namespace dynamic {
namespace test {

field_definition mock_field_definition_factory::containing_namespaces() const {
    field_definition r;
    r.name().simple("containing_namespaces");
    r.name().qualified("containing_namespaces");
    r.ownership_hierarchy().model_name("stitch");
    r.value_type(value_types::text);
    r.definition_type(field_definition_types::instance);
    r.scope(scope_types::not_applicable);
    return r;
}

field_definition mock_field_definition_factory::copyright_notice() const {
    field_definition r;
    r.name().simple("copyright_notice");
    r.name().qualified("copyright_notice");
    r.ownership_hierarchy().model_name("formatters");
    r.value_type(value_types::text);
    r.definition_type(field_definition_types::instance);
    r.scope(scope_types::not_applicable);
    return r;
}

field_definition mock_field_definition_factory::licence_name() const {
    field_definition r;
    r.name().simple("licence_name");
    r.name().qualified("licence_name");
    r.ownership_hierarchy().model_name("formatters");
    r.value_type(value_types::text);
    r.definition_type(field_definition_types::instance);
    r.scope(scope_types::not_applicable);
    return r;
}

field_definition mock_field_definition_factory::create_comment() const {
    field_definition r;
    r.name().simple("comment");
    r.name().qualified("dia.comment");
    r.ownership_hierarchy().model_name("yarn_dia");
    r.value_type(value_types::text);
    r.definition_type(field_definition_types::instance);
    r.scope(scope_types::not_applicable);
    return r;
}

field_definition mock_field_definition_factory::
create_identity_attribute() const {
    field_definition r;
    r.name().simple("identity_attribute");
    r.name().qualified("dia.identity_attribute");
    r.ownership_hierarchy().model_name("yarn_dia");
    r.value_type(value_types::text);
    r.definition_type(field_definition_types::instance);
    r.scope(scope_types::property);
    return r;
}

std::list<field_definition> mock_field_definition_factory::
make_canned_field_definitions() const {
    std::list<field_definition> r;
    r.push_back(create_comment());
    r.push_back(create_identity_attribute());
    r.push_back(licence_name());
    r.push_back(copyright_notice());
    r.push_back(containing_namespaces());
    return r;
}

field_definition mock_field_definition_factory::
make_field_definition(const std::string n, value_types vt) const {
    dogen::dynamic::field_definition r;
    r.name().simple(n);
    r.name().qualified(n);
    r.value_type(vt);
    r.definition_type(field_definition_types::instance);
    r.scope(scope_types::any);
    return r;
}

} } }
