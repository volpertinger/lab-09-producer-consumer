// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#include <boost/program_options.hpp>
#include <cstddef>
#include <iostream>
#include <string>
#include <web_crawler_lib.h>

namespace web_crawler_app {
namespace program_options = ::boost::program_options;

constexpr char const* HELP_OPTION_NAME = "help";
constexpr char const* URL_OPTION_NAME = "url";
constexpr char const* DEPTH_OPTION_NAME = "depth";
constexpr char const* NETWORK_THREADS_OPTION_NAME = "network_threads";
constexpr char const* PARSER_THREADS_OPTION_NAME = "parser_threads";
constexpr char const* OUTPUT_OPTION_NAME = "output";

//<editor-fold desc="Initializer of PROGRAM_OPTIONS_DESCRIPTION" defaultstate ="collapsed">
static program_options::options_description create_program_options_description_() noexcept {
  program_options::options_description description{"Options"};

  using program_options::value;
  //@formatter:off (just weird Boost syntax)
  description.add_options()
      (HELP_OPTION_NAME, "Shows this help message")
      (URL_OPTION_NAME, value<::std::string>(), "HTML page address")
      (DEPTH_OPTION_NAME, value<::std::size_t>()->default_value(0), "Page search depth")
      (NETWORK_THREADS_OPTION_NAME, value<::std::size_t>()->default_value(0), "Number of downloader-threads")
      (PARSER_THREADS_OPTION_NAME, value<::std::size_t>()->default_value(0), "Number of parser-threads")
      (OUTPUT_OPTION_NAME, value<::std::string>(), "Path to output file")
      ;
  //</editor-fold>

  return description;
}

auto const PROGRAM_OPTIONS_DESCRIPTION = create_program_options_description_();

[[nodiscard]] program_options::variables_map parse_program_options(int arguments_count,
                                                                   const char* const arguments[]);
} // namespace web_crawler_app

int main(int const arguments_count, char const* const arguments[]) {
  auto const program_options = web_crawler_app::parse_program_options(arguments_count, arguments);

  if (program_options.count("help")) {
    ::std::cout << web_crawler_app::PROGRAM_OPTIONS_DESCRIPTION << ::std::endl;

    return 0;
  }

  ::std::string url;
  if (!program_options.count(web_crawler_app::URL_OPTION_NAME)) {
    ::std::cerr << "Missing option " << web_crawler_app::URL_OPTION_NAME << ::std::endl;
    return 1;
  }
  url = program_options[web_crawler_app::URL_OPTION_NAME].as<::std::string>();

  auto const depth = program_options[web_crawler_app::DEPTH_OPTION_NAME].as<::std::size_t>();
  auto const network_threads = program_options[web_crawler_app::NETWORK_THREADS_OPTION_NAME].as<::std::size_t>();
  auto const parser_threads = program_options[web_crawler_app::PARSER_THREADS_OPTION_NAME].as<::std::size_t>();

  ::std::string output;
  if (!program_options.count(web_crawler_app::OUTPUT_OPTION_NAME)) {
    ::std::cerr << "Missing option " << web_crawler_app::OUTPUT_OPTION_NAME << ::std::endl;
    return 1;
  }
  output = program_options[web_crawler_app::OUTPUT_OPTION_NAME].as<::std::string>();

  web_crawler_lib::WebCrawler::from(url, depth, network_threads, parser_threads, output).join();
}

namespace web_crawler_app {

program_options::variables_map parse_program_options(int const arguments_count, const char* const arguments[]) {
  program_options::variables_map variables;
  program_options::store(
      program_options::parse_command_line(arguments_count, arguments, PROGRAM_OPTIONS_DESCRIPTION),
      variables
  );
  variables.notify();

  return variables;
}
} // namespace web_crawler_app
