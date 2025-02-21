// <gearlang/error.cpp> -*- C++ -*-
//
// This file is part of the GearLang v0.0.1 executable. This executable is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.
//
// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <bit>
#include <exception>
#include <sstream>

namespace std_gearlang {

    /**
     * @brief Enum representing different error codes in the GearLang interpreter.
     *
     * This enum is used to define specific error codes for various types of
     * errors encountered during the execution of GearLang code.
     */
    enum class ErrorCode {
        Ok,                ///< No error, operation was successful
        NoFileSelected,    ///< No file was selected for processing
        NonMatchedToken,   ///< A token could not be matched during parsing
    };

    /**
     * @brief A class for managing and representing errors using error codes.
     *
     * The `Error` class is used to encapsulate error codes (either provided as
     * an enum or an integer) and offers methods for retrieving and converting
     * error codes to different formats (such as integer format for output).
     */
    class Error {
    private:
        ErrorCode err; ///< The error code stored in the Error object

    public:
        /**
         * @brief Constructs an Error object from an ErrorCode enum.
         *
         * This constructor initializes the `Error` object with a specific error
         * code from the `ErrorCode` enum.
         *
         * @param e The error code (of type `ErrorCode`) to initialize the object with.
         */
        inline Error(ErrorCode e) {
            err = e;
        }

        /**
         * @brief Constructs an Error object from an integer value.
         *
         * This constructor initializes the `Error` object with an integer
         * value and casts it to the corresponding `ErrorCode` enum value.
         *
         * @param e The error code as an integer, which will be cast to an `ErrorCode` enum.
         */
        inline Error(int e) {
            err = std::bit_cast<ErrorCode>(e);
        }

        /**
         * @brief Retrieves the error code as an `ErrorCode` enum.
         *
         * This method returns the current error code stored in the `Error` object
         * in its enum format.
         *
         * @return The error code as an `ErrorCode` enum value.
         */
        inline ErrorCode get_error() {
            return err;
        }

        /**
         * @brief Retrieves the error code as an integer.
         *
         * This method converts the error code to its integer representation,
         * useful for displaying or logging the error in a numeric format.
         *
         * @return The error code as an integer.
         */
        inline int cerr() {
            return std::bit_cast<int>(err);
        }

        /**
         * @brief Retrieves the error code as an integer from a given `ErrorCode`.
         *
         * This static method takes an `ErrorCode` enum value and converts it to
         * its integer representation.
         *
         * @param e The error code in the form of `ErrorCode` enum.
         * @return The error code as an integer.
         */
        static inline int cerr(ErrorCode e) {
            return std::bit_cast<int>(e);
        }
    };
}

namespace std_gearlang::except {
    class UnwrapResultError : public std::exception {
    private:
        std::size_t loc;
        char* file;

    public:
        UnwrapResultError(std::size_t l, char* f) {
            loc = l;
            file = f;
        }

        std::exception& operator= (const std::exception& e) noexcept {
            throw e;
        }

        const char *what() const noexcept override {
            std::stringstream message;
            std::string buf;

            message << "Tried to call unwrap on a std_gearlang::Result, in file "
                << file << ", on line: " << loc;

            buf = message.str();

            return static_cast<const char *>(buf.c_str());
        }

        inline std::size_t get_loc() {
            return loc;
        }
    };
}
