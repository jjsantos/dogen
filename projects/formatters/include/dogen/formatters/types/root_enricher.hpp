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
#ifndef DOGEN_SML_TYPES_META_DATA_ROOT_ENRICHER_HPP
#define DOGEN_SML_TYPES_META_DATA_ROOT_ENRICHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/sml/types/meta_data/enricher_interface.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Responsible for enriching the meta-data with the core
 * formatter tags.
 */
class root_enricher : public sml::meta_data::enricher_interface {
public:
    virtual std::string id() const override;

    virtual std::list<std::string> dependencies() const override;

    virtual void first_stage_enrichment(const sml::model& model,
        sml::concept& target) override;
    virtual void first_stage_enrichment(const sml::model& model,
        sml::module& target) override;
    virtual void first_stage_enrichment(const sml::model& model,
        sml::type& target) override;

    virtual void second_stage_enrichment(const sml::model& model,
        sml::concept& target) override;
    virtual void second_stage_enrichment(const sml::model& model,
        sml::module& target) override;
    virtual void second_stage_enrichment(const sml::model& model,
        sml::type& target) override;
};

} }

#endif
