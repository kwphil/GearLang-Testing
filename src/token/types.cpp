// <gearlang/token/types.cpp> -*- C++ -*-
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

#include <string>
#include "../token.cpp"

namespace std_gearlang::token {
    /**
     * An enum to match the tokens easily
     */
    enum class TokenType {
        Unknown,
        Return,
        Exit,
        Number,
        Semicolon
    };

    /**
     * Base class for all token types.
     * This class defines a common interface for all token types, including the type
     * of the token and the parsing function to match the token from a string input.
     */
    class Base {
    public:
        virtual ~Base() = default;

        /**
         * Returns a TokenType enum representing the token types.
         *
         * @return A string describing the token type.
         */
        static inline TokenType type();

        /**
         * Returns a value
         *
         * If no value is needed, e.g. a keyword, just return type() as human readable
         */
        virtual inline std::string get_value() const = 0;

        /**
         * Attempts to parse a token from the given input string.
         *
         * @param input The input string to parse.
         * @return A NoErr_Result containing the parsed token or nullopt if no token is matched.
         */
        static auto -> try_parse(std::string_view input) -> std_gearlang::NoErr_Result<std::shared_ptr<Base>>;

        bool operator==(Base const& other) {
            return type() == other.type();
        }

        bool operator==(TokenType const& other) {
            return type() == other;
        }
    };
}