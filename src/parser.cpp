// <gearlang/token.cpp> -*- C++ -*-
//
// This file is part of the GearLang v0.0.1 executable. This executable is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.
//
// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// If not, see <http://www.gnu.org/licenses/>.

/// @file parser.cpp
/// @brief Implements the parser for GearLang.
/// @details This file contains the implementation of the GearLang parser,
/// which processes input strings and converts them into tokens for further
/// interpretation.

#include <functional>
#include <string>
#include <vector>
#include "token.cpp"

namespace std_gearlang {
    /// @brief A vector of token parsing functions.
    /// @details This vector stores functions that attempt to parse different types
    /// of tokens from the input string.
    std::vector<std::function<std_gearlang::NoErr_Result<std::shared_ptr<std_gearlang::token::Base>>(std::string_view input)>> token_types = {
        std_gearlang::token::Exit::try_parse,
        std_gearlang::token::Return::try_parse,
    };

    /// @class Parser
    /// @brief Parses input strings into GearLang tokens.
    class Parser {
    private:
        std::string full_input; ///< Stores the full input string.
        std::string_view input; ///< Stores the current unparsed portion of the input.

        /// @brief Checks if a given parser function can extract a token.
        /// @param parser A function that attempts to parse a token.
        /// @return An optional shared pointer to the parsed token if successful, otherwise nullopt.
        auto check_parser(auto parser) -> std::optional<std::shared_ptr<std_gearlang::token::Base>> {
            auto parse_output = parser(input);

            if (!parse_output) {
                return std::nullopt;
            }

            auto [token, new_input] = parse_output.value();

            // Set the new input
            input = new_input;

            // Return the token
            return token;
        }

    public:
        /// @brief Constructs a Parser with a given input string.
        /// @param s The input string to be parsed.
        Parser(std::string s) {
            full_input = s;
            input = full_input;
        }

        /// @brief Virtual destructor for the Parser class.
        virtual ~Parser() = default;

        /// @brief Peeks at the next character in the input without consuming it.
        /// @return An optional character, or nullopt if the input is empty.
        std::optional<char> peek() {
            if (input.length() < 1) {
                return std::nullopt;
            }
            return input[0];
        }

        /// @brief Extracts the next token from the input.
        /// @details This function first removes leading whitespace, then attempts to parse
        /// a token using the available token parsers.
        /// @return An optional shared pointer to the next token, or nullopt if no token is found.
        std::optional<std::shared_ptr<std_gearlang::token::Base>> next_token() {
            if (!peek()) {
                return std::nullopt;
            }

            // First clear whitespace
            input = std_gearlang::consume_whitespace(input);

            // Attempt to match a token
            for (auto& parser : std_gearlang::token_types) {
                auto output = check_parser(parser);

                if (output) {
                    return output;
                }
            }

            return std::nullopt;
        }

        std::string_view get_input() {
            return input;
        }
    };
}