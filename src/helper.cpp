// <gearlang/helper.cpp> -*- C++ -*-

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

#include <string>

namespace std_gearlang {
    /**
     * Attempts to parse an identifier from the provided input string.
     * The identifier must start with an alphabetical character, and can be followed by
     * alphanumeric characters. This function returns a tuple containing the identifier
     * and the remaining input.
     *
     * @param input The string to parse the identifier from.
     * @return A tuple containing the parsed identifier and the remaining input.
     */
    auto get_identifier(std::string_view input) -> std::tuple<std::string, std::string_view> {
        std::string collected_identifier = "";

        // If the first character is not an alphabet, return empty identifier
        if(!isalpha(input[0])) {
            return { "", input };
        }

        // Start collecting the identifier
        collected_identifier.push_back(input[0]);

        // Process the remaining characters of the input
        for(auto it = input.begin()+1; it < input.end(); ++it) {
            char c = *it;

            // If the character is non-alphanumeric, stop collecting
            if(!std::isalnum(c)) {
                return { collected_identifier, std::string_view(it, input.end()) };
            }

            // Store the valid character
            collected_identifier.push_back(c);
        }

        // Return the identifier and an empty string if the identifier was at the end
        return { collected_identifier, "" };
    }

    /**
     * Consumes any leading whitespace from the input string.
     * This function returns the remaining input after the whitespace has been removed.
     *
     * @param input The string to remove leading whitespace from.
     * @return A string view containing the input after the whitespace.
     */
    std::string_view consume_whitespace(std::string_view input) {
        // Traverse through the input and find the first non-blank character
        for(auto it = input.begin(); it < input.end(); ++it) {
            char c = *it;

            // If a non-blank character is found, return the remaining input
            if(!std::isblank(c)) {
                return std::string_view(it, input.end());
            }
        }

        // If no non-blank character is found, return the original input
        return input;
    }
}