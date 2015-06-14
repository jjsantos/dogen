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
#include "dogen/cpp/types/formatters/hash/pair_helper_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace hash {

void pair_helper_stitch(
    formatters::nested_type_formatting_assistant& fa,
    const formattables::nested_type_info& t) {

    {
        auto snf(fa.make_scoped_namespace_formatter(t));
        const auto first(t.children().front());
        const auto second(t.children().back());
fa.stream() << "inline std::size_t hash_" << t.complete_identifiable_name() << "(const " << t.complete_name() << "& v) {" << std::endl;
fa.stream() << "    std::size_t seed(0);" << std::endl;
fa.stream() << std::endl;
        if (!fa.requires_hashing_helper_method(first))
fa.stream() << "    combine(seed, v.first);" << std::endl;
        else
fa.stream() << "    combine(seed, hash_" << first.complete_identifiable_name() << "(v.first));" << std::endl;

        if (!fa.requires_hashing_helper_method(second))
fa.stream() << "    combine(seed, v.second);" << std::endl;
        else
fa.stream() << "    combine(seed, hash_" << second.complete_identifiable_name() << "(v.second));" << std::endl;
fa.stream() << "    return seed;" << std::endl;
    }
fa.stream() << std::endl;
}
} } } }