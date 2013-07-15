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
#include "dogen/sml/hash/nested_qname_hash.hpp"
#include "dogen/sml/hash/operation_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value)
{
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_pair_std_string_std_string(const std::pair<std::string, std::string>& v){
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_vector_std_pair_std_string_std_string_(const std::vector<std::pair<std::string, std::string> >& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_std_string_std_string(i));
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_sml_nested_qname(const std::list<dogen::sml::nested_qname>& v){
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_boost_optional_dogen_sml_nested_qname(const boost::optional<dogen::sml::nested_qname>& v){
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

}

namespace dogen {
namespace sml {

std::size_t operation_hasher::hash(const operation&v) {
    std::size_t seed(0);

    combine(seed, v.documentation());
    combine(seed, hash_std_vector_std_pair_std_string_std_string_(v.implementation_specific_parameters()));
    combine(seed, v.name());
    combine(seed, hash_std_list_dogen_sml_nested_qname(v.arguments()));
    combine(seed, hash_boost_optional_dogen_sml_nested_qname(v.return_type()));

    return seed;
}

} }