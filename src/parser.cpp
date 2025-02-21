// <gearlang/parser.cpp> -*- C++ -*-
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
/// which processes input strings, removes whitespace, and converts them into
/// tokens using a set of predefined token parsers.

#pragma once

#include <functional>
#include <string>
#include <vector>
#include "result.cpp"
#include "token.cpp"

namespace std_gearlang {
    /// @brief A vector of token parsing functions.
    /// @details This vector contains functions that attempt to parse various token types
    /// from the input string, such as keywords (e.g., "Exit", "Return") and literals (e.g., numbers).
    /// These functions are applied sequentially to match the input string to a valid token type.
    static std::vector<std::function<std_gearlang::NoErr_Result<std::shared_ptr<std_gearlang::token::Base>>(std::string_view input)>> token_types = {
        std_gearlang::token::Exit::try_parse,   // Parser for the "Exit" keyword.
        std_gearlang::token::Return::try_parse, // Parser for the "Return" keyword.
        std_gearlang::token::Number::try_parse, // Parser for numbers (e.g., literals).
        std_gearlang::token::Semi::try_parse, // Semicolon
    };

    /// @class Parser
    /// @brief Parses input strings into GearLang tokens.
    /// @details The `Parser` class is responsible for interpreting an input string,
    /// identifying individual tokens using predefined parsers, and managing the
    /// current position in the input string.
    class Parser {
    private:
        std::string full_input; ///< The full input string to be parsed.
        std::string_view input; ///< A view into the current unparsed portion of the input string.

        /// @brief Attempts to parse a token from the input using a provided parser function.
        /// @param parser A function that attempts to parse a token from the current input.
        /// @return An optional shared pointer to the parsed token if successful, or nullopt if the parser fails.
        auto check_parser(auto parser) -> std::optional<std::shared_ptr<std_gearlang::token::Base>> {
            auto parse_output = parser(input);

            if (!parse_output) {
                return std::nullopt; // Parsing failed.
            }

            auto [token, new_input] = parse_output.value();

            // Update the input string view to the new unparsed portion.
            input = new_input;

            // Return the parsed token.
            return token;
        }

    public:
        /// @brief Constructs a Parser object with a given input string.
        /// @param s The input string to be parsed.
        /// @details The input string is stored, and the `input` view is initialized to point to the full input.
        Parser(std::string s) {
            full_input = std::move(s);
            input = full_input;
        }

        /// @brief Virtual destructor for the Parser class.
        virtual ~Parser() = default;

        /// @brief Peeks at the next character in the input without consuming it.
        /// @return An optional character, or nullopt if the input is empty.
        std::optional<char> peek() {
            if (input.length() < 1) {
                return std::nullopt; // No more characters to peek.
            }
            return input[0];
        }

        /// @brief Extracts the next token from the input string.
        /// @details This function first removes leading whitespace, then attempts to parse
        /// a token using the available parsers. If no valid token is found, an error is returned.
        /// @return A `Result` object containing either the parsed token or an error message.
        auto next_token() -> std_gearlang::Result<std::shared_ptr<std_gearlang::token::Base>, std::string> {
            using O = std::shared_ptr<std_gearlang::token::Base>;
            using E = std::string;

            if (!peek()) {
                return std_gearlang::Result<O, E>::err("Unexpected EOF"); // End of input.
            }

            // Remove any leading whitespace.
            input = std_gearlang::consume_whitespace(input);

            // Attempt to match a token using the available parsers.
            for (auto& parser : std_gearlang::token_types) {
                auto output = check_parser(parser);

                if (output) {
                    return std_gearlang::Result<O, E>::ok(output.value()); // Token successfully parsed.
                }
            }

            return std_gearlang::Result<O, E>::err("Unmatched Token"); // No valid token found.
        }

        /// @brief Parses the entire input string and returns a sequence of tokens.
        /// @details This function repeatedly calls `next_token` until the end of the input is reached,
        /// collecting all parsed tokens in a vector.
        /// @return A `Result` object containing either the vector of tokens or an error message.
        auto parse() -> std_gearlang::Result<std::vector<std::shared_ptr<std_gearlang::token::Base>>, std::string> {
            using O = std::vector<std::shared_ptr<std_gearlang::token::Base>>;
            using E = std::string;

            std::vector<std::shared_ptr<std_gearlang::token::Base>> tokens;

            while(peek()) {
                auto token = next_token();

                if(token.is_err()) {
                    return std_gearlang::Result<O, E>::err("Unexpected token: " + peek().value());
                }

                tokens.push_back(token.unwrap()); // Add token to the vector.
            }

            return std_gearlang::Result<O, E>::ok(tokens); // Return all parsed tokens.
        }

        /// @brief Static helper method to parse an input string into tokens.
        /// @param input The input string to be parsed.
        /// @return A `Result` object containing either the vector of tokens or an error message.
        static auto parse(std::string& input) -> std_gearlang::Result<std::vector<std::shared_ptr<std_gearlang::token::Base>>, std::string> {
            Parser p(input); // Create a parser for the given input string.
            return p.parse(); // Parse the input and return the result.
        }

        /// @brief Gets the current unparsed portion of the input string.
        /// @return A string view representing the remaining input to be parsed.
        std::string_view get_input() {
            return input;
        }
    };
}
