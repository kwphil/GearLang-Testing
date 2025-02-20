// <gearlang/main.cpp> -*- C++ -*-

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

#include <fstream>
#include <iostream>
#include "error.cpp"
#include "token.cpp"
#include "parser.cpp"

int main(int argc, char *argv[]) {
    // Making sure the file is present
    if(argc < 2) {
        std::cout << "No file has been selected" << std::endl;

        return std_gearlang::Error::cerr(std_gearlang::ErrorCode::NoFileSelected);
    }

    std::string input = "exit 0;";
    std_gearlang::Parser parser(input);

    auto output = parser.next_token();

    if(!output) {
        std::cout << "None";
        return -1;
    }

    std::cout << (*output.value()).type() << std::endl;

    output = parser.next_token();

    if(!output) {
        std::cout << parser.get_input();
        return -1;
    }

    std::cout << (*output.value()).type() << std::endl;

    // Success
    return std_gearlang::Error::cerr(std_gearlang::ErrorCode::Ok);
}
