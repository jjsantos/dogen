/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright(C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/formatters/types/cpp/scoped_boilerplate_formatter.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/registrar_implementation_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace serialization {

dogen::formatters::file registrar_implementation_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::registrar_info& ri) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        {
            auto snf(fa.make_scoped_namespace_formatter());
            const auto deps(ri.model_dependencies());
            const auto leaves(ri.leaves());
            const bool has_types(!deps.empty() || !leaves.empty());
            const std::string arg_name(has_types ? " ar" : "");
fa.stream() << std::endl;
fa.stream() << "template<typename Archive>" << std::endl;
fa.stream() << "void register_types(Archive&" << arg_name << ") {" << std::endl;
            if (has_types) {
                for (const auto d : deps)
fa.stream() << "    " << d << "::register_types(ar);" << std::endl;
                if (!deps.empty() && !leaves.empty())
fa.stream() << std::endl;
                for (const auto l : leaves)
fa.stream() << "    ar.template register_type<" << l << ">();" << std::endl;

            }
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template void register_types(boost::archive::polymorphic_oarchive&" << arg_name << ");" << std::endl;
fa.stream() << "template void register_types(boost::archive::polymorphic_iarchive&" << arg_name << ");" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template void register_types(boost::archive::text_oarchive&" << arg_name << ");" << std::endl;
fa.stream() << "template void register_types(boost::archive::text_iarchive&" << arg_name << ");" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template void register_types(boost::archive::binary_oarchive&" << arg_name << ");" << std::endl;
fa.stream() << "template void register_types(boost::archive::binary_iarchive&" << arg_name << ");" << std::endl;
fa.stream() << std::endl;
            if (!fa.is_xml_serialization_disabled()) {
fa.stream() << "template void register_types(boost::archive::xml_oarchive&" << arg_name << ");" << std::endl;
fa.stream() << "template void register_types(boost::archive::xml_iarchive&" << arg_name << ");" << std::endl;
fa.stream() << std::endl;
            }
        } // snf
    } // sbf
    return fa.make_file();
}

} } } }
