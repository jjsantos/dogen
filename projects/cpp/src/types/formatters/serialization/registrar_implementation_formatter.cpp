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
#include <boost/make_shared.hpp>
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/serialization/registrar_implementation_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/serialization/registrar_implementation_formatter.hpp"

namespace {
    const std::string registrar_name("registrar");
}

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

namespace {

class provider final : public formattables::
        inclusion_dependencies_provider_interface<tack::model> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
        provide(const formattables::inclusion_dependencies_builder_factory& f,
        const tack::model& m) const override;
};

std::string provider::formatter_name() const {
    return registrar_implementation_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const formattables::inclusion_dependencies_builder_factory& f,
    const tack::model& m) const {

    tack::name n;
    n.simple(registrar_name);
    n.location().original_model_name(m.name().location().original_model_name());
    n.location().external_module_path(
        m.name().location().external_module_path());

    auto builder(f.make());
    const auto rh_fn(traits::registrar_header_formatter_name());
    builder.add(n, rh_fn);

    using ic = inclusion_constants;
    const auto as(builder.get_aspect_settings(n));

    builder.add(ic::boost::archive::text_iarchive());
    builder.add(ic::boost::archive::text_oarchive());
    builder.add(ic::boost::archive::binary_iarchive());
    builder.add(ic::boost::archive::binary_oarchive());
    builder.add(ic::boost::archive::polymorphic_iarchive());
    builder.add(ic::boost::archive::polymorphic_oarchive());

    if (!as.disable_xml_serialization()) {
        builder.add(ic::boost::archive::xml_iarchive());
        builder.add(ic::boost::archive::xml_oarchive());
    }

    const auto ch_fn(traits::class_header_formatter_name());
    for (const auto& l : m.leaves())
        builder.add(l, ch_fn);

    for (const auto& pair : m.references()) {
        const auto origin_type(pair.second);
        if (origin_type == tack::origin_types::system)
            continue;

        const auto ref(pair.first);
        tack::name n;
        n.location().original_model_name(
            ref.location().original_model_name());
        n.simple(registrar_name);
        n.location().external_module_path(
            ref.location().external_module_path());
        builder.add(n, ch_fn);
    }
    return builder.build();
}

}

std::string registrar_implementation_formatter::static_formatter_name() {
    return traits::registrar_implementation_formatter_name();
}

dynamic::ownership_hierarchy
registrar_implementation_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            registrar_implementation_formatter::static_formatter_name(),
            formatters::traits::implementation_formatter_group_name());
    return r;
}

file_types registrar_implementation_formatter::file_type() const {
    return file_types::cpp_implementation;
}

formattables::origin_types
registrar_implementation_formatter::formattable_origin_type() const {
    return formattables::origin_types::internal;
}

void registrar_implementation_formatter::
register_inclusion_dependencies_provider(
  formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file registrar_implementation_formatter::
format(const formattables::registrar_info& ri) const {
    entity_formatting_assistant fa(ri, ownership_hierarchy(), file_type());
    const auto r(registrar_implementation_formatter_stitch(fa, ri));
    return r;
}

} } } }
