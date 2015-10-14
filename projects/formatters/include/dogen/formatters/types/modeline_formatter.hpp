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
#ifndef DOGEN_FORMATTERS_TYPES_MODELINE_FORMATTER_HPP
#define DOGEN_FORMATTERS_TYPES_MODELINE_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include "dogen/formatters/types/modeline.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Creates a modeline, ready to be wrapped in comments.
 *
 * Note that the name @modeline is slightly misleading because a
 * bottom modeline may actually have more than one line. To wrap it
 * into comments one must iterate through the lines.
 *
 */
class modeline_formatter {
public:
    modeline_formatter() = default;
    modeline_formatter(const modeline_formatter&) = default;
    modeline_formatter& operator=(const modeline_formatter&) = delete;
    modeline_formatter(modeline_formatter&& rhs) = default;

private:
    /**
     * @brief Returns true if the target editor is vim.
     */
    bool is_vim(const modeline& m) const;

    /**
     * @brief Returns true if the target editor is emacs.
     */
    bool is_emacs(const modeline& m) const;

    /**
     * @brief Returns true if the modeline should be placed at the top
     * of the file.
     */
    bool is_top_line(const modeline& m) const;

    /**
     * @brief Returns true if the modeline should be placed at the bottom
     * of the file.
     */
    bool is_bottom_line(const modeline& m) const;

private:
    /**
     * @brief Creates a modeline for the vim editor.
     */
    void vim_modeline(std::ostream& s, const modeline& m) const;

    /**
     * @brief Creates a modeline for the emacs editor, first line.
     */
    void emacs_top_modeline(std::ostream& s, const modeline& m) const;

    /**
     * @brief Creates a modeline for the emacs editor, last lines.
     */
    void emacs_bottom_modeline(std::ostream& s, const modeline& m) const;

public:
    void format(std::ostream& s, const modeline& m) const;
};

} }

#endif
