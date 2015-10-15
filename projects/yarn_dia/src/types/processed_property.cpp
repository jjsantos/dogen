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
#include "dogen/yarn_dia/types/processed_property.hpp"

namespace dogen {
namespace yarn_dia {

processed_property::processed_property(
    const std::string& name,
    const std::string& type,
    const dogen::yarn_dia::processed_comment& comment)
    : name_(name),
      type_(type),
      comment_(comment) { }

void processed_property::swap(processed_property& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(type_, other.type_);
    swap(comment_, other.comment_);
}

bool processed_property::operator==(const processed_property& rhs) const {
    return name_ == rhs.name_ &&
        type_ == rhs.type_ &&
        comment_ == rhs.comment_;
}

processed_property& processed_property::operator=(processed_property other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& processed_property::name() const {
    return name_;
}

std::string& processed_property::name() {
    return name_;
}

void processed_property::name(const std::string& v) {
    name_ = v;
}

void processed_property::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::string& processed_property::type() const {
    return type_;
}

std::string& processed_property::type() {
    return type_;
}

void processed_property::type(const std::string& v) {
    type_ = v;
}

void processed_property::type(const std::string&& v) {
    type_ = std::move(v);
}

const dogen::yarn_dia::processed_comment& processed_property::comment() const {
    return comment_;
}

dogen::yarn_dia::processed_comment& processed_property::comment() {
    return comment_;
}

void processed_property::comment(const dogen::yarn_dia::processed_comment& v) {
    comment_ = v;
}

void processed_property::comment(const dogen::yarn_dia::processed_comment&& v) {
    comment_ = std::move(v);
}

} }
