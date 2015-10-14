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
#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("formatters.filesystem_writer"));

const std::string using_dir_message("Using directory: ");
const std::string created_dir_message("Created directory: ");

std::string create_hacked_contents(const std::string file_name) {
    std::ostringstream ss;

    ss << "// dummy function to suppress ranlib warnings" << std::endl
       << "void " << file_name << "() { }"
       << std::endl;

    return ss.str();
}

}

namespace dogen {
namespace formatters {

filesystem_writer::filesystem_writer(const bool force_write)
    : force_write_(force_write) {}

bool filesystem_writer::content_changed(const file& f) const {
    if (force_write_)
        return true;

    if (!boost::filesystem::exists(f.path()))
        return true;

    using dogen::utility::filesystem::read_file_content;
    const std::string existing_content(read_file_content(f.path()));

    if (existing_content == f.content()) {
        BOOST_LOG_SEV(lg, debug) << "File contents have not changed, "
                                 << "and force write is false so not writing.";
        return false;
    }

    BOOST_LOG_SEV(lg, debug) << "File contents have changed, need to write";
    return true;
}

void filesystem_writer::create_directories(
    const boost::filesystem::path& file_path) const {
    const auto dir(file_path.parent_path());
    if (dir.empty() || dir.generic_string() == "/")
        return;

    using boost::filesystem::create_directories;
    const bool created(create_directories(dir));
    BOOST_LOG_SEV(lg, debug) << (created ? created_dir_message :
        using_dir_message) << dir.generic_string();
}

void filesystem_writer::write_empty_file(const formatters::file& f) const {
    const auto gs(f.path().generic_string());
    if (boost::filesystem::exists(f.path())) {
        BOOST_LOG_SEV(lg, debug) << "File has no content so no writing: " << gs;
        return;
    }

    // FIXME: massive hack to deal with ranlib warnings on OSX
    const auto fn(f.path().stem().generic_string());
    const auto hc(create_hacked_contents(fn));

    using dogen::utility::filesystem::write_file_content;
    if (boost::ends_with(gs, ".cpp"))
        write_file_content(f.path(), hc);
    else
        write_file_content(f.path(), f.content());

    return;
}


void filesystem_writer::write(const formatters::file& f) const {
    const auto gs(f.path().generic_string());
    BOOST_LOG_SEV(lg, debug) << "Processing file: " << gs;

    if (gs.empty()) {
        // FIXME: throw
        BOOST_LOG_SEV(lg, error) << "Empty file name supplied.";
        return;
    }

    create_directories(f.path());
    if (f.content().empty()) {
        write_empty_file(f);
        return;
    }

    using dogen::utility::filesystem::write_file_content;
    if (content_changed(f)) {
        BOOST_LOG_SEV(lg, debug) << "File contents have changed.";
        write_file_content(f.path(), f.content());
        BOOST_LOG_SEV(lg, debug) << "Wrote file: " << gs;
    } else {
        BOOST_LOG_SEV(lg, debug) << "File contents have not changed, "
                                 << "and force write is false so not writing.";
    }
}

void filesystem_writer::write(const std::forward_list<file>& files) const {
    for (const auto& f : files)
        write(f);
}

} }
