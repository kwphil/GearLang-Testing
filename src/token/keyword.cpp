#include "../token.cpp"

namespace std_gearlang::token {
        /**
     * Represents a "return" token in GearLang.
     * This class attempts to parse the "return" keyword from the input string.
     */
    class Return : public Base {
    public:
        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            // Check if the identifier matches "return"
            if(identifier == "return") {
                return std::make_tuple(std::make_shared<Return>(), new_input);
            }

            // If the identifier does not match, return std::nullopt
            return std::nullopt;
        }

        inline std::string type() const override {
            return "return";
        }

        inline std::string get_value() const override {
            return type();
        }
    };

    /**
     * Represents an "exit" token in GearLang.
     * This class attempts to parse the "exit" keyword from the input string.
     */
    class Exit : public Base {
    public:
        static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input) {
            auto [ identifier, new_input ] = std_gearlang::get_identifier(input);

            // Check if the identifier matches "exit"
            if(identifier == "exit") {
                return std::make_tuple(std::make_shared<Exit>(), new_input);
            }

            // If the identifier does not match, return std::nullopt
            return std::nullopt;
        }

        inline std::string type() const override {
            return "exit";
        }

        inline std::string get_value() const override {
            return type();
        }
    };
}