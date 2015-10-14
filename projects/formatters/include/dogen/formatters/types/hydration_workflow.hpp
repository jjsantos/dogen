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
#ifndef DOGEN_FORMATTERS_TYPES_HYDRATION_WORKFLOW_HPP
#define DOGEN_FORMATTERS_TYPES_HYDRATION_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/formatters/types/modeline_group.hpp"
#include "dogen/formatters/types/repository.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Hydrates all reference data used by the formatters model
 * into a repository.
 */
class hydration_workflow {
    /**
     * @brief Creates the list of directories to load data from.
     */
    std::forward_list<boost::filesystem::path> create_directory_list(
        const std::forward_list<boost::filesystem::path>& dirs,
        const std::string& for_whom) const;

    /**
     * @brief Hydrates all the modelines available in the library.
     */
    std::unordered_map<std::string, modeline_group> hydrate_modeline_groups(
        const std::forward_list<boost::filesystem::path>& dirs) const;

    /**
     * @brief Hydrates all the licence texts available in the library.
     */
    std::unordered_map<std::string, std::string> hydrate_licence_texts(
        const std::forward_list<boost::filesystem::path>& dirs) const;

public:
    /**
     * @brief Hydrate all files found in the supplied directories into
     * objects of the formatters' domain.
     */
    repository hydrate(
        const std::forward_list<boost::filesystem::path>& dirs) const;
};

} }

#endif
