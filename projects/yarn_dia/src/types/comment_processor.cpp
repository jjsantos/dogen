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
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn_dia/types/traits.hpp"
#include "dogen/yarn_dia/types/processing_error.hpp"
#include "dogen/yarn_dia/types/comment_processor.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("yarn_dia.comment_processor"));

const std::string empty;
const std::string instruction_marker("#DOGEN ");
const std::string equals("=");
const std::string separator_not_found("Expected separator on KVP.");

}

namespace dogen {
namespace yarn_dia {

processed_comment comment_processor::process(const std::string& c) const {
    processed_comment r;

    if (c.empty())
        return r;

    r.original_content(c);
    std::istringstream comments_stream(c);
    std::ostringstream documentation_stream;
    std::string line;
    bool applicable_to_parent_object(false);
    while (std::getline(comments_stream, line)) {
        if (boost::starts_with(line, instruction_marker)) {
            boost::replace_all(line, instruction_marker, empty);

            const auto pos(line.find_first_of(equals));
            if (pos == std::string::npos) {
                BOOST_LOG_SEV(lg, error) << separator_not_found;
                BOOST_THROW_EXCEPTION(processing_error(separator_not_found));
            }

            const auto key(line.substr(0, pos));
            const auto value(line.substr(pos + 1));
            applicable_to_parent_object |= (key == traits::comment());
            r.key_value_pairs().push_back(std::make_pair(key, value));
        } else
            documentation_stream << line << std::endl;
    }

    r.documentation(documentation_stream.str());
    r.applicable_to_parent_object(applicable_to_parent_object);
    return r;
}

} }
