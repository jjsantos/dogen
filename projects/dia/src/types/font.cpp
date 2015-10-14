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
#include "dogen/dia/types/font.hpp"

namespace dogen {
namespace dia {

font::font(
    const std::string& family,
    const std::string& style,
    const std::string& name)
    : family_(family),
      style_(style),
      name_(name) { }

void font::swap(font& other) noexcept {
    using std::swap;
    swap(family_, other.family_);
    swap(style_, other.style_);
    swap(name_, other.name_);
}

bool font::operator==(const font& rhs) const {
    return family_ == rhs.family_ &&
        style_ == rhs.style_ &&
        name_ == rhs.name_;
}

font& font::operator=(font other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& font::family() const {
    return family_;
}

std::string& font::family() {
    return family_;
}

void font::family(const std::string& v) {
    family_ = v;
}

void font::family(const std::string&& v) {
    family_ = std::move(v);
}

const std::string& font::style() const {
    return style_;
}

std::string& font::style() {
    return style_;
}

void font::style(const std::string& v) {
    style_ = v;
}

void font::style(const std::string&& v) {
    style_ = std::move(v);
}

const std::string& font::name() const {
    return name_;
}

std::string& font::name() {
    return name_;
}

void font::name(const std::string& v) {
    name_ = v;
}

void font::name(const std::string&& v) {
    name_ = std::move(v);
}

} }
