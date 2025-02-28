// <gearlang/token/keyword.cpp> -*- C++ -*-
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

#include "../token.cpp"

namespace std_gearlang::token {
    /**
     * Represents a "return" token in GearLang.
     * This class attempts to parse the "return" keyword from the input string.
     */
    class Return : public Base {
    public:
        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            // Check if the identifier matches "return"
            if(identifier == "return") {
                return std::make_tuple(std::make_shared<Return>(), new_input);
            }

            // If the identifier does not match, return std::nullopt
            return std::nullopt;
        }

        inline TokenType type() const override {
            return TokenType::Return;
        }

        inline std::string get_value() const override {
            return "return";
        }
    };

    /**
     * Represents an "exit" token in GearLang.
     * This class attempts to parse the "exit" keyword from the input string.
     */
    class Exit : public Base {
    public:
        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            // Check if the identifier matches "exit"
            if(identifier == "exit") {
                return std::make_tuple(std::make_shared<Exit>(), new_input);
            }

            // If the identifier does not match, return std::nullopt
            return std::nullopt;
        }

        inline TokenType type() const override {
            return TokenType::Exit;
        }

        inline std::string get_value() const override {
            return "exit";
        }
    };
}