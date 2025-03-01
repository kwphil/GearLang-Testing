// <gearlang/helper.cpp> -*- C++ -*-

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

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