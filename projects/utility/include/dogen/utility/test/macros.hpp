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
#ifndef DOGEN_UTILITY_TEST_MACROS_HPP
#define DOGEN_UTILITY_TEST_MACROS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Macro for compiling test code that should fail to compile.
 *
 * This is used for example for ensuring that certain classes are
 * non-copyable, etc.
 */

#ifdef DOGEN_TEST_COMPILATION
#define DOGEN_COMPILE_BROKEN_CODE
#else
#undef DOGEN_COMPILE_BROKEN_CODE
#endif

#ifdef BOOST_IGNORE_AUTO_TEST_CASE
#undef
#endif
#define BOOST_IGNORE_AUTO_TEST_CASE(test_name) void test_name()

#endif
