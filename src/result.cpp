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
    template <class T, class E>
    class Result {
    private:
        std::optional<T> ok_val;
        std::optional<E> err_val;

        Result(std::optional<T> val, std::optional<E> err) {
            ok_val = val;
            err_val = err;
        }
    public:
        static inline Result<T, E> ok(T val) {
            return Result(val, std::nullopt);
        }

        static inline Result<T, E> err(E val) {
            return Result(std::nullopt, val);
        }

        inline constexpr bool is_ok() {
            return !is_err();
        }

        inline constexpr bool is_err() {
            return err_val.has_value();
        }

        inline constexpr T unwrap() {
            if(is_err()) {
                throw std_gearlang::except::UnwrapResultError(__LINE__, __FILE__);
            }

            return ok_val.value();
        }
    };
}