/* <gearlang/include/string.h> -*- C -*-
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 */

#ifndef STRING_H
#define STRING_H

#include <string.h>

#define st_ char*

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    st_ ptr;
    size_t extent;
} basic_string;

#ifdef __cplusplus
}

#include <vector>
#include <gearlang/lexer>

namespace gearlang {
    class String {
    private:
        basic_string input;

    public:
        String(char* input)
        : input({.ptr=input,.extent=strlen(input)}) { }

        template<class T, class Func>
        std::vector<T> map(Func f) {
            std::vector<T> out;

            for(int i = 0; input[i] != '\0'; ++i) {
                out.push(f());
            }


        }
    };
}

#endif
#endif