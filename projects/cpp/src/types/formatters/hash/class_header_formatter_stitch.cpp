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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/class_header_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace hash {

dogen::formatters::file class_header_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::class_info& c) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        {
            auto snf(fa.make_scoped_namespace_formatter());
fa.stream() << std::endl;
fa.stream() << "struct " << c.name() << "_hasher {" << std::endl;
fa.stream() << "public:" << std::endl;
fa.stream() << "    static std::size_t hash(const " << c.name() << "& v);" << std::endl;
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
        } // snf
fa.stream() << std::endl;
fa.stream() << "namespace std {" << std::endl;
fa.stream() << std::endl;
fa.stream() << "template<>" << std::endl;
fa.stream() << "struct hash<" << c.qualified_name() << "> {" << std::endl;
fa.stream() << "public:" << std::endl;
fa.stream() << "    size_t operator()(const " << c.qualified_name() << "& v) const {" << std::endl;
fa.stream() << "        return " << c.qualified_name() << "_hasher::hash(v);" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << "};" << std::endl;
fa.stream() << std::endl;
fa.stream() << "}" << std::endl;
    } // sbf
    return fa.make_file();
}
} } } }
