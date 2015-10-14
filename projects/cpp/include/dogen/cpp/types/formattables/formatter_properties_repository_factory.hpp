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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_REPOSITORY_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_REPOSITORY_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/config/types/cpp_options.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/cpp/types/settings/path_settings.hpp"
#include "dogen/cpp/types/settings/bundle_repository.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/registrar.hpp"
#include "dogen/cpp/types/formattables/enablement_repository.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository.hpp"
#include "dogen/cpp/types/formattables/integrated_facets_repository.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_directives_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_repository.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_builder_factory.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the formatter properties repository.
 */
class formatter_properties_repository_factory {
private:
    struct merged_formatter_data {
        std::unordered_map<std::string, path_derivatives> path_derivatives_;
        std::unordered_map<std::string, std::list<std::string> >
        inclusion_dependencies;
        std::unordered_map<std::string, bool> enablement;
    };

private:
    /**
     * @brief Initialises the registrar with all the providers sourced
     * from the formatters container.
     */
    void initialise_registrar(const formatters::container& c,
        registrar& rg) const;

private:
    /**
     * @brief Create the inclusion directives repository.
     */
    inclusion_directives_repository create_inclusion_directives_repository(
        const dynamic::repository& srp,
        const formatters::container& fc,
        const path_derivatives_repository& pdrp,
        const tack::model& m) const;

    /**
     * @brief Create the inclusion dependencies repository.
     */
    inclusion_dependencies_repository create_inclusion_dependencies_repository(
        const inclusion_dependencies_builder_factory& bf,
        const container& pc, const tack::model& m) const;

    /**
     * @brief Creates the enablement repository.
     */
    enablement_repository
    create_enablement_repository(const dynamic::repository& srp,
        const dynamic::object& root_object,
        const formatters::container& fc, const tack::model& m) const;

    /**
     * @brief Creates integrated facets repository
     */
    integrated_facets_repository create_integrated_facets_repository(
        const dynamic::repository& srp,
        const dynamic::object& root_object,
        const formatters::container& fc) const;

    /**
     * @brief Merge all data structures.
     */
    std::unordered_map<tack::name, merged_formatter_data>
    merge(const path_derivatives_repository& pdrp,
        const inclusion_dependencies_repository& idrp,
        const enablement_repository& erp) const;

    /**
     * @brief Produce the formatter properties.
     */
    formatter_properties_repository
    create_formatter_properties(
        const std::unordered_map<tack::name, merged_formatter_data>& mfd,
        const integrated_facets_repository& ifrp) const;

public:
    formatter_properties_repository make(
        const dynamic::repository& srp,
        const dynamic::object& root_object,
        const settings::bundle_repository& brp,
        const path_derivatives_repository& pdrp,
        const formatters::container& fc,
        const tack::model& m) const;
};

} } }

#endif
