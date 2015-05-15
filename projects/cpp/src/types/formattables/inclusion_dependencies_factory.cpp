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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("cpp.formattables.inclusion_dependencies_factory"));

const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string empty_include_directive("Include directive is empty.");

const char angle_bracket('<');
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

}

namespace dogen {
namespace cpp {
namespace formattables {

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {
    if (lhs.empty() || rhs.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_include_directive;
        BOOST_THROW_EXCEPTION(building_error(empty_include_directive));
    }

    const bool lhs_has_angle_brackets(lhs[0] == angle_bracket);
    const bool rhs_has_angle_brackets(rhs[0] == angle_bracket);

    if (lhs_has_angle_brackets && !rhs_has_angle_brackets)
        return true;

    if (!lhs_has_angle_brackets && rhs_has_angle_brackets)
        return false;

    if (lhs_has_angle_brackets && rhs_has_angle_brackets) {
        const auto npos(std::string::npos);
        const bool lhs_is_boost(lhs.find_first_of(boost_name) != npos);
        const bool rhs_is_boost(rhs.find_first_of(boost_name) != npos);
        if (!lhs_is_boost && rhs_is_boost)
            return false;

        if (lhs_is_boost && !rhs_is_boost)
            return true;

        // FIXME: hacks for headers that must be last
        const bool lhs_is_gregorian(
            lhs.find_first_of(boost_serialization_gregorian) != npos);
        const bool rhs_is_gregorian(
            rhs.find_first_of(boost_serialization_gregorian) != npos);
        if (lhs_is_gregorian && !rhs_is_gregorian)
            return true;

        if (!lhs_is_gregorian && rhs_is_gregorian)
            return false;
    }

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    return lhs < rhs;
}

template<typename SmlEntity>
std::unordered_map<std::string, std::list<std::string> >
generate(const dynamic::schema::repository& srp,
    std::forward_list<
        boost::shared_ptr<
            inclusion_dependencies_provider_interface<SmlEntity>
            >
        > providers, const inclusion_directives_repository& idrp,
    const SmlEntity& e) {

    const auto n(sml::string_converter::convert(e.name()));
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion dependencies for: " << n;

    std::unordered_map<std::string, std::list<std::string> > r;
    for (const auto p : providers) {
        BOOST_LOG_SEV(lg, debug) << "Providing for: " << p->formatter_name();
        auto id(p->provide(srp, idrp, e));

        if (!id)
            continue;

        id->sort(include_directive_comparer);
        id->unique();
        const auto id_pair(std::make_pair(p->formatter_name(), *id));
        const bool inserted(r.insert(id_pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                     << p->formatter_name()
                                     << " for type: " << n;
            BOOST_THROW_EXCEPTION(building_error(duplicate_formatter_name +
                    p->formatter_name()));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies for: "
                             << n;

    return r;
}

inclusion_dependencies_factory::inclusion_dependencies_factory(
    const dynamic::schema::repository& srp, const container& c,
    const inclusion_directives_repository& idrp)
    : schema_repository_(srp), provider_container_(c),
      inclusion_directives_repository_(idrp) {}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const sml::object& o) const {
    return generate(schema_repository_, provider_container_.object_providers(),
        inclusion_directives_repository_, o);
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const sml::enumeration& /*e*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const sml::primitive& /*p*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const sml::module& /*m*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

std::unordered_map<std::string, std::list<std::string> >
inclusion_dependencies_factory::make(const sml::concept& /*c*/) const {
    std::unordered_map<std::string, std::list<std::string> > r;
    return r;
}

} } }