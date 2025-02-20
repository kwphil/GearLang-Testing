// <gearlang/parser.cpp> -*- C++ -*-

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

#include <functional>
#include <string>
#include <vector>
#include "token.cpp"

namespace std_gearlang {
    std::vector<std::function<std_gearlang::Result<std::shared_ptr<std_gearlang::token::Base>>(std::string_view input)>> token_types = {
        std_gearlang::token::Exit::try_parse,
        std_gearlang::token::Return::try_parse,
    };

    class Parser {
    private:
        std::string full_input;
        std::string_view input;

        auto check_parser(auto parser) -> std::optional<std::shared_ptr<std_gearlang::token::Base>> {
            auto parse_output = parser(input);

            if(!parse_output) {
                return std::nullopt;
            }

            // Get the variables from the tuple
            auto [ token, new_input ] = parse_output;

            // Set the new input
            input = new_input;

            // Return the token
            return token;
        }

    public:
        Parser(std::string s) {
            full_input = s;
            input = full_input;
        }

        virtual ~Parser() = default; 

        std::optional<char> peek() {
            if(input.length() < 1) {
                return std::nullopt;
            }

            return input[0];
        }

        std::optional<std::shared_ptr<std_gearlang::token::Base>> next_token() {
            if(!peek()) {
                return std::nullopt;
            }

            // First clear whitespace
            std_gearlang::consume_whitespace(input);

            // And then start matching
            for(auto& parser : std_gearlang::token_types) {
                auto output = check_parser(parser);
                
                if(output) {
                    return output;
                }
            }

            return std::nullopt;
        }
    };
}