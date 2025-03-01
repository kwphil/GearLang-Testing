// <gearlang/main.cpp> -*- C++ -*-

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#include <fstream>
#include <iostream>
#include "compiler.cpp"
#include "error.cpp"
#include "token.cpp"
#include "parser.cpp"
#include "result.cpp"
#include "tree/builder.cpp"
#include "tree/statement.cpp"

int main(int argc, char *argv[]) {
    // GCC Runtime exception
    std::cout << "This GCC Runtime Library Exception (\"Exception\") is an additional permission under section 7 of the GNU General Public License, version 3 (\"GPLv3\"). It applies to a given file (the \"Runtime Library\") that bears a notice placed by the copyright holder of the file stating that the file is governed by GPLv3 along with this Exception.";

    // Making sure the file is present
    if(argc < 2) {
        std::cout << "No file has been selected" << std::endl;

        return std_gearlang::Error::cerr(std_gearlang::ErrorCode::NoFileSelected);
    }

    std::string input = "exit 0;";
    std_gearlang::Parser parser(input);

    std::cout << parser.parse().is_ok();
    auto output = parser.parse().unwrap();
    std::cout << output.size() << std::endl;
    for(auto it = output.begin(); it < output.end(); ++it) {
        std::cout << it->get()->get_value() << std::endl;
    }

    // std_gearlang::ir::create_start();

    // Success
    return std_gearlang::Error::cerr(std_gearlang::ErrorCode::Ok);
}
