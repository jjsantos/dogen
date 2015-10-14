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
#ifndef DOGEN_CPP_TYPES_SETTINGS_BUNDLE_HPP
#define DOGEN_CPP_TYPES_SETTINGS_BUNDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/settings/aspect_settings.hpp"
#include "dogen/cpp/types/settings/opaque_settings_fwd.hpp"
#include "dogen/cpp/serialization/settings/bundle_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class bundle final {
public:
    bundle() = default;
    bundle(const bundle&) = default;
    ~bundle() = default;

public:
    bundle(bundle&& rhs);

public:
    bundle(
        const boost::optional<dogen::formatters::general_settings>& general_settings,
        const dogen::cpp::settings::aspect_settings& aspect_settings,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& opaque_settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const bundle& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, bundle& v, unsigned int version);

public:
    const boost::optional<dogen::formatters::general_settings>& general_settings() const;
    boost::optional<dogen::formatters::general_settings>& general_settings();
    void general_settings(const boost::optional<dogen::formatters::general_settings>& v);
    void general_settings(const boost::optional<dogen::formatters::general_settings>&& v);

    const dogen::cpp::settings::aspect_settings& aspect_settings() const;
    dogen::cpp::settings::aspect_settings& aspect_settings();
    void aspect_settings(const dogen::cpp::settings::aspect_settings& v);
    void aspect_settings(const dogen::cpp::settings::aspect_settings&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& opaque_settings() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& opaque_settings();
    void opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >& v);
    void opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> >&& v);

public:
    bool operator==(const bundle& rhs) const;
    bool operator!=(const bundle& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(bundle& other) noexcept;
    bundle& operator=(bundle other);

private:
    boost::optional<dogen::formatters::general_settings> general_settings_;
    dogen::cpp::settings::aspect_settings aspect_settings_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> > opaque_settings_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::bundle& lhs,
    dogen::cpp::settings::bundle& rhs) {
    lhs.swap(rhs);
}

}

#endif
