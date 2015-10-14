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
#include <boost/filesystem/operations.hpp>
#include "dogen/stitcher/parser_validation_error.hpp"
#include "dogen/stitcher/program_options_parser.hpp"

// Note on logging: we are NOT logging any of the exceptions to the
// log in this file. This is by design. The logger is only initialised
// after the options have been parsed; were we to log prior to this,
// we would dump all the messages into the console. The output is very
// confusing users that are accustomed to normal console applications.

namespace {

const std::string more_information(
    "Try `dogen_stitcher --help' for more information.");
const std::string at_least_one_argument("Expected at least one argument");

const std::string empty;
const std::string help_arg("help");
const std::string version_arg("version");
const std::string verbose_arg("verbose");
const std::string target_arg("target");
const std::string force_write_arg("force-write");

}

namespace dogen {
namespace stitcher {

program_options_parser::
program_options_parser(std::vector<std::string> arguments)
    : arguments_(arguments),
      current_path_(boost::filesystem::current_path()) { }

program_options_parser::
program_options_parser(const int argc, const char* argv[])
    : arguments_(argv + 1, argv + argc),
      current_path_(boost::filesystem::current_path()) { }

boost::program_options::options_description
program_options_parser::general_options_factory() const {
    boost::program_options::options_description r("General options");
    r.add_options()
        ("help,h", "Display this help and exit.")
        ("version", "Output version information and exit.");
    return r;
}

boost::program_options::options_description
program_options_parser::troubleshooting_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Troubleshooting options");
    r.add_options()
        ("verbose,v", "Output additional diagnostic information.");

    return r;
}

boost::program_options::options_description
program_options_parser::input_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Input options");
    r.add_options()
        ("target,t",
            value<std::string>(),
            "Stitch template file or directory containing stitch templates.");

    return r;
}

boost::program_options::options_description
program_options_parser::output_options_factory() const {
    using boost::program_options::value;
    boost::program_options::options_description r("Output options");
    r.add_options()
        ("force-write", "Always write to file even when there are"
            " no differences");

    return r;
}

boost::program_options::options_description
program_options_parser::options_factory() const {
    boost::program_options::options_description r;
    r.add(general_options_factory());
    r.add(troubleshooting_options_factory());
    r.add(input_options_factory());
    r.add(output_options_factory());
    return r;
}

boost::optional<boost::program_options::variables_map>
program_options_parser::variables_map_factory() const {
    const auto options(options_factory());

    using namespace boost::program_options;
    variables_map r;
    try {
        basic_command_line_parser<char> parser(arguments_);
        store(parser.options(options).run(), r);
        notify(r);
    } catch (const boost::program_options::error& e) {
        BOOST_THROW_EXCEPTION(parser_validation_error(e.what()));
    }

    if (r.count(help_arg)) {
        if (help_function_) {
            std::ostringstream stream;
            stream << options;
            help_function_(stream.str());
        }
        return boost::optional<boost::program_options::variables_map>();
    }

    if (r.count(version_arg)) {
        if (version_function_)
            version_function_();
        return boost::optional<boost::program_options::variables_map>();
    }
    return boost::optional<boost::program_options::variables_map>(r);
}

void program_options_parser::
help_function(std::function<void(std::string)> value) {
    help_function_ = value;
}

void program_options_parser::throw_missing_target() const {
    std::ostringstream stream;
    stream << "Mandatory parameter target is missing. " << more_information;
    BOOST_THROW_EXCEPTION(parser_validation_error(stream.str()));
}

void program_options_parser::version_function(std::function<void()> value) {
    version_function_ = value;
}

config::stitching_options program_options_parser::
transform_options(const variables_map& vm) const {
    config::stitching_options r;

    r.verbose(vm.count(verbose_arg));
    if (!vm.count(target_arg))
        throw_missing_target();

    r.target(vm[target_arg].as<std::string>());
    r.force_write(vm.count(force_write_arg));
    return r;
}

boost::optional<config::stitching_options> program_options_parser::parse() {
    auto optional_vm(variables_map_factory());

    if (!optional_vm)
        return boost::optional<config::stitching_options>();

    const boost::program_options::variables_map vm(*optional_vm);
    const auto r(transform_options(vm));
    return boost::optional<config::stitching_options>(r);
}

} }
