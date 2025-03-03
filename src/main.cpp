// <gearlang/src/main.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so.

#include <iostream>
#include <gearlang/error>

int main(int argc, char *argv[]) {
    // Making sure the file is present
    if(argc < 2) {
        std::cout << "No file has been selected" << std::endl;

        return gearlang::cerr(gearlang::error::INVALID_PARAMS);
    }

    // Success
    return gearlang::cerr(gearlang::error::OK);
}