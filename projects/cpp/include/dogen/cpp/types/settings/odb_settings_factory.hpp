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
#ifndef DOGEN_CPP_TYPES_SETTINGS_ODB_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_ODB_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/cpp/types/settings/opaque_settings_factory_interface.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class odb_settings_factory final : public opaque_settings_factory_interface {
public:
    ~odb_settings_factory() noexcept;

private:
    /**
     * @brief All field definitions we require.
     */
    struct field_definitions {
        dynamic::field_definition odb_pragma;
    };

public:
    std::string settings_key() const override;

    void setup(const dynamic::repository& rp) override;

    boost::shared_ptr<opaque_settings>
        make(const dynamic::object& o) const override;

private:
    boost::shared_ptr<field_definitions> field_definitions_;
};

} } }

#endif
