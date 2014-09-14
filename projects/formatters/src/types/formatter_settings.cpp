/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/formatters/types/formatter_settings.hpp"

namespace dogen {
namespace formatters {

formatter_settings::formatter_settings()
    : generate_preamble_(static_cast<bool>(0)) { }

formatter_settings::formatter_settings(
    const bool generate_preamble,
    const dogen::formatters::annotation& annotation)
    : generate_preamble_(generate_preamble),
      annotation_(annotation) { }

void formatter_settings::swap(formatter_settings& other) noexcept {
    using std::swap;
    swap(generate_preamble_, other.generate_preamble_);
    swap(annotation_, other.annotation_);
}

bool formatter_settings::operator==(const formatter_settings& rhs) const {
    return generate_preamble_ == rhs.generate_preamble_ &&
        annotation_ == rhs.annotation_;
}

formatter_settings& formatter_settings::operator=(formatter_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool formatter_settings::generate_preamble() const {
    return generate_preamble_;
}

void formatter_settings::generate_preamble(const bool v) {
    generate_preamble_ = v;
}

const dogen::formatters::annotation& formatter_settings::annotation() const {
    return annotation_;
}

dogen::formatters::annotation& formatter_settings::annotation() {
    return annotation_;
}

void formatter_settings::annotation(const dogen::formatters::annotation& v) {
    annotation_ = v;
}

void formatter_settings::annotation(const dogen::formatters::annotation&& v) {
    annotation_ = std::move(v);
}

} }