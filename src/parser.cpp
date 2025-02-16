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

#include <string>
#include <vector>
#include <gearlang/token>

class Parser {
private:
    std::string input = "";
    int pos;
    std::vector<Token::Base> tokens;

public:
    Parser(std::string& input) {
        (*this).input = input;
        pos = 0;
        tokens = {};
    }    

    char peek() {
        return input[pos];
    }

    void advance() {
        ++pos;
    }

    Token::Base next_token() {
        
    }
};