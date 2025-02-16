// This file is part of the GearLang v0.0.1 executable. This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation; either version 3, or (at your option) any later version.

// This executable is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details. 

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include <optional>
#include <tuple>
#include <gearlang/token>

class Number : public Token::Base {
private:
    int value;

public: 
    Number(int value) {
        (*this).value = value;
    }

    // If can't parse, it will throw a null
    static Token::Result<Number> try_parse(std::string& input) {
        std::string ret = "";
        std::string::iterator it;
        
        for(it = input.begin(); it < input.end(); ++it) {
            char c = *it;

            if(!std::isdigit(c)) {
                break;
            }

            ret.push_back(c);
        }

        /* If no chars were parsed return null */
        if(ret == "") {
            return std::nullopt;
        }

        auto ret_wrap = std::make_tuple(Number(std::stoi(ret)), std::string(it, input.end()));
        return std::make_optional(ret_wrap);
    }

    int get_value() {
        return value;
    }

    std::string get_type() {
        return "Number";    
    }
};