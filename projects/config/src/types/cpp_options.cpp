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
#include "dogen/config/types/cpp_options.hpp"

namespace dogen {
namespace config {

cpp_options::cpp_options()
    : disable_cmakelists_(static_cast<bool>(0)) { }

cpp_options::cpp_options(cpp_options&& rhs)
    : project_directory_path_(std::move(rhs.project_directory_path_)),
      disable_cmakelists_(std::move(rhs.disable_cmakelists_)) { }

cpp_options::cpp_options(
    const boost::filesystem::path& project_directory_path,
    const bool disable_cmakelists)
    : project_directory_path_(project_directory_path),
      disable_cmakelists_(disable_cmakelists) { }

void cpp_options::swap(cpp_options& other) noexcept {
    using std::swap;
    swap(project_directory_path_, other.project_directory_path_);
    swap(disable_cmakelists_, other.disable_cmakelists_);
}

bool cpp_options::operator==(const cpp_options& rhs) const {
    return project_directory_path_ == rhs.project_directory_path_ &&
        disable_cmakelists_ == rhs.disable_cmakelists_;
}

cpp_options& cpp_options::operator=(cpp_options other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& cpp_options::project_directory_path() const {
    return project_directory_path_;
}

boost::filesystem::path& cpp_options::project_directory_path() {
    return project_directory_path_;
}

void cpp_options::project_directory_path(const boost::filesystem::path& v) {
    project_directory_path_ = v;
}

void cpp_options::project_directory_path(const boost::filesystem::path&& v) {
    project_directory_path_ = std::move(v);
}

bool cpp_options::disable_cmakelists() const {
    return disable_cmakelists_;
}

void cpp_options::disable_cmakelists(const bool v) {
    disable_cmakelists_ = v;
}

} }
