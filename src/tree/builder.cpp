// <gearlang/tree/builder.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#pragma once

#include <functional>
#include <memory>
#include <vector>
#include "../token/types.cpp"

namespace std_gearlang::tree {
    template<class T, class... Params>
    constexpr inline std::unique_ptr<T> object_factory(Params&&... params) {
        return std::make_unique<T>(std::forward<Params>(params)...);
    }

    class Node {
    protected:
        std::weak_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;

        Node() { }

        Node(std::weak_ptr<Node> par)
        : parent(par) { }

        Node(
            std::weak_ptr<Node> par,
            std::vector<std::shared_ptr<Node>> child
        ) : parent(par), children(child) { }

        // Removing iterate_parsers because it seems to only be making more problems

    public:
        virtual ~Node() = default;

        virtual inline std::weak_ptr<Node>& get_parent() { return parent; }
        virtual inline std::vector<std::shared_ptr<Node>>& get_children() { return children; }

        virtual bool try_parse(std::span<std::shared_ptr<token::Base>>) = 0;

        Node& operator=(Node& other) {
            parent = other.get_parent();
            children = other.get_children();

            return *this;
        }
    };

    class Parser {
    private:
        const std::vector<std::shared_ptr<token::Base>>& token_list;
        std::vector<std::shared_ptr<token::Base>>::iterator iterator;
        std::vector<std::function<std::optional<Node>(std::span<std::shared_ptr<token::Base>>)>> parsers;

    public:
        Parser(std::vector<std::shared_ptr<token::Base>>& tokens)
        : token_list(tokens), iterator(tokens.begin()) { }

        std::vector<std::shared_ptr<void>> parse() {
            while(iterator++ < token_list.end()) {

            }

            return {};
        }

        static inline std::vector<std::shared_ptr<void>> parse(std::vector<std::shared_ptr<token::Base>>& tokens) {
            Parser parser(tokens);
            return parser.parse();
        }
    };
}