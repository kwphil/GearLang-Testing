// <gearlang/main.cpp> -*- C++ -*-

// This file is part of the GearLang v0.0.1 executable. This executable is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <optional>
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

        inline constexpr T unwrap() {
            if(is_err()) {
                throw std_gearlang::except::UnwrapResultError(__LINE__, __FILE__);
            }

            return ok_val.value();
        }
    };
}