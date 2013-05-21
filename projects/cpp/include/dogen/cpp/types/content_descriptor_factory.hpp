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
#ifndef DOGEN_CPP_TYPES_CONTENT_DESCRIPTOR_FACTORY_HPP
#define DOGEN_CPP_TYPES_CONTENT_DESCRIPTOR_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include "dogen/sml/types/pod.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/meta_types.hpp"
#include "dogen/sml/types/pod_types.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/cpp/types/content_descriptor.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Produces all the content descriptors for the supplied
 * inputs.
 */
class content_descriptor_factory {
public:
    content_descriptor_factory() = delete;
    content_descriptor_factory(const content_descriptor_factory&) = default;
    content_descriptor_factory&
    operator=(const content_descriptor_factory&) = delete;

public:
    explicit content_descriptor_factory(
        const std::set<config::cpp_facet_types>& enabled_facets);

private:
    /**
     * @brief Returns the available facets for the given inputs.
     *
     * @param mt Meta-type which we want to process.
     * @param pt Pod type to process; must be set to invalid if the
     * meta-type is not a pod.
     */
    std::set<config::cpp_facet_types> enabled_facets(const sml::meta_types mt,
        const sml::pod_types pt) const;

    /**
     * @brief Returns true if the facet requires a C++ source file,
     * false otherwise.
     */
    bool has_implementation(const config::cpp_facet_types ft,
        const sml::meta_types mt) const;

    /**
     * @brief Returns true if facet has forward declarations, false otherwise.
     */
    bool has_forward_decls(const config::cpp_facet_types ft,
        const sml::meta_types mt) const;

public:
    /**
     * @brief Generate all of the content descriptors for the given
     * parameters.
     */
    std::list<content_descriptor> create(const sml::qname& qn,
        const sml::category_types ct = sml::category_types::invalid,
        const sml::pod_types pt = sml::pod_types::invalid) const;

    /**
     * @brief Generate a content descriptor for the model.
     *
     * @todo this is a hack to deal with a lack of qname at the model
     * level.
     */
    std::list<content_descriptor> create(const sml::model& m) const;

private:
    const std::set<config::cpp_facet_types>& enabled_facets_;
};

} }

#endif
