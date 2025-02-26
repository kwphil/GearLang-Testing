// <gearlang/compiler.cpp> -*- C++ -*-

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

#include <cstdlib>
#include <functional>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <vector>
#include "token.cpp"
#include "tree.cpp"

namespace std_gearlang::ir {
    extern void create_start();
}

namespace std_gearlang::tree {
    class Statement {
    public:
        static std::optional<Statement> try_parse(
            std::vector<std::shared_ptr<std_gearlang::token::Base>>::iterator iterator
        ) {
            // const auto beginning = iterator;

            // while(true) {
            //     if(*it == token::Semi) {
            //         // loop through the parsers
            //     }
            // }
        }
    };

    class Exit : public Statement {
    private:
        int code;

    public:
        Exit(int c) {
            code = c;
        }

        static std::optional<Statement> try_parse(
            std::ranges::range<std_gearlang::token::Base> section
        ) {
            if(iterator->get()->type() != "exit") {
                return std::nullopt;
            }

            return Exit(std::stoi((iterator+1)->get()->get_value().c_str()));
        }

        int get_code() {
            return code;
        }
    };

    static ParserList<> parsers {
        Exit::try_parse
    };
}

namespace std_gearlang {
    class Compiler {
    private:
        std::string output;
        std::vector<std::shared_ptr<std_gearlang::token::Base>>& tokens;

    public:
        Compiler(std::vector<std::shared_ptr<std_gearlang::token::Base>>& t) {
            output = "";
            tokens = t;
        }

        static void test(auto& t) {
            auto output = std_gearlang::tree::Exit::try_parse(t.begin());

            if(!output) {
                throw;
            }
        }
    };
}
