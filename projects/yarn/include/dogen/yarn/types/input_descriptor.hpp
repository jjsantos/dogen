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
#ifndef DOGEN_YARN_TYPES_INPUT_DESCRIPTOR_HPP
#define DOGEN_YARN_TYPES_INPUT_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/yarn/serialization/input_descriptor_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Describes an input to process.
 */
class input_descriptor final {
public:
    input_descriptor(const input_descriptor&) = default;
    ~input_descriptor() = default;

public:
    input_descriptor();

public:
    input_descriptor(input_descriptor&& rhs);

public:
    input_descriptor(
        const boost::filesystem::path& path,
        const std::string& external_module_path,
        const bool is_target);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const input_descriptor& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, input_descriptor& v, unsigned int version);

public:
    /**
     * @brief Location of the input.
     */
    /**@{*/
    const boost::filesystem::path& path() const;
    boost::filesystem::path& path();
    void path(const boost::filesystem::path& v);
    void path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief External modules which contain the model, delimited by "::".
     */
    /**@{*/
    const std::string& external_module_path() const;
    std::string& external_module_path();
    void external_module_path(const std::string& v);
    void external_module_path(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the input contains the target model.
     */
    /**@{*/
    bool is_target() const;
    void is_target(const bool v);
    /**@}*/

public:
    bool operator==(const input_descriptor& rhs) const;
    bool operator!=(const input_descriptor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(input_descriptor& other) noexcept;
    input_descriptor& operator=(input_descriptor other);

private:
    boost::filesystem::path path_;
    std::string external_module_path_;
    bool is_target_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::input_descriptor& lhs,
    dogen::yarn::input_descriptor& rhs) {
    lhs.swap(rhs);
}

}

#endif
