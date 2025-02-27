// <gearlang/tree/builder.cpp> -*- C++ -*-
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

#include <memory>
#include <vector>
#include "../token/types.cpp"

namespace std_gearlang::tree {
    class Node {
    protected:
        Node value;
        std::weak_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;

    public:
        inline Node& get_value() { return value };
        inline std::weak_ptr<Node>& get_parent() { return parent };
        inline std::vector<std::shared_ptr<Node>>& get_children() { return children };

        virtual bool try_parse(span<std::shared_ptr<token::Base>>) const = 0;
    };

    class Parser {
    private:
        std::vector<std::shared_ptr<token::Base>>& token_list;
        std::vector<std::shared_ptr<token::Base>>::iterator iterator;

    public:
        Parser(std::vector<std::shared_ptr<token::Base>>& tokens)
        : token_list(tokens), iterator(token_list.begin()) { }

        std::vector<std::shared_ptr<void>> parse() {
            while(iterator++ < token_list.end()) {

            }
        }

        static inline std::vector<std::shared_ptr<void>> parse(std::vector<std::shared_ptr<token::Base>>& tokens) {
            Parser parser(tokens);
            return parser.parse();
        }
    };
}