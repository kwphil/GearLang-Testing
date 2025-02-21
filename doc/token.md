# Understanding Tokens

Tokens are a crucial part in the parser, so I have done my best to ensure that they are easy to add on to.

All tokens are to be derived from the `std_gearlang::token::Base` class, here is the class:

```cpp
class Base {
public:
    virtual ~Base() = default;
    virtual inline std::string type() const = 0;
    virtual inline std::string get_value() const = 0;
    static std_gearlang::NoErr_Result<std::shared_ptr<Base>> try_parse(std::string_view input);
}
```

* `type` - This is a human-readable version of the token type. For example - Return would return "return"
* `get_value` - Gets the value stored in the class, For example - Number(0) would return "0"
* `try_parse` - This will attempt to parse the token. If successful, it will return a shared pointer to the class, and a `string_view`, containing the rest of the input. If it fails, it will simply return `nullopt`.

## Some Functions to Help

I have written some functions to help with repetition.

* `get_identifier` - Will return the string of the identifier, and the rest of the input. This is especially good for matching keywords.
* `consume_whitespace` - I doubt you'll have to worry about this, but it just gets rid of the whitespace at the beginning of the input. This is used in `Parser::next_token`, so you probably don't need to worry about it.