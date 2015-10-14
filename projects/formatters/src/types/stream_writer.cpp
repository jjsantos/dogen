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
#include "dogen/formatters/types/stream_writer.hpp"

namespace {

const std::string outputter_name("Stream outputter");
const std::string file_name("Filename: ");
const std::string content("Content: ");

}

namespace dogen {
namespace formatters {

stream_writer::stream_writer(std::ostream& s) : stream_(s) {}

void stream_writer::write(const std::forward_list<file>& files) const {
    for (const auto& f : files) {
        stream_ << file_name << f.path().generic_string() << std::endl
                << content << std::endl << f.content() << std::endl;
    }
}

} }
