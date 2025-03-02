// <gearlang/tree/builder.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#pragma once

#include <memory>
#include <span>
#include "../token/types.cpp"
#include "builder.cpp"
#include "exit.cpp"

namespace std_gearlang::tree {
    class Statement : public Node {
    private:
        template <typename... Types>
        bool iterate_parsers(auto token_list) {
            (([&] {
                auto output = object_factory<Types>(Node::get_parent());

                if (output) {
                    *this = dynamic_cast<Statement*>(*output);
                    return true;
                }
            }()), ...);

            return false;
        }

    public:
        Statement(std::weak_ptr<Node> par)
        : Node(par) { }

        bool try_parse(std::span<std::shared_ptr<token::Base>> token_list) override {
            for(auto& token : token_list ) {
                if(*token == token::TokenType::Semicolon) {
                    auto subspan = token_list.subspan(0, token_list.size()-2);

                    return iterate_parsers<Exit>(token_list);
                }
            }

            return false;
        }
    };
}