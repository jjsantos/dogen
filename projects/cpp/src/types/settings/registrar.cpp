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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/settings/opaque_settings_factory_interface.hpp"
#include "dogen/cpp/types/settings/registrar_error.hpp"
#include "dogen/cpp/types/settings/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.registrar"));

const std::string no_factories(
    "No opaque settings factories have been provided.");
const std::string null_factory(
    "Opaque settings factory supplied is null");

}

namespace dogen {
namespace cpp {
namespace settings {

void registrar::validate() const {
    if (opaque_settings_factories_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_factories;
        BOOST_THROW_EXCEPTION(registrar_error(no_factories));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void registrar::register_opaque_settings_factory(
    boost::shared_ptr<opaque_settings_factory_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_factory));

    opaque_settings_factories_.push_front(f);
}

const std::forward_list<
    boost::shared_ptr<opaque_settings_factory_interface>
    >& registrar::opaque_settings_factories() const {
    return opaque_settings_factories_;
}

} } }
