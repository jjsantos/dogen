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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/test_models/trivial_inheritance/serialization/pkg1/child_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg3/child_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/pkg4/child_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/descendant2_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/descendant3_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_of_a_child1_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_of_a_child2_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_with_members_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/move_ctor_descendant_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/child_without_members_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/move_ctor_empty_descendant_ser.hpp"
#include "dogen/test_models/trivial_inheritance/serialization/second_child_without_members_ser.hpp"

namespace dogen {
namespace test_models {
namespace trivial_inheritance {

template<typename Archive>
void register_types(Archive& ar) {
    ar.template register_type<dogen::test_models::trivial_inheritance::child_of_a_child1>();
    ar.template register_type<dogen::test_models::trivial_inheritance::child_of_a_child2>();
    ar.template register_type<dogen::test_models::trivial_inheritance::child_with_members>();
    ar.template register_type<dogen::test_models::trivial_inheritance::child_without_members>();
    ar.template register_type<dogen::test_models::trivial_inheritance::descendant2>();
    ar.template register_type<dogen::test_models::trivial_inheritance::descendant3>();
    ar.template register_type<dogen::test_models::trivial_inheritance::move_ctor_descendant>();
    ar.template register_type<dogen::test_models::trivial_inheritance::move_ctor_empty_descendant>();
    ar.template register_type<dogen::test_models::trivial_inheritance::pkg1::child>();
    ar.template register_type<dogen::test_models::trivial_inheritance::pkg3::child>();
    ar.template register_type<dogen::test_models::trivial_inheritance::pkg4::child>();
    ar.template register_type<dogen::test_models::trivial_inheritance::second_child_without_members>();
}

template void register_types(boost::archive::polymorphic_oarchive& ar);
template void register_types(boost::archive::polymorphic_iarchive& ar);

template void register_types(boost::archive::text_oarchive& ar);
template void register_types(boost::archive::text_iarchive& ar);

template void register_types(boost::archive::binary_oarchive& ar);
template void register_types(boost::archive::binary_iarchive& ar);

template void register_types(boost::archive::xml_oarchive& ar);
template void register_types(boost::archive::xml_iarchive& ar);

} } }
