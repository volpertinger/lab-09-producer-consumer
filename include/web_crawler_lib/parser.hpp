// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#pragma once

#include <iostream>
#include <set>
#include <string>
#include <web_crawler_lib/parser.hpp>
#include <web_crawler_lib/url_reader.hpp>

namespace web_crawler_lib {

    /**
     * @brief Result of parsing url-reader's response.
     */
    struct ParsingResult {
        /// URLs to the images
        ::std::set<::std::string> image_urls;
        /// URLs to children
        ::std::set<::std::string> child_urls;

        [[nodiscard]] bool operator ==(ParsingResult const& other) const;
    };

    ::std::ostream &operator<<(::std::ostream &out, ParsingResult const& result);

    /**
     * @brief Parses the given response.
     *
     * @param response response which should be parsed
     * @return result of parsing
     */
    [[nodiscard]] ParsingResult parse_http_response(http_response_t const& response, bool parse_children);
} // namespace web_crawler_lib
