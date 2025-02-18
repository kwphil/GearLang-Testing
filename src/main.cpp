// "main" -*- C++ -*-

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

#include <iostream>
#include <fstream>
#include <sstream>
#include "token"
#include "parser"

int main(int argc, char *argv[]) {
    std::string filename = argv[1];
    std::string output;

    // Getting the file contents
    std::ifstream filestream(filename);
    std::stringstream buf;
    buf << filestream.rdbuf();
    output = buf.str();

    // First need to start by tokenizing the input
    Parser parser(output);
    
    return EXIT_SUCCESS;
}