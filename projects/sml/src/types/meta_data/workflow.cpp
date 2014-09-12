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
#include "dogen/sml/types/meta_data/workflow.hpp"

namespace dogen {
namespace sml {
namespace meta_data {

std::unique_ptr<registrar> workflow::registrar_;

registrar& workflow::get_registrar() {
    if (registrar_ == nullptr)
        registrar_ = std::unique_ptr<registrar>(new registrar());

    return *registrar_;
}

void workflow::
register_root_enricher(std::shared_ptr<enricher_interface> e) {
    get_registrar().register_root_enricher(e);
}

void workflow::
register_ordinary_enricher(std::shared_ptr<enricher_interface> e) {
    get_registrar().register_ordinary_enricher(e);
}

void workflow::execute(model& /*m*/) const {

}

} } }