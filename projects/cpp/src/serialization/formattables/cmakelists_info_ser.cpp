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
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/utility/serialization/path.hpp"
#include "dogen/formatters/serialization/general_settings_ser.hpp"
#include "dogen/cpp/serialization/formattables/formattable_ser.hpp"
#include "dogen/cpp/serialization/formattables/cmakelists_info_ser.hpp"

BOOST_CLASS_TRACKING(
    dogen::cpp::formattables::cmakelists_info,
    boost::serialization::track_selectively)

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::cpp::formattables::cmakelists_info& v,
    const unsigned int /*version*/) {
    ar << make_nvp("formattable", base_object<dogen::cpp::formattables::formattable>(v));

    ar << make_nvp("file_path", v.file_path_.generic_string());
    ar << make_nvp("model_name", v.model_name_);
    ar << make_nvp("product_name", v.product_name_);
    ar << make_nvp("file_name", v.file_name_);
    ar << make_nvp("source_file_path", v.source_file_path_.generic_string());
    ar << make_nvp("include_file_path", v.include_file_path_.generic_string());
    ar << make_nvp("general_settings", v.general_settings_);
    ar << make_nvp("odb_folder", v.odb_folder_);
    ar << make_nvp("odb_enabled", v.odb_enabled_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::cpp::formattables::cmakelists_info& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("formattable", base_object<dogen::cpp::formattables::formattable>(v));

    std::string file_path_tmp;
    ar >> make_nvp("file_path", file_path_tmp);
    v.file_path_ = file_path_tmp;
    ar >> make_nvp("model_name", v.model_name_);
    ar >> make_nvp("product_name", v.product_name_);
    ar >> make_nvp("file_name", v.file_name_);
    std::string source_file_path_tmp;
    ar >> make_nvp("source_file_path", source_file_path_tmp);
    v.source_file_path_ = source_file_path_tmp;
    std::string include_file_path_tmp;
    ar >> make_nvp("include_file_path", include_file_path_tmp);
    v.include_file_path_ = include_file_path_tmp;
    ar >> make_nvp("general_settings", v.general_settings_);
    ar >> make_nvp("odb_folder", v.odb_folder_);
    ar >> make_nvp("odb_enabled", v.odb_enabled_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::cpp::formattables::cmakelists_info& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::cpp::formattables::cmakelists_info& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::cpp::formattables::cmakelists_info& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::cpp::formattables::cmakelists_info& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::cpp::formattables::cmakelists_info& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::cpp::formattables::cmakelists_info& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::cpp::formattables::cmakelists_info& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::cpp::formattables::cmakelists_info& v, unsigned int version);

} }
