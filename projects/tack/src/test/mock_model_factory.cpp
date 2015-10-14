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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include"dogen/utility/log/logger.hpp"
#include "dogen/utility/exception/utility_exception.hpp"
#include "dogen/dynamic/types/value_factory.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/tack/test/building_error.hpp"
#include "dogen/tack/test/mock_model_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("tack.mock_model_factory"));

const std::string model_name_prefix("some_model_");
const std::string type_name_prefix("some_type_");
const std::string concept_name_prefix("some_concept_");
const std::string property_name_prefix("some_property_");
const std::string module_name_prefix("some_module_");
const std::string visitor_postfix("_visitor");
const std::string versioned_postfix("_versioned");
const std::string unversioned_postfix("_unversioned");

const std::string boolean("bool");
const std::string unsigned_int("unsigned int");

const std::string documentation("Some documentation");

const std::string types_main_header("types_");
const std::string types_forward_declaration("types_fwd_");
const std::string serialization_main_header("serialization_");
const std::string serialization_forward_declaration("serialization_fwd_");

const std::string licence_name_key("licence_name");
const std::string licence_name_value("gpl_v2");
const std::string modeline_group_name_key("modeline_group_name");
const std::string modeline_group_name_value("emacs");
const std::string generate_preamble_key("generate_preamble");
const std::string generate_preamble_value("true");
const std::string code_generation_marker_message_key(
    "code_generation_marker.message");
const std::string code_generation_marker_message_value("sample message");
const std::string copyright_notices_key("copyright_notices");
const std::string copyright_notices_value(
    "Copyright (C) 2012 Person <name@company.co.uk>");

const std::string header_extension(".hpp");

const std::string invalid_property_type("Unknown property type.");
const std::string invalid_object_type("Invalid or unsupported object type.");

std::string concept_name(const unsigned int i) {
    std::ostringstream stream;
    stream << concept_name_prefix << i;
    return stream.str();
}

std::string type_name(const unsigned int i) {
    std::ostringstream stream;
    stream << type_name_prefix << i;
    return stream.str();
}

std::string model_name(const unsigned int i) {
    std::ostringstream stream;
    stream << model_name_prefix << i;
    return stream.str();
}

std::string property_name(const unsigned int i) {
    std::ostringstream stream;
    stream << property_name_prefix << i;
    return stream.str();
}

std::string module_name(const unsigned int i) {
    std::ostringstream stream;
    stream << module_name_prefix << i;
    return stream.str();
}

dogen::tack::nested_name mock_nested_name(const dogen::tack::name& n) {
    dogen::tack::name nn;
    nn.simple(n.simple());
    nn.location().original_model_name(n.location().original_model_name());

    dogen::tack::nested_name r;
    r.type(nn);
    return r;
}

dogen::tack::name mock_model_name(unsigned int i) {
    dogen::tack::name r;
    r.location().original_model_name(model_name(i));
    r.simple(model_name(i));
    return r;
}

dogen::tack::nested_name
mock_nested_name_shared_ptr(const dogen::tack::name& n) {
    dogen::tack::name e;
    e.simple("shared_ptr");
    e.location().original_model_name("boost");

    dogen::tack::nested_name r;
    r.type(e);

    dogen::tack::nested_name c;
    c.type(n);

    r.children(std::list<dogen::tack::nested_name> { c });

    return r;
}

dogen::tack::nested_name mock_nested_name(
    dogen::tack::test::mock_model_factory::property_types pt) {
    using namespace dogen::tack;

    name n;
    nested_name r;

    typedef test::mock_model_factory::property_types property_types;
    switch(pt) {
    case property_types::unsigned_int:
        n.simple(unsigned_int);
        r.type(n);
        break;
    case property_types::boolean:
        n.simple(boolean);
        r.type(n);
        break;
    case property_types::boost_variant: {
        name e;
        e.simple("variant");
        e.location().original_model_name("boost");
        r.type(e);

        name f;
        f.simple(boolean);
        nested_name c;
        c.type(f);

        name g;
        g.simple(unsigned_int);
        nested_name d;
        d.type(g);
        r.children(std::list<nested_name> { c, d });
        break;
    }
    case property_types::std_string:
        n.simple("string");
        n.location().original_model_name("std");
        r.type(n);
        break;
    case property_types::std_pair: {
        name e;
        e.simple("pair");
        e.location().original_model_name("std");
        r.type(e);

        name f;
        f.simple(boolean);
        nested_name c;
        c.type(f);

        name g;
        g.simple(boolean);
        nested_name d;
        d.type(g);
        r.children(std::list<nested_name> { c, d });
        break;
    }
    default:
        BOOST_LOG_SEV(lg, error) << invalid_property_type;
        BOOST_THROW_EXCEPTION(test::building_error(invalid_property_type));
    }
    return r;
}

void populate_object(dogen::tack::object& o, const unsigned int i,
    const dogen::tack::name& model_name, const unsigned int module_n) {

    dogen::tack::name n;
    n.location().original_model_name(
        model_name.location().original_model_name());
    n.simple(type_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        n.location().internal_module_path().push_back(module_name(i));

    o.name(n);
    o.generation_type(dogen::tack::generation_types::full_generation);
    o.documentation(documentation);
    o.origin_type(dogen::tack::origin_types::user);
}

void populate_simple_model_properties(dogen::tack::model& m,
    const unsigned int n) {
    m.name(mock_model_name(n));
    m.documentation(documentation);
    m.origin_type(dogen::tack::origin_types::user);
    m.generation_type(dogen::tack::generation_types::full_generation);
}

dogen::tack::property mock_property(const unsigned int n = 0,
    const dogen::tack::test::mock_model_factory::property_types pt =
    dogen::tack::test::mock_model_factory::property_types::unsigned_int,
    boost::optional<dogen::tack::name> name =
    boost::optional<dogen::tack::name>()) {
    dogen::tack::property r;
    r.name(property_name(n));

    using property_types = dogen::tack::test::mock_model_factory::property_types;
    if (pt == property_types::value_object)
        r.type(mock_nested_name(*name));
    else if (pt == property_types::boost_shared_ptr)
        r.type(mock_nested_name_shared_ptr(*name));
    else
        r.type(mock_nested_name(pt));

    return r;
}

template<typename Stateful>
void add_property(Stateful& s, const bool properties_indexed,
    const unsigned int n = 0,
    const dogen::tack::test::mock_model_factory::property_types pt =
    dogen::tack::test::mock_model_factory::property_types::unsigned_int,
    boost::optional<dogen::tack::name> name =
    boost::optional<dogen::tack::name>()) {

    auto p(mock_property(n, pt, name));
    s.local_properties().push_back(p);

    if (properties_indexed)
        s.all_properties().push_back(p);
}

template<typename Nameable>
void add_relationship(dogen::tack::object& target,
    const Nameable& relative,
    const dogen::tack::relationship_types rt) {
    using dogen::tack::relationship_types;
    target.relationships()[rt].push_back(relative.name());
}

const bool add_leaf(true);

void model_concept(const bool properties_indexed,
    dogen::tack::object& o, const dogen::tack::concept& c) {

    using dogen::tack::relationship_types;
    add_relationship(o, c, relationship_types::modeled_concepts);
    if (properties_indexed) {
        for (const auto& p : c.all_properties()) {
            o.local_properties().push_back(p);
            o.all_properties().push_back(p);
        }
    }
}

void parent_to_child(const bool properties_indexed,
    dogen::tack::object& parent,
    dogen::tack::object& child,
    dogen::tack::object& original_parent,
    const bool add_leaf_relationship = true) {
    using dogen::tack::relationship_types;
    add_relationship(child, parent, relationship_types::parents);
    add_relationship(child, original_parent,
        relationship_types::original_parents);

    if (add_leaf_relationship)
        add_relationship(parent, child, relationship_types::leaves);

    parent.is_parent(true);
    child.is_child(true);

    if (properties_indexed && !parent.all_properties().empty()) {
        child.inherited_properties().insert(std::make_pair(
                parent.name(), parent.all_properties()));

        child.all_properties().insert(child.all_properties().end(),
            parent.all_properties().begin(), parent.all_properties().end());
    }
}

void parent_to_child(const bool properties_indexed,
    dogen::tack::object& parent, dogen::tack::object& child,
    const bool add_leaf_relationship = true) {
    parent_to_child(properties_indexed, parent, child, parent,
        add_leaf_relationship);
}

template<typename Nameable>
void insert_nameable(std::unordered_map<dogen::tack::name, Nameable>& map,
    const Nameable& n) {
    map.insert(std::make_pair(n.name(), n));
}

void insert_object(dogen::tack::model& m, const dogen::tack::object& o) {
    m.objects().insert(std::make_pair(o.name(), o));
}

std::string name_for_file_name(const dogen::tack::name& n) {
    if (n.simple().empty())
        return n.location().original_model_name();
    return n.simple();
}

std::string types_header_filename(const dogen::tack::name& n) {
    return types_main_header + name_for_file_name(n);
}

std::string types_forward_declaration_filename(const dogen::tack::name& n) {
    return types_forward_declaration + name_for_file_name(n);
}

std::string boost_serialization_header_filename(const dogen::tack::name& n) {
    return serialization_main_header + name_for_file_name(n);
}

std::string boost_serialization_forward_declaration_filename(
    const dogen::tack::name& n) {
    return serialization_forward_declaration + name_for_file_name(n);
}

void add_test_dynamic_extensions(dogen::dynamic::object& o) {
    using namespace dogen::dynamic;

    value_factory f;
    o.fields().insert(std::make_pair(licence_name_key,
            field_instance(f.make_text(licence_name_value))));

    o.fields().insert(std::make_pair(copyright_notices_key,
            field_instance(f.make_text(copyright_notices_value))));

    o.fields().insert(std::make_pair(modeline_group_name_key,
            field_instance(f.make_text(modeline_group_name_value))));

    o.fields().insert(std::make_pair(code_generation_marker_message_key,
            field_instance(
                f.make_text(code_generation_marker_message_value))));

    o.fields().insert(std::make_pair(generate_preamble_key,
            field_instance(f.make_text(generate_preamble_value))));
}

}

namespace dogen {
namespace tack {
namespace test {

mock_model_factory::flags::flags(const bool tagged,
    const bool merged, const bool resolved,
    const bool concepts_indexed, const bool properties_indexed,
    const bool associations_indexed) :
    tagged_(tagged), merged_(merged), resolved_(resolved),
    concepts_indexed_(concepts_indexed),
    properties_indexed_(properties_indexed),
    associations_indexed_(associations_indexed) { }

bool mock_model_factory::flags::tagged() const { return tagged_; }
void mock_model_factory::flags::tagged(const bool v) { tagged_ = v; }

bool mock_model_factory::flags::merged() const { return merged_; }
void mock_model_factory::flags::merged(const bool v) { merged_ = v; }

bool mock_model_factory::flags::resolved() const { return resolved_; }
void mock_model_factory::flags::resolved(const bool v) { resolved_ = v; }

bool mock_model_factory::flags::concepts_indexed() const {
    return concepts_indexed_;
}
void mock_model_factory::flags::concepts_indexed(const bool v) {
    concepts_indexed_ = v;
}

bool mock_model_factory::flags::properties_indexed() const {
    return properties_indexed_;
}
void mock_model_factory::flags::properties_indexed(const bool v) {
    properties_indexed_ = v;
}

bool mock_model_factory::flags::associations_indexed() const {
    return associations_indexed_;
}
void mock_model_factory::flags::associations_indexed(const bool v) {
    associations_indexed_ = v;
}

mock_model_factory::
mock_model_factory(const flags& f, dynamic_extension_function_type fn)
    : flags_(f),
      dynamic_extension_function_(fn ? fn : add_test_dynamic_extensions) { }

std::string mock_model_factory::model_name(const unsigned int n) const {
    return ::model_name(n);
}

std::string mock_model_factory::concept_name(const unsigned int n) const {
    return ::concept_name(n);
}

std::string mock_model_factory::type_name(const unsigned int n) const {
    return ::type_name(n);
}

std::string mock_model_factory::module_name(const unsigned int n) const {
    return ::module_name(n);
}

std::string mock_model_factory::property_name(const unsigned int n) const {
    return ::property_name(n);
}

std::string mock_model_factory::types_header_filename(const name& n) const {
    return ::types_header_filename(n);
}

std::string mock_model_factory::
types_forward_declaration_filename(const name& n) const {
    return ::types_forward_declaration_filename(n);
}

std::string mock_model_factory::
boost_serialization_header_filename(const name& n) const {
    return ::boost_serialization_header_filename(n);
}

std::string mock_model_factory::
boost_serialization_forward_declaration_filename(const name& n) const {
    return ::boost_serialization_forward_declaration_filename(n);
}

bool mock_model_factory::
is_model_n(const unsigned int n, const name& name) const {
    return is_model_n(n, name.location().original_model_name());
}

bool mock_model_factory::
is_model_n(const unsigned int n, const std::string& name) const {
    return model_name(n) == name;
}

bool mock_model_factory::
is_type_name_n(const unsigned int n, const name& name) const {
    return is_type_name_n(n, name.simple());
}

bool mock_model_factory::
is_concept_name_n(const unsigned int n, const name& name) const {
    return concept_name(n) == name.simple();
}

bool mock_model_factory::
is_type_name_n(const unsigned int n, const std::string& name) const {
    return type_name(n) == name;
}

bool mock_model_factory::
is_module_n(const unsigned int n, const std::string& name) const {
    return module_name(n) == name;
}

bool mock_model_factory::is_type_name_n_visitor(const unsigned int n,
    const name& name) const {
    return
        boost::contains(name.simple(), type_name(n)) &&
        boost::contains(name.simple(), visitor_postfix);
}

void mock_model_factory::
handle_model_module(const bool add_model_module, tack::model& m) const {
    if (!add_model_module)
        return;

    name n;
    n.location().original_model_name(
        m.name().location().original_model_name());
    n.simple(m.name().simple());
    const auto module(make_module(n, documentation));
    insert_nameable(m.modules(), module);
}

object mock_model_factory::make_value_object(const unsigned int i,
    const name& model_name, const unsigned int module_n) const {

    object r;
    populate_object(r, i, model_name, module_n);
    r.object_type(dogen::tack::object_types::user_defined_value_object);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

object mock_model_factory::make_value_object(unsigned int i,
    const unsigned int module_n) const {
    return make_value_object(i, mock_model_name(i), module_n);
}

concept mock_model_factory::make_concept(const unsigned int i,
    const name& model_name) const {

    name n;
    n.location().original_model_name(
        model_name.location().original_model_name());
    n.simple(concept_name(i));

    concept r;
    r.name(n);
    r.documentation(documentation);
    r.origin_type(origin_types::user);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

enumeration mock_model_factory::
make_enumeration(const unsigned int i, const name& model_name,
    const unsigned int module_n) const {
    name n;
    n.location().original_model_name(
        model_name.location().original_model_name());
    n.simple(type_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        n.location().internal_module_path().push_back(module_name(i));

    enumeration r;
    r.name(n);
    r.generation_type(generation_types::full_generation);
    r.documentation(documentation);

    name un;
    un.simple(unsigned_int);
    r.underlying_type(un);

    const auto lambda([&](const unsigned int n) -> enumerator {
            enumerator r;
            r.name(type_name(n));
            r.value(boost::lexical_cast<std::string>(n));
            return r;
        });

    r.enumerators().push_back(lambda(0));
    r.enumerators().push_back(lambda(1));

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

object mock_model_factory::make_exception(const unsigned int i,
    const name& model_name, const unsigned int module_n) const {
    name n;
    n.location().original_model_name(
        model_name.location().original_model_name());
    n.simple(type_name(i));

    for (unsigned int i(0); i < module_n; ++i)
        n.location().internal_module_path().push_back(module_name(i));

    object r;
    r.name(n);
    r.generation_type(generation_types::full_generation);
    r.documentation(documentation);
    r.object_type(dogen::tack::object_types::exception);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

module mock_model_factory::make_module(const tack::name& n,
    const std::string& documentation) const {
    module r;
    r.name(n);
    r.documentation(documentation);
    return r;
}

module mock_model_factory::make_module(const unsigned int module_n,
    const std::string& model_name,
    const std::list<std::string>& internal_module_path,
    const std::string& documentation) const {

    name n;
    n.location().original_model_name(model_name);
    n.simple(module_name(module_n));
    n.location().internal_module_path(internal_module_path);
    return make_module(n, documentation);
}

name mock_model_factory::make_name(const unsigned int model_n,
    const unsigned int simple_n) const {

    name r;
    r.location().original_model_name(model_name(model_n));
    r.simple(type_name(simple_n));
    return r;
}

model mock_model_factory::make_empty_model(const unsigned int n,
    const bool add_model_module) const {
    model r;
    populate_simple_model_properties(r, n);
    handle_model_module(add_model_module, r);

    if (flags_.tagged())
        dynamic_extension_function_(r.extensions());

    return r;
}

model mock_model_factory::
make_single_type_model(const unsigned int n, const object_types ot,
    const bool add_model_module) const {
    return make_multi_type_model(n, 1, ot, 0, add_model_module);
}

model mock_model_factory::
make_single_type_model_in_module(const unsigned int n, const object_types ot,
    const unsigned int mod_n, const bool add_model_module) const {
    return make_multi_type_model(n, 1, ot, mod_n, add_model_module);
}

model mock_model_factory::
make_multi_type_model(const unsigned int n, const unsigned int type_n,
    const object_types ot, const unsigned int mod_n,
    const bool add_model_module) const {

    model r(make_empty_model(n, add_model_module));

    std::list<std::string> internal_module_path;
    const auto mn(r.name().location().original_model_name());
    for (unsigned int i(0); i < mod_n; ++i) {
        const auto m(make_module(i, mn, internal_module_path, documentation));
        insert_nameable(r.modules(), m);
        internal_module_path.push_back(module_name(i));
    }

    switch (ot) {
    case object_types::value_object:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto o(make_value_object(i, r.name(), mod_n));
            insert_object(r, o);
        }
        break;
    case object_types::enumeration:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(make_enumeration(i, r.name(), mod_n));
            insert_nameable(r.enumerations(), e);
        }
        break;
    case object_types::exception:
        for (unsigned int i(0); i < type_n; ++i) {
            const auto e(make_exception(i, r.name(), mod_n));
            insert_object(r, e);
        }
        break;
    default:
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }

    return r;
}

model mock_model_factory::
make_single_concept_model(const unsigned int n,
    const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));

    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c(make_concept(0, r.name()));
    add_property(c, flags_.properties_indexed());
    insert_nameable(r.concepts(), c);

    auto o(make_value_object(0, r.name()));
    add_property(o, flags_.properties_indexed(), 1);
    model_concept(flags_.properties_indexed(), o, c);
    insert_object(r, o);

    return r;
}

model mock_model_factory::
make_first_degree_concepts_model(const unsigned int n,
    const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c0);
    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    add_property(o1, flags_.properties_indexed(), 2);

    if (flags_.concepts_indexed())
        model_concept(flags_.properties_indexed(), o1, c0);

    model_concept(flags_.properties_indexed(), o1, c1);
    insert_object(r, o1);

    return r;
}

model mock_model_factory::
make_second_degree_concepts_model(const unsigned int n,
    const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(2, r.name()));
    add_property(c2, flags_.properties_indexed(), 2);

    if (flags_.concepts_indexed())
        c2.refines().push_back(c0.name());

    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c0);
    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    if (flags_.concepts_indexed())
        model_concept(flags_.properties_indexed(), o1, c0);

    model_concept(flags_.properties_indexed(), o1, c1);
    insert_object(r, o1);

    auto o2(make_value_object(2, r.name()));
    add_property(o2, flags_.properties_indexed(), 3);
    if (flags_.concepts_indexed()) {
        model_concept(flags_.properties_indexed(), o2, c0);
        model_concept(flags_.properties_indexed(), o2, c1);
    }
    model_concept(flags_.properties_indexed(), o2, c2);
    insert_object(r, o2);

    return r;
}

model mock_model_factory::make_multiple_inheritance_concepts_model(
    const unsigned int n, const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(1, r.name()));
    add_property(c2, flags_.properties_indexed(), 2);
    c2.refines().push_back(c0.name());
    c2.refines().push_back(c1.name());
    insert_nameable(r.concepts(), c2);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c2);
    insert_object(r, o0);
    return r;
}

model mock_model_factory::
make_diamond_inheritance_concepts_model(const unsigned int n,
    const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    concept c2(make_concept(2, r.name()));
    add_property(c2, flags_.properties_indexed(), 2);
    c2.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c2);

    concept c3(make_concept(3, r.name()));
    add_property(c3, flags_.properties_indexed(), 3);
    if (flags_.concepts_indexed())
        c3.refines().push_back(c0.name());

    c3.refines().push_back(c1.name());
    c3.refines().push_back(c2.name());
    insert_nameable(r.concepts(), c3);

    auto o0(make_value_object(0, r.name()));
    if (flags_.concepts_indexed()) {
        model_concept(flags_.properties_indexed(), o0, c0);
        model_concept(flags_.properties_indexed(), o0, c1);
        model_concept(flags_.properties_indexed(), o0, c2);
    }
    model_concept(flags_.properties_indexed(), o0, c3);
    insert_object(r, o0);
    return r;
}

model mock_model_factory::make_object_with_parent_that_models_concept(
    const unsigned int n, const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    auto o0(make_value_object(0, r.name()));
    model_concept(flags_.properties_indexed(), o0, c0);

    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    parent_to_child(flags_.properties_indexed(), o0, o1);
    o0.is_parent(true);
    insert_object(r, o1);

    return r;
}

model mock_model_factory::
make_object_with_parent_that_models_a_refined_concept(
    const unsigned int n, const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    concept c1(make_concept(1, r.name()));
    add_property(c1, flags_.properties_indexed(), 1);
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);

    auto o0(make_value_object(0, r.name()));

    model_concept(flags_.properties_indexed(), o0, c1);
    if (flags_.concepts_indexed())
        model_concept(flags_.properties_indexed(), o0, c0);

    insert_object(r, o0);

    auto o1(make_value_object(1, r.name()));
    parent_to_child(flags_.properties_indexed(), o0, o1);
    o0.is_parent(true);
    insert_object(r, o1);

    return r;
}

model mock_model_factory::
make_concept_that_refines_missing_concept(const unsigned int n,
    const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    concept c0(make_concept(0, r.name()));
    concept c1(make_concept(1, r.name()));
    c1.refines().push_back(c0.name());
    insert_nameable(r.concepts(), c1);
    return r;
}

model mock_model_factory::
make_object_that_models_missing_concept(const unsigned int n,
    const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());

    auto o0(make_value_object(0, r.name()));

    model_concept(flags_.properties_indexed(), o0, c0);
    insert_object(r, o0);
    return r;
}

model mock_model_factory::make_object_that_models_concept_with_missing_parent(
    const unsigned int n, const bool add_model_module) const {
    model r(make_empty_model(n, add_model_module));
    primitive ui;
    ui.name().simple(unsigned_int);
    r.primitives().insert(std::make_pair(ui.name(), ui));

    concept c0(make_concept(0, r.name()));
    add_property(c0, flags_.properties_indexed());
    insert_nameable(r.concepts(), c0);

    auto o0(make_value_object(0, r.name()));
    auto o1(make_value_object(1, r.name()));
    parent_to_child(flags_.properties_indexed(), o0, o1);
    o0.is_parent(true);

    model_concept(flags_.properties_indexed(), o1, c0);
    insert_object(r, o1);

    return r;
}

model mock_model_factory::object_with_both_regular_and_weak_associations(
    const bool add_model_module) const {
    model r(make_empty_model(0, add_model_module));
    const auto mn(mock_model_name(0));
    auto o1(make_value_object(1, mn));
    insert_object(r, o1);

    object o0(make_value_object(0, mn));
    property p0(mock_property(0, property_types::value_object, o1.name()));
    o0.local_properties().push_back(p0);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p0);

    const auto ra(relationship_types::regular_associations);
    if (flags_.associations_indexed())
        o0.relationships()[ra].push_back(o1.name());

    name n;
    n.simple("shared_ptr");
    n.location().original_model_name("boost");

    object o2;
    o2.name(n);
    o2.object_type(dogen::tack::object_types::smart_pointer);
    insert_object(r, o2);

    property p1(mock_property(1, property_types::boost_shared_ptr, o1.name()));
    o0.local_properties().push_back(p1);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p1);

    const auto wa(relationship_types::weak_associations);
    if (flags_.associations_indexed())
        o0.relationships()[wa].push_back(o1.name());

    object o3(make_value_object(3, mn));
    insert_object(r, o3);

    property p2(mock_property(2, property_types::boost_shared_ptr, o3.name()));
    o0.local_properties().push_back(p2);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p2);

    if (flags_.associations_indexed())
        o0.relationships()[wa].push_back(o3.name());

    n.simple("string");
    n.location().original_model_name("std");

    object o4;
    o4.name(n);
    o4.object_type(dogen::tack::object_types::user_defined_value_object);
    insert_object(r, o4);

    property p3(mock_property(3, property_types::value_object, o4.name()));
    o0.local_properties().push_back(p3);

    if (flags_.properties_indexed())
        o0.all_properties().push_back(p3);

    if (flags_.associations_indexed())
        o0.relationships()[ra].push_back(o4.name());

    insert_object(r, o0);
    return r;
}

model mock_model_factory::
object_with_property(const object_types ot, const property_types pt,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o1(make_value_object(1, mn));

    property p(mock_property(0, pt, o1.name()));

    object o0;
    if (ot == object_types::value_object)
        o0 = make_value_object(0, mn);
    else {
        BOOST_LOG_SEV(lg, error) << invalid_object_type;
        BOOST_THROW_EXCEPTION(building_error(invalid_object_type));
    }

    o0.local_properties().push_back(p);
    if (flags_.properties_indexed())
        o0.all_properties().push_back(p);

    model r(make_empty_model(0, add_model_module));
    const auto ra(relationship_types::regular_associations);
    const auto wa(relationship_types::weak_associations);
    if (pt == property_types::value_object ||
        pt == property_types::boost_shared_ptr) {
        insert_object(r, o1);

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(o1.name());
    }

    if (pt == property_types::unsigned_int ||
        pt == property_types::boolean) {
        primitive ui;
        ui.name(p.type().type());
        insert_nameable(r.primitives(), ui);

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(ui.name());

    } else if (pt == property_types::boost_shared_ptr) {
        name n;
        n.simple("shared_ptr");
        n.location().original_model_name("boost");

        object o2;
        o2.name(n);
        o2.object_type(dogen::tack::object_types::smart_pointer);
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.relationships()[wa].push_back(o2.name());

    } else if (pt == property_types::std_pair) {
        primitive b;
        b.name().simple(boolean);
        r.primitives().insert(std::make_pair(b.name(), b));

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(b.name());

        name n;
        n.simple("pair");
        n.location().original_model_name("std");

        object o2;
        o2.name(n);
        o2.object_type(dogen::tack::object_types::user_defined_value_object);

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(o2.name());

        insert_object(r, o2);
    } else if (pt == property_types::boost_variant) {
        primitive b;
        b.name().simple(boolean);
        r.primitives().insert(std::make_pair(b.name(), b));

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(b.name());

        primitive ui;
        ui.name().simple(unsigned_int);
        r.primitives().insert(std::make_pair(ui.name(), ui));

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(ui.name());

        name n;
        n.simple("variant");
        n.location().original_model_name("boost");

        object o2;
        o2.name(n);
        o2.object_type(dogen::tack::object_types::user_defined_value_object);
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(o2.name());

    } else if (pt == property_types::std_string) {
        name n;
        n.simple("string");
        n.location().original_model_name("std");

        object o2;
        o2.name(n);
        o2.object_type(dogen::tack::object_types::user_defined_value_object);
        insert_object(r, o2);

        if (flags_.associations_indexed())
            o0.relationships()[ra].push_back(o2.name());
    }
    insert_object(r, o0);
    return r;
}

std::array<model, 2>
mock_model_factory::object_with_property_type_in_different_model(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));

    add_property(o0, flags_.properties_indexed(),
        0, property_types::value_object, o1.name());

    name m0_n;
    m0_n.location().original_model_name(model_name(0));

    model m0;
    m0.name(m0_n);
    insert_object(m0, o0);
    handle_model_module(add_model_module, m0);

    name m1_n;
    m1_n.location().original_model_name(model_name(1));

    model m1;
    m1.name(m1_n);
    insert_object(m1, o1);
    handle_model_module(add_model_module, m1);

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::object_with_missing_property_type(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));

    add_property(o0, flags_.properties_indexed(), 0,
        property_types::value_object, o1.name());

    const auto ra(relationship_types::regular_associations);
    if (flags_.associations_indexed())
        o0.relationships()[ra].push_back(o1.name());

    model r(make_empty_model(0, add_model_module));
    insert_object(r, o0);

    return r;
}

model mock_model_factory::
object_with_parent_in_the_same_model(const bool has_property,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));

    model r(make_empty_model(0, add_model_module));
    if (has_property) {
        primitive ui;
        ui.name().simple(unsigned_int);
        r.primitives().insert(std::make_pair(ui.name(), ui));
    }

    auto o0(make_value_object(0, mn));
    if (has_property)
        add_property(o0, flags_.properties_indexed());

    auto o1(make_value_object(1, mn));
    if (has_property)
        add_property(o1, flags_.properties_indexed(), 1);

    parent_to_child(flags_.properties_indexed(), o1, o0);
    insert_object(r, o0);
    insert_object(r, o1);

    o1.is_parent(true);
    return r;
}

model mock_model_factory::object_with_missing_parent_in_the_same_model(
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn));
    auto o1(make_value_object(1, mn));
    o1.is_parent(true);
    parent_to_child(flags_.properties_indexed(), o1, o0);
    model r(make_empty_model(0, add_model_module));
    insert_object(r, o1);

    return r;
}

std::array<model, 2> mock_model_factory::
object_with_parent_in_different_models(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));
    parent_to_child(flags_.properties_indexed(), o1, o0);

    o1.is_parent(true);

    model m0(make_empty_model(0, add_model_module));
    insert_object(m0, o0);

    model m1(make_empty_model(1, add_model_module));
    insert_object(m1, o1);
    m1.name(mock_model_name(1));
    m1.origin_type(origin_types::user);

    return std::array<model, 2> {{ m0, m1 }};
}

model mock_model_factory::object_with_three_children_in_same_model(
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn));
    auto o1(make_value_object(1, mn));
    auto o2(make_value_object(2, mn));
    auto o3(make_value_object(3, mn));

    parent_to_child(flags_.properties_indexed(), o3, o0);
    parent_to_child(flags_.properties_indexed(), o3, o1);
    parent_to_child(flags_.properties_indexed(), o3, o2);

    o3.is_parent(true);

    model r(make_empty_model(0, add_model_module));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    insert_object(r, o3);
    r.name(mn);
    return r;
}

model mock_model_factory::
object_with_third_degree_parent_in_same_model(const bool has_property,
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));

    model r(make_empty_model(0, add_model_module));
    if (has_property) {
        primitive ui;
        ui.name().simple(unsigned_int);
        r.primitives().insert(std::make_pair(ui.name(), ui));
    }

    auto o3(make_value_object(3, mn));
    if (has_property)
        add_property(o3, flags_.properties_indexed(), 3);

    auto o2(make_value_object(2, mn));
    if (has_property)
        add_property(o2, flags_.properties_indexed(), 2);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    auto o1(make_value_object(1, mn));
    if (has_property)
        add_property(o1, flags_.properties_indexed(), 1);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);

    auto o0(make_value_object(0, mn));
    if (has_property)
        add_property(o0, flags_.properties_indexed());

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);

    o1.is_parent(true);
    add_relationship(o1, o0, relationship_types::leaves);

    o2.is_parent(true);
    add_relationship(o2, o0, relationship_types::leaves);

    o3.is_parent(true);
    add_relationship(o3, o0, relationship_types::leaves);

    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    insert_object(r, o3);

    return r;
}

model mock_model_factory::object_with_third_degree_parent_missing(
    const bool add_model_module) const {
    const auto mn(mock_model_name(0));
    auto o0(make_value_object(0, mn));
    auto o1(make_value_object(1, mn));
    auto o2(make_value_object(2, mn));
    auto o3(make_value_object(3, mn));

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    add_relationship(o1, o0, relationship_types::leaves);

    o2.is_parent(true);
    add_relationship(o2, o0, relationship_types::leaves);

    o3.is_parent(true);
    add_relationship(o3, o0, relationship_types::leaves);

    model r(make_empty_model(0, add_model_module));
    insert_object(r, o0);
    insert_object(r, o1);
    insert_object(r, o2);
    r.name(mn);
    return r;
}

std::array<model, 4> mock_model_factory::
object_with_third_degree_parent_in_different_models(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));
    auto o2(make_value_object(2));
    auto o3(make_value_object(3));

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    add_relationship(o1, o0, relationship_types::leaves);

    o2.is_parent(true);
    add_relationship(o2, o0, relationship_types::leaves);

    o3.is_parent(true);
    add_relationship(o3, o0, relationship_types::leaves);

    model m0(make_empty_model(0, add_model_module));
    insert_object(m0, o0);

    model m1(make_empty_model(1, add_model_module));
    insert_object(m1, o1);

    model m2(make_empty_model(2, add_model_module));
    insert_object(m2, o2);

    model m3(make_empty_model(3, add_model_module));
    insert_object(m3, o3);

    return std::array<model, 4>{{ m0, m1, m2, m3 }};
}

std::array<model, 4> mock_model_factory::
object_with_missing_third_degree_parent_in_different_models(
    const bool add_model_module) const {
    auto o0(make_value_object(0));
    auto o1(make_value_object(1));
    auto o2(make_value_object(2));
    auto o3(make_value_object(3));

    parent_to_child(flags_.properties_indexed(), o1, o0, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o2, o1, o3, !add_leaf);
    parent_to_child(flags_.properties_indexed(), o3, o2, o3, !add_leaf);

    o1.is_parent(true);
    add_relationship(o1, o0, relationship_types::leaves);

    o2.is_parent(true);
    add_relationship(o2, o0, relationship_types::leaves);

    o3.is_parent(true);
    add_relationship(o3, o0, relationship_types::leaves);

    model m0(make_empty_model(0, add_model_module));
    insert_object(m0, o0);

    model m1(make_empty_model(1, add_model_module));
    insert_object(m1, o1);

    model m2(make_empty_model(2, add_model_module));
    insert_object(m2, o2);

    return std::array<model, 4>{{ m0, m1, m2 }};
}

model mock_model_factory::object_with_group_of_properties_of_different_types(
    const bool repeat_group, const bool add_model_module) const {
    model r(make_empty_model(0, add_model_module));
    const auto mn(r.name());

    auto o0(make_value_object(0, mn));
    const auto lambda([&](const property& p) {
            o0.local_properties().push_back(p);
            if (flags_.properties_indexed())
                o0.all_properties().push_back(p);
        });

    auto o1(make_value_object(1, mn));
    auto p0(mock_property(0, property_types::value_object, o1.name()));
    lambda(p0);
    insert_object(r, o1);

    auto p1(mock_property(1));
    lambda(p1);
    primitive ui;
    ui.name(p1.type().type());
    insert_nameable(r.primitives(), ui);

    auto o3(make_value_object(3, mn));
    insert_object(r, o3);
    auto p2(mock_property(2, property_types::boost_shared_ptr, o3.name()));
    lambda(p2);

    name n;
    n.simple("shared_ptr");
    n.location().original_model_name("boost");

    object o2;
    o2.name(n);
    o2.object_type(dogen::tack::object_types::smart_pointer);
    insert_object(r, o2);

    auto o4(make_value_object(4, mn));
    insert_object(r, o4);
    auto p3(mock_property(3, property_types::value_object, o4.name()));
    lambda(p3);

    if (repeat_group) {
        auto p4(mock_property(4, property_types::value_object, o1.name()));
        lambda(p4);

        auto p5(mock_property(5));
        lambda(p5);

        auto p6(mock_property(6, property_types::boost_shared_ptr, o3.name()));
        lambda(p6);

        auto p7(mock_property(7, property_types::value_object, o4.name()));
        lambda(p7);
    }
    insert_object(r, o0);
    return r;
}

} } }
