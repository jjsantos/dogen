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
#ifndef DOGEN_STITCH_TYPES_STITCHING_SETTINGS_HPP
#define DOGEN_STITCH_TYPES_STITCHING_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen/stitch/serialization/stitching_settings_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class stitching_settings final {
public:
    stitching_settings() = default;
    stitching_settings(const stitching_settings&) = default;
    ~stitching_settings() = default;

public:
    stitching_settings(stitching_settings&& rhs);

public:
    stitching_settings(
        const std::string& stream_variable_name,
        const boost::optional<boost::filesystem::path>& template_path,
        const boost::optional<boost::filesystem::path>& output_path,
        const boost::optional<boost::filesystem::path>& relative_output_directory,
        const std::list<std::string>& inclusion_dependencies,
        const std::list<std::string>& containing_namespaces);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const stitching_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, stitching_settings& v, unsigned int version);

public:
    const std::string& stream_variable_name() const;
    std::string& stream_variable_name();
    void stream_variable_name(const std::string& v);
    void stream_variable_name(const std::string&& v);

    const boost::optional<boost::filesystem::path>& template_path() const;
    boost::optional<boost::filesystem::path>& template_path();
    void template_path(const boost::optional<boost::filesystem::path>& v);
    void template_path(const boost::optional<boost::filesystem::path>&& v);

    const boost::optional<boost::filesystem::path>& output_path() const;
    boost::optional<boost::filesystem::path>& output_path();
    void output_path(const boost::optional<boost::filesystem::path>& v);
    void output_path(const boost::optional<boost::filesystem::path>&& v);

    const boost::optional<boost::filesystem::path>& relative_output_directory() const;
    boost::optional<boost::filesystem::path>& relative_output_directory();
    void relative_output_directory(const boost::optional<boost::filesystem::path>& v);
    void relative_output_directory(const boost::optional<boost::filesystem::path>&& v);

    const std::list<std::string>& inclusion_dependencies() const;
    std::list<std::string>& inclusion_dependencies();
    void inclusion_dependencies(const std::list<std::string>& v);
    void inclusion_dependencies(const std::list<std::string>&& v);

    const std::list<std::string>& containing_namespaces() const;
    std::list<std::string>& containing_namespaces();
    void containing_namespaces(const std::list<std::string>& v);
    void containing_namespaces(const std::list<std::string>&& v);

public:
    bool operator==(const stitching_settings& rhs) const;
    bool operator!=(const stitching_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(stitching_settings& other) noexcept;
    stitching_settings& operator=(stitching_settings other);

private:
    std::string stream_variable_name_;
    boost::optional<boost::filesystem::path> template_path_;
    boost::optional<boost::filesystem::path> output_path_;
    boost::optional<boost::filesystem::path> relative_output_directory_;
    std::list<std::string> inclusion_dependencies_;
    std::list<std::string> containing_namespaces_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::stitching_settings& lhs,
    dogen::stitch::stitching_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
