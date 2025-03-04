/* <gearlang/src/token.c> -*- C -*-
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 */

#include <stddef.h>
#include <gearlang/string.h>

/* The bit conversions would quickly become unreadable
 * So I made these real quick for it
 */
char peek_(st_ input) { *input; }
char prev_(st_ input) { *(char*)((size_t)input-1); }
char next_(st_ input) { *(char*)((size_t)input+1); }
char move_(st_ input, ssize_t count) { *(char*)((size_t)input+=count); }
