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
#include "dogen/classes_without_package/test_data/class_1_td.hpp"
#include "dogen/classes_without_package/test_data/versioned_key_td.hpp"

namespace {

dogen::classes_without_package::versioned_key
create_dogen_classes_without_package_versioned_key(const unsigned int position) {
    return dogen::classes_without_package::versioned_key_generator::create(position);
}

}

namespace dogen {
namespace classes_without_package {

class_1_generator::class_1_generator() : position_(0) { }

void class_1_generator::
populate(const unsigned int position, result_type& v) {
    v.versioned_key(create_dogen_classes_without_package_versioned_key(position + 0));
}

class_1_generator::result_type
class_1_generator::create(const unsigned int position) {
    class_1 r;
    class_1_generator::populate(position, r);
    return r;
}
class_1_generator::result_type*
class_1_generator::create_ptr(const unsigned int position) {
    class_1* p = new class_1();
    class_1_generator::populate(position, *p);
    return p;
}

class_1_generator::result_type
class_1_generator::operator()() {
    return create(position_++);
}

} }
