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
#include <span>
#include "../token/types.cpp"
#include "builder.cpp"

namespace std_gearlang::tree {
    class Statement : public Node {
    public:
        bool try_parse(std::span<std::shared_ptr<token::Base>> token_list) {
            for(auto& token : token_list ) {
                if(token == token::TokenType::Semicolon) {

                }
            }
        }
    };
}