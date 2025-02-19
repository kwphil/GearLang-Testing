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

// File reading
#include <fstream>
// Debug
#include <iostream>
// Error enum
#include "error.cpp"
// Tokens
#include "token.cpp"

int main(int argc, char *argv[]) {
    // Making sure the file is present
    if(argc < 2) {
        std::cout << "No file has been selected" << std::endl;

        return std_gearlang::Error::cerr(std_gearlang::ErrorCode::NoFileSelected);
    }

    std::string input = "a1234 b";

    auto [ identifier, left ] = std_gearlang::get_identifier(input);

    std::cout << identifier << std::endl << left << std::endl;
    std::cout << std_gearlang::consume_whitespace(left);

    // Success
    return std_gearlang::Error::cerr(std_gearlang::ErrorCode::Ok);
}

