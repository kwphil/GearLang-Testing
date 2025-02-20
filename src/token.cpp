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

#pragma once

#include <format>
#include <memory>
#include <optional>
#include <string>
#include <tuple>

namespace std_gearlang {
    /**
     * A generic result type for parsing operations, which returns an optional
     * tuple containing the parsed result and the remaining input.
     *
     * @tparam T The type of the parsed object.
     */
    template <class T>
    using Result = std::optional<std::tuple<T, std::string_view>>;

    /**
     * Attempts to parse an identifier from the provided input string.
     * The identifier must start with an alphabetical character, and can be followed by
     * alphanumeric characters. This function returns a tuple containing the identifier
     * and the remaining input.
     *
     * @param input The string to parse the identifier from.
     * @return A tuple containing the parsed identifier and the remaining input.
     */
    auto get_identifier(std::string_view input) -> std::tuple<std::string, std::string_view> {
        std::string collected_identifier = "";

        // If the first character is not an alphabet, return empty identifier
        if(!isalpha(input[0])) {
            return { "", input };
        }

        // Start collecting the identifier
        collected_identifier.push_back(input[0]);

        // Process the remaining characters of the input
        for(auto it = input.begin()+1; it < input.end(); ++it) {
            char c = *it;

            // If the character is non-alphanumeric, stop collecting
            if(!std::isalnum(c)) {
                return { collected_identifier, std::string_view(it, input.end()) };
            }

            // Store the valid character
            collected_identifier.push_back(c);
        }

        // Return the identifier and an empty string if the identifier was at the end
        return { collected_identifier, "" };
    }

    /**
     * Consumes any leading whitespace from the input string.
     * This function returns the remaining input after the whitespace has been removed.
     *
     * @param input The string to remove leading whitespace from.
     * @return A string view containing the input after the whitespace.
     */
    std::string_view consume_whitespace(std::string_view input) {
        // Traverse through the input and find the first non-blank character
        for(auto it = input.begin(); it < input.end(); ++it) {
            char c = *it;

            // If a non-blank character is found, return the remaining input
            if(!std::isblank(c)) {
                return std::string_view(it, input.end());
            }
        }

        // If no non-blank character is found, return the original input
        return input;
    }
}

namespace std_gearlang::token {

    /**
     * Base class for all token types.
     * This class defines a common interface for all token types, including the type
     * of the token and the parsing function to match the token from a string input.
     */
    class Base {
    public:
        virtual ~Base() = default;

        /**
         * Returns a string representing the type of the token.
         *
         * @return A string describing the token type.
         */
        virtual inline std::string type() const = 0;

        /**
         * Returns a value
         *
         * If no value is needed, e.g. a keyword, just return type()
         */
        virtual inline std::string get_value() const = 0;

        /**
         * Attempts to parse a token from the given input string.
         *
         * @param input The input string to parse.
         * @return A result containing the parsed token or nullopt if no token is matched.
         */
        static std_gearlang::Result<std::shared_ptr<Base>> try_parse(std::string_view input);
    };

    /**
     * Represents a "return" token in GearLang.
     * This class attempts to parse the "return" keyword from the input string.
     */
    class Return : public Base {
    public:
        /**
         * Attempts to parse the "return" keyword from the input string.
         * If the input starts with "return", it returns a parsed Return token.
         * Otherwise, it returns std::nullopt indicating no match.
         *
         * @param input The input string to parse.
         * @return A result containing a shared pointer to the parsed Return token or nullopt.
         */
        static std_gearlang::Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            // Check if the identifier matches "return"
            if(identifier == "return") {
                return std::make_tuple(std::make_shared<Return>(), new_input);
            }

            // If the identifier does not match, return std::nullopt
            return std::nullopt;
        }

        /**
         * Returns the type of this token, which is "return".
         *
         * @return The string "return".
         */
        inline std::string type() const override {
            return "return";
        }

        inline std::string get_value() const override {
            return type();
        }
    };

    /**
     * Represents an "exit" token in GearLang.
     * This class attempts to parse the "exit" keyword from the input string.
     */
    class Exit : public Base {
    public:
        /**
         * Attempts to parse the "exit" keyword from the input string.
         * If the input starts with "exit", it returns a parsed Exit token.
         * Otherwise, it returns std::nullopt indicating no match.
         *
         * @param input The input string to parse.
         * @return A result containing a shared pointer to the parsed Exit token or nullopt.
         */
        static std_gearlang::Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            // Check if the identifier matches "exit"
            if(identifier == "exit") {
                return std::make_tuple(std::make_shared<Exit>(), new_input);
            }

            // If the identifier does not match, return std::nullopt
            return std::nullopt;
        }

        /**
         * Returns the type of this token, which is "exit".
         *
         * @return The string "exit".
         */
        inline std::string type() const override {
            return "exit";
        }

        inline std::string get_value() const override {
            return type();
        }
    };

    class Number : public Base {
    private:
        std::string value;

    public:
        Number(std::string val) {
            value = val;
        }

        static std_gearlang::Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            std::string val = "";

            for(auto it = input.begin(); it < input.end(); ++it) {
                if(!std::isdigit(*it)) {
                    if(val == "") {
                        return std::nullopt;
                    }
                    
                    return std::make_tuple(std::make_shared<Number>(val), std::string_view(it, input.end()));
                }

                val.push_back(*it);
            }

            return std::nullopt;
        }

        inline std::string type() const override {
            return "number";
        }

        inline std::string get_value() const override {
            return value;
        }
    };
}
