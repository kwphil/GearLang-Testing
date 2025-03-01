// <gearlang/token/types.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#pragma once

#include <string>
#include "../token.cpp"

namespace std_gearlang::token {
    /**
     * An enum to match the tokens easily
     */
    enum class TokenType {
        Unknown,
        Return,
        Exit,
        Number,
        Semicolon
    };

    /**
     * Base class for all token types.
     * This class defines a common interface for all token types, including the type
     * of the token and the parsing function to match the token from a string input.
     */
    class Base {
    public:
        virtual ~Base() = default;

        /**
         * Returns a TokenType enum representing the token types.
         *
         * @return A string describing the token type.
         */
        virtual inline TokenType type() const = 0;

        /**
         * Returns a value
         *
         * If no value is needed, e.g. a keyword, just return type() as human readable
         */
        virtual inline std::string get_value() const = 0;

        /**
         * Attempts to parse a token from the given input string.
         *
         * @param input The input string to parse.
         * @return A NoErr_Result containing the parsed token or nullopt if no token is matched.
         */
        static auto try_parse(std::string_view input) -> std_gearlang::NoErr_Result<std::shared_ptr<Base>>;

        bool operator==(Base const& other) {
            return type() == other.type();
        }

        bool operator==(TokenType const& other) {
            return type() == other;
        }
    };
}