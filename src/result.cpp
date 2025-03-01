// <gearlang/main.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

#pragma once

#include <bit>
#include <optional>
#include <source_location>
#include "error.cpp"

namespace std_gearlang {
    /**
     * A generic result type for parsing operations, which returns an optional
     * tuple containing the parsed result and the remaining input.
     *
     * @tparam T The type of the parsed object.
     */
    template <class T>
    using NoErr_Result = std::optional<std::tuple<T, std::string_view>>;

    template <class T, class E>
    class Result {
    private:
        std::optional<T> ok_val;
        std::optional<E> err_val;
        bool has_err;

        Result(std::optional<T> val, std::optional<E> err, bool active_err) {
            ok_val = val;
            err_val = err;
            has_err = active_err;
        }
    public:
        static inline Result<T, E> ok(T val) {
            return Result(val, std::nullopt, false);
        }

        static inline Result<T, E> err(E val) {
            return Result(std::nullopt, val, true);
        }

        inline E err() {
            return err_val.value();
        }

        inline constexpr bool is_ok() {
            return !is_err();
        }

        inline constexpr bool is_err() {
            return has_err;
        }

        inline constexpr T unwrap(std::source_location loc = std::source_location::current()) {
            if(is_err()) {
                throw std_gearlang::except::UnwrapResultError("Tried to call unwrap on a std_gearlang::Result", loc);
            }

            return ok_val.value();
        }
    };
}