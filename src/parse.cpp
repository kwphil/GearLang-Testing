// <gearlang/src/parse.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so.

#include <cstdlib>
#include <gearlang/token>

namespace gearlang::parser {
    PARSER identifier(char* input) {
        for(int i = 0; input[i] != '\0'; ++i) {
            if(std::isalpha(input[i]))
        } 
    }
}