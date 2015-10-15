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
#ifndef DOGEN_YARN_TYPES_NODE_HPP
#define DOGEN_YARN_TYPES_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/node_fwd.hpp"
#include "dogen/yarn/serialization/node_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class node final {
public:
    node() = default;
    node(const node&) = default;
    node(node&&) = default;
    ~node() = default;

public:
    node(
        const boost::shared_ptr<dogen::yarn::node>& parent,
        const dogen::yarn::name& data,
        const std::list<boost::shared_ptr<dogen::yarn::node> >& children);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const node& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, node& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::yarn::node>& parent() const;
    boost::shared_ptr<dogen::yarn::node>& parent();
    void parent(const boost::shared_ptr<dogen::yarn::node>& v);
    void parent(const boost::shared_ptr<dogen::yarn::node>&& v);

    const dogen::yarn::name& data() const;
    dogen::yarn::name& data();
    void data(const dogen::yarn::name& v);
    void data(const dogen::yarn::name&& v);

    const std::list<boost::shared_ptr<dogen::yarn::node> >& children() const;
    std::list<boost::shared_ptr<dogen::yarn::node> >& children();
    void children(const std::list<boost::shared_ptr<dogen::yarn::node> >& v);
    void children(const std::list<boost::shared_ptr<dogen::yarn::node> >&& v);

public:
    bool operator==(const node& rhs) const;
    bool operator!=(const node& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(node& other) noexcept;
    node& operator=(node other);

private:
    boost::shared_ptr<dogen::yarn::node> parent_;
    dogen::yarn::name data_;
    std::list<boost::shared_ptr<dogen::yarn::node> > children_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::node& lhs,
    dogen::yarn::node& rhs) {
    lhs.swap(rhs);
}

}

#endif
