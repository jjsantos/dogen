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
#include <boost/make_shared.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/tack/types/object.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_provider_interface.hpp"
#include "dogen/cpp/types/formatters/entity_formatting_assistant.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/hash/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_implementation_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/types/class_implementation_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formatters.types.class_implementation_formatter"));

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

namespace {

class provider final : public formattables::
        inclusion_dependencies_provider_interface<tack::object> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
        provide(const formattables::inclusion_dependencies_builder_factory& f,
        const tack::object& o) const override;
};

std::string provider::formatter_name() const {
    return class_implementation_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const formattables::inclusion_dependencies_builder_factory& f,
    const tack::object& o) const {
    auto builder(f.make());
    const auto ch_fn(traits::class_header_formatter_name());
    builder.add(o.name(), ch_fn);

    using rt = tack::relationship_types;
    builder.add(o, rt::weak_associations, ch_fn);

    const auto io_fctn(formatters::io::traits::facet_name());
    const auto self_fn(class_implementation_formatter::static_formatter_name());

    const bool in_inheritance(o.is_parent() || o.is_child());
    const bool io_enabled(builder.is_enabled(o.name(), self_fn));
    const bool io_integrated(builder.is_integrated(self_fn, io_fctn));
    const bool requires_io(io_enabled && (in_inheritance || io_integrated));

    if (!requires_io)
        return builder.build();

    const auto os(inclusion_constants::std::ostream());
    builder.add(os);

    const auto si(builder.make_special_includes(o));
    if (si.requires_stream_manipulators)
        builder.add(inclusion_constants::boost::io::ios_state());

    if (si.has_std_string)
        builder.add(inclusion_constants::boost::algorithm::string());

    const auto io_fn(formatters::io::traits::class_header_formatter_name());
    builder.add(o, rt::weak_associations, io_fn);
    builder.add(o, rt::regular_associations, io_fn);
    builder.add(o, rt::parents, io_fn);

    return builder.build();
}

}

std::string class_implementation_formatter::static_formatter_name() {
    return traits::class_implementation_formatter_name();
}

dynamic::ownership_hierarchy
class_implementation_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            class_implementation_formatter::static_formatter_name(),
            formatters::traits::implementation_formatter_group_name());
    return r;
}

file_types class_implementation_formatter::file_type() const {
    return file_types::cpp_implementation;
}

formattables::origin_types
class_implementation_formatter::formattable_origin_type() const {
    return formattables::origin_types::external;
}

void class_implementation_formatter::register_inclusion_dependencies_provider(
    formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file class_implementation_formatter::
format(const formattables::class_info& c) const {
    entity_formatting_assistant fa(c, ownership_hierarchy(), file_type());
    const auto r(class_implementation_formatter_stitch(fa, c));
    return r;
}

} } } }
