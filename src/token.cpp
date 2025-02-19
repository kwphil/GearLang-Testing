// <gearlang/token.cpp> -*- C++ -*-

// This file is part of the GearLang v0.0.1 executable. This executable is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

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
    template <class T>
    using Result = std::optional<std::tuple<T, std::string_view>>;

    auto get_identifier(std::string_view input) -> std::tuple<std::string, std::string_view> {
        std::string collected_identifier = "";
        
        if(!isalpha(input[0])) {
            return { "", input };
        }

        collected_identifier.push_back(input[0]);
        
        // Since we know that input[0] is valid, we can go to input[1]
        for(auto it = input.begin()+1; it < input.end(); ++it) {
            char c = *it;

            if(!std::isalnum(c)) {
                return { collected_identifier, std::string_view(it, input.end()) };
            }

            // Store the character
            collected_identifier.push_back(c);
        }

        // The identifier was the last token... return
        return { collected_identifier, "" };
    }

    std::string_view consume_whitespace(std::string_view input) {
        for(auto it = input.begin(); it < input.end(); ++it) {
            char c = *it;

            if(!std::isblank(c)) {
                return std::string_view(it, input.end());
            }
        }

        return input;
    }
}

namespace std_gearlang::token {
    class Base {
    public:
        virtual ~Base() = default;
        virtual inline std::string type() const = 0;
        virtual std_gearlang::Result<std::shared_ptr<Base>> try_parse(std::string_view input) const = 0;
    };

    class Return : public Base {
    public:
        std_gearlang::Result<std::shared_ptr<Base>> try_parse(std::string_view input) const override {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            if(identifier == "return") {
                return std::make_tuple(std::make_shared<Return>(), new_input);
            }

            return std::nullopt;
        }

        inline std::string type() const override {
            return "return";
        }
    };

    class Exit : public Base {
    public:
        std_gearlang::Result<std::shared_ptr<Base>> try_parse(std::string_view input) const override {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            if(identifier == "exit") {
                return std::make_tuple(std::make_shared<Exit>(), new_input);
            }

            return std::nullopt;
        }

        inline std::string type() const override {
            return "exit";
        }
    };
}