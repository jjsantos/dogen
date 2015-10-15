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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_provider_interface.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder.hpp"
#include "dogen/cpp/types/formatters/traits.hpp"
#include "dogen/cpp/types/formatters/formatting_error.hpp"
#include "dogen/cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/serialization/forward_declarations_formatter_stitch.hpp"
#include "dogen/cpp/types/formatters/serialization/forward_declarations_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::cpp::formatters::serialization;
static logger
lg(logger_factory(forward_declarations_formatter::static_formatter_name()));

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

namespace {

class provider : public formattables::
        inclusion_dependencies_provider_interface<yarn::object> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
    provide(const formattables::inclusion_dependencies_builder_factory& f,
        const yarn::object& o) const override;
};

std::string provider::formatter_name() const {
    return forward_declarations_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::object& o) const {

    const auto self_fn(forward_declarations_formatter::static_formatter_name());
    auto builder(f.make());

    using tp = formatters::types::traits;
    const auto tp_fn(tp::forward_declarations_formatter_name());
    builder.add(o.name(), tp_fn);

    return builder.build();
}

}

std::string forward_declarations_formatter::static_formatter_name() {
    return traits::forward_declarations_formatter_name();
}

dynamic::ownership_hierarchy
forward_declarations_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            forward_declarations_formatter::static_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types forward_declarations_formatter::file_type() const {
    return file_types::cpp_header;
}

formattables::origin_types
forward_declarations_formatter::formattable_origin_type() const {
    return formattables::origin_types::external;
}

void forward_declarations_formatter::register_inclusion_dependencies_provider(
    formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file forward_declarations_formatter::
format(const formattables::forward_declarations_info& fd) const {
    // FIXME: hack: legacy formatters do not support serialisation
    // forward declarations for some types.
    if (fd.is_enum() || fd.is_exception())
        return dogen::formatters::file();

    entity_formatting_assistant fa(fd, ownership_hierarchy(), file_type());
    const auto r(forward_declarations_formatter_stitch(fa, fd));
    return r;
}

} } } }
