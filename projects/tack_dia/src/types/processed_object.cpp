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
#include "dogen/tack_dia/types/processed_object.hpp"

namespace dogen {
namespace tack_dia {

processed_object::processed_object()
    : object_type_(static_cast<dogen::tack_dia::object_types>(0)) { }

processed_object::processed_object(processed_object&& rhs)
    : id_(std::move(rhs.id_)),
      name_(std::move(rhs.name_)),
      object_type_(std::move(rhs.object_type_)),
      stereotype_(std::move(rhs.stereotype_)),
      comment_(std::move(rhs.comment_)),
      child_node_id_(std::move(rhs.child_node_id_)),
      connection_(std::move(rhs.connection_)),
      properties_(std::move(rhs.properties_)) { }

processed_object::processed_object(
    const std::string& id,
    const std::string& name,
    const dogen::tack_dia::object_types object_type,
    const std::string& stereotype,
    const dogen::tack_dia::processed_comment& comment,
    const std::string& child_node_id,
    const boost::optional<std::pair<std::string, std::string> >& connection,
    const std::list<dogen::tack_dia::processed_property>& properties)
    : id_(id),
      name_(name),
      object_type_(object_type),
      stereotype_(stereotype),
      comment_(comment),
      child_node_id_(child_node_id),
      connection_(connection),
      properties_(properties) { }

void processed_object::swap(processed_object& other) noexcept {
    using std::swap;
    swap(id_, other.id_);
    swap(name_, other.name_);
    swap(object_type_, other.object_type_);
    swap(stereotype_, other.stereotype_);
    swap(comment_, other.comment_);
    swap(child_node_id_, other.child_node_id_);
    swap(connection_, other.connection_);
    swap(properties_, other.properties_);
}

bool processed_object::operator==(const processed_object& rhs) const {
    return id_ == rhs.id_ &&
        name_ == rhs.name_ &&
        object_type_ == rhs.object_type_ &&
        stereotype_ == rhs.stereotype_ &&
        comment_ == rhs.comment_ &&
        child_node_id_ == rhs.child_node_id_ &&
        connection_ == rhs.connection_ &&
        properties_ == rhs.properties_;
}

processed_object& processed_object::operator=(processed_object other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& processed_object::id() const {
    return id_;
}

std::string& processed_object::id() {
    return id_;
}

void processed_object::id(const std::string& v) {
    id_ = v;
}

void processed_object::id(const std::string&& v) {
    id_ = std::move(v);
}

const std::string& processed_object::name() const {
    return name_;
}

std::string& processed_object::name() {
    return name_;
}

void processed_object::name(const std::string& v) {
    name_ = v;
}

void processed_object::name(const std::string&& v) {
    name_ = std::move(v);
}

dogen::tack_dia::object_types processed_object::object_type() const {
    return object_type_;
}

void processed_object::object_type(const dogen::tack_dia::object_types v) {
    object_type_ = v;
}

const std::string& processed_object::stereotype() const {
    return stereotype_;
}

std::string& processed_object::stereotype() {
    return stereotype_;
}

void processed_object::stereotype(const std::string& v) {
    stereotype_ = v;
}

void processed_object::stereotype(const std::string&& v) {
    stereotype_ = std::move(v);
}

const dogen::tack_dia::processed_comment& processed_object::comment() const {
    return comment_;
}

dogen::tack_dia::processed_comment& processed_object::comment() {
    return comment_;
}

void processed_object::comment(const dogen::tack_dia::processed_comment& v) {
    comment_ = v;
}

void processed_object::comment(const dogen::tack_dia::processed_comment&& v) {
    comment_ = std::move(v);
}

const std::string& processed_object::child_node_id() const {
    return child_node_id_;
}

std::string& processed_object::child_node_id() {
    return child_node_id_;
}

void processed_object::child_node_id(const std::string& v) {
    child_node_id_ = v;
}

void processed_object::child_node_id(const std::string&& v) {
    child_node_id_ = std::move(v);
}

const boost::optional<std::pair<std::string, std::string> >& processed_object::connection() const {
    return connection_;
}

boost::optional<std::pair<std::string, std::string> >& processed_object::connection() {
    return connection_;
}

void processed_object::connection(const boost::optional<std::pair<std::string, std::string> >& v) {
    connection_ = v;
}

void processed_object::connection(const boost::optional<std::pair<std::string, std::string> >&& v) {
    connection_ = std::move(v);
}

const std::list<dogen::tack_dia::processed_property>& processed_object::properties() const {
    return properties_;
}

std::list<dogen::tack_dia::processed_property>& processed_object::properties() {
    return properties_;
}

void processed_object::properties(const std::list<dogen::tack_dia::processed_property>& v) {
    properties_ = v;
}

void processed_object::properties(const std::list<dogen::tack_dia::processed_property>&& v) {
    properties_ = std::move(v);
}

} }
