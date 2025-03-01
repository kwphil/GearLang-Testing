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

#pragma once

#include <functional>
#include <memory>
#include <vector>
#include "../token/types.cpp"

namespace std_gearlang::tree {
    class Node {
    protected:
        std::weak_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;

        Node() { }

        Node(std::weak_ptr<Node> par)
        : parent(par) { }

        Node(
            std::weak_ptr<Node> par,
            std::vector<std::shared_ptr<Node>> child
        ) : parent(par), children(child) { }

        virtual auto iterate_parsers(
            std::span<std::shared_ptr<token::Base>>& list,
            std::vector<std::function<Node*(std::weak_ptr<Node>)>>& types,
            std::weak_ptr<Node>& parent
        ) -> std::optional<std::shared_ptr<Node>> const {
            for(auto& type : types) {
                Node& object = *type(parent);

                auto result = object.try_parse(list);

                if(result) {
                    return std::make_shared<Node>(object);
                }
            }
        }

    public:
        virtual ~Node() = default;

        virtual inline std::weak_ptr<Node>& get_parent() { return parent; }
        virtual inline std::vector<std::shared_ptr<Node>>& get_children() { return children; }

        virtual bool try_parse(std::span<std::shared_ptr<token::Base>>) = 0;

        virtual Node& operator=(Node& other) {
            parent = other.get_parent();
            children = other.get_children();

            return *this;
        }
    };

    class Parser {
    private:
        const std::vector<std::shared_ptr<token::Base>>& token_list;
        std::vector<std::shared_ptr<token::Base>>::iterator iterator;
        std::vector<std::function<std::optional<Node>(std::span<std::shared_ptr<token::Base>>)>> parsers;

    public:
        Parser(std::vector<std::shared_ptr<token::Base>>& tokens)
        : token_list(tokens), iterator(tokens.begin()) { }

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