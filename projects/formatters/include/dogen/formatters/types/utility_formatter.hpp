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
#ifndef DOGEN_FORMATTERS_TYPES_UTILITY_FORMATTER_HPP
#define DOGEN_FORMATTERS_TYPES_UTILITY_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <ostream>
#include "dogen/formatters/types/quote_types.hpp"
#include "dogen/formatters/types/spacing_types.hpp"

namespace dogen {
namespace formatters {

/**
 * @brief Mixed grab-bag of formatting utilities.
 */
class utility_formatter {
public:
    explicit utility_formatter(std::ostream& s);

private:
    /**
     * @brief Inserts a quote to the stream.
     */
    void insert_quote(const quote_types qt) const;

    /**
     * @brief Escapes a quote.
     */
    std::string escape_quote(const std::string& s, const quote_types qt) const;

public:
    /**
     * @brief Insert content to stream, using the supplied space
     * flags.
     */
    void insert(const std::string& s,
        const spacing_types st = spacing_types::no_space) const;

    /**
     * @brief Inserts the content, but escapes any quotes.
     */
    void insert_escaped(const std::string& s,
        const quote_types qt = quote_types::double_quote,
        const spacing_types st = spacing_types::no_space) const;

    /**
     * @brief Quotes the supplied content.
     */
    void insert_quoted(const std::string& s,
        const bool escape_content = false,
        const quote_types qt = quote_types::double_quote,
        const spacing_types st = spacing_types::no_space) const;

    /**
     * @brief Quotes the supplied content, and places it inside
     * escaped quotes.
     *
     * For an input of 'a', outputs '"\"a\""'.
     */
    void insert_quoted_escaped(const std::string& s) const;

    /**
     * @brief Adds escapped quotes to s, with c++ streaming syntax.
     *
     * Using single quotes to denote the string boundary (e.g. they
     * are not actually on the string), an s of 'a' produces the
     * output '<< "\"" << a << "\"""'.
     */
    void insert_streamed(const std::string& s) const;

public:
    std::ostream& stream_;
};

} }

#endif
