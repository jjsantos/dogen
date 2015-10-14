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
#ifndef DOGEN_TEST_MODELS_STEREOTYPES_TYPES_STEREOTYPES_HPP
#define DOGEN_TEST_MODELS_STEREOTYPES_TYPES_STEREOTYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace test_models {

/**
 * @brief Test model for all of the stereotype related scenarios.
 *
 * These are the main cases:
 *
 * @li @e immutability: pods that have no setters, assignment, etc.
 * @li @e fluency: pods with setters which return this
 * @li @e generability: pods which are marked as non-generatable
 * @li @e value and @e enttiy: value and entity pods.
 * @li @e service: pods marked as service - non-generatable.
 * @li @e entity: pods marked as entity must have an identity
 * @li @e keyed: entities marked as keyed will generate external keys.
 *
 */
namespace stereotypes {
}

} }

#endif
