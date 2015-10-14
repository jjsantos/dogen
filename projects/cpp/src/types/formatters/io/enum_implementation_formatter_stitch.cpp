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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/cpp/types/formatters/io/enum_header_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace io {

dogen::formatters::file enum_implementation_formatter_stitch(
    formatters::entity_formatting_assistant& fa,
    const formattables::enum_info& e) {

    {
        auto sbf(fa.make_scoped_boilerplate_formatter());
        {
            auto snf(fa.make_scoped_namespace_formatter());
fa.stream() << std::endl;
fa.stream() << "std::ostream& operator<<(std::ostream& s, const " << e.name() << "& v) {" << std::endl;
fa.stream() << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << e.name() << "\\\", \" << \"\\\"value\\\": \";" << std::endl;
fa.stream() << std::endl;
fa.stream() << "    std::string attr;" << std::endl;
fa.stream() << "    switch (v) {" << std::endl;
            for (const auto en : e.enumerators()) {
fa.stream() << "    case " << e.name() << "::" << en.name() << ":" << std::endl;
fa.stream() << "        attr = \"\\\"" << en.name() << "\\\"\";" << std::endl;
fa.stream() << "        break;" << std::endl;
            }
fa.stream() << "    default:" << std::endl;
fa.stream() << "        throw std::invalid_argument(\"Invalid value for " << e.name() << "\");" << std::endl;
fa.stream() << "    }" << std::endl;
fa.stream() << "    s << attr << \" }\";" << std::endl;
fa.stream() << "    return s;" << std::endl;
fa.stream() << "}" << std::endl;
fa.stream() << std::endl;
         } // snf
    } // sbf
    return fa.make_file();
}

} } } }
