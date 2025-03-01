// <gearlang/tree/builder.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#include <cstdlib>
#include <span>
#include "../token/types.cpp"
#include "statement.cpp"

namespace std_gearlang::tree {
    class Exit : public Statement {
    private:
        int code;

    public:
        Exit(std::weak_ptr<Node> par)
        : Statement(par) { }

        bool try_parse(std::span<std::shared_ptr<token::Base>> token_list) override {
            auto& keyword = *token_list[0];
            auto& num     = *token_list[1];

            if(
                keyword == token::TokenType::Exit &&
                num == token::TokenType::Number
            ) {
                code = std::stoi(num.get_value());

                return true;
            }

            return false;
        }
    };
}