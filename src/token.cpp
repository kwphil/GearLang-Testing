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

#include <exception>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include "helper.cpp"
#include "result.cpp"
#include "token/types.cpp"
#include "token/keyword.cpp"

namespace std_gearlang::token {
    class Number : public Base {
    private:
        std::string value;

    public:
        Number(std::string val) {
            value = val;
        }

        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            std::string val = "";

            for(auto it = input.begin(); it < input.end(); ++it) {
                if(std::isdigit(*it)) {
                    val.push_back(*it);

                    continue;
                }

                if(val == "") {
                    return std::nullopt;
                }

                return std::make_tuple(std::make_shared<Number>(val), std::string_view(it, std::distance(it, input.end())));
            }

            if(val == "") {
                return std::nullopt;
            }

            return std::make_tuple(std::make_shared<Number>(val), "");
        }

        static inline TokenType type() {
            return TokenType::Number;
        }

        inline std::string get_value() const override {
            return value;
        }
    };

    class Semi : public Base {
    public:
        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            if (!(input[0] == ';')) {
                return std::nullopt;
            }

            return std::make_tuple(std::make_shared<Semi>(), std::string_view(input.begin()+1, input.length()-1));
        }

        static inline TokenType type() {
            return TokenType::Semicolon;
        }

        inline std::string get_value() const override {
            return "Semicolon";
        }
    };
}
