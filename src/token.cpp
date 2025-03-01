// <gearlang/token.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#pragma once

#include <exception>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include "helper.cpp"
#include "result.cpp"
#include "token/types.cpp"
#include "token/keyword.cpp"

namespace std_gearlang::token {
    class Number : public Base {
    private:
        std::string value;

    public:
        Number(std::string val)
        : value(val) { }

        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            std::string val = "";

            for(auto it = input.begin(); it < input.end(); ++it) {
                if(std::isdigit(*it)) {
                    val.push_back(*it);

                    continue;
                }

                if(val == "") {
                    return std::nullopt;
                }

                return std::make_tuple(std::make_shared<Number>(val), std::string_view(it, std::distance(it, input.end())));
            }

            if(val == "") {
                return std::nullopt;
            }

            return std::make_tuple(std::make_shared<Number>(val), "");
        }

        inline TokenType type() const override {
            return TokenType::Number;
        }

        inline std::string get_value() const override {
            return value;
        }
    };

    class Semi : public Base {
    public:
        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            if (!(input[0] == ';')) {
                return std::nullopt;
            }

            return std::make_tuple(std::make_shared<Semi>(), std::string_view(input.begin()+1, input.length()-1));
        }

        inline TokenType type() const override {
            return TokenType::Semicolon;
        }

        inline std::string get_value() const override {
            return "Semicolon";
        }
    };
}
