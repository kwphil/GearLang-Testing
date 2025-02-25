# Defining the Syntax Tree

There is not yet a base class for a node

## Statements

Statements can be the following:

* An `exit` keyword followed by a number
* A `return` keyword followed by a value or variable
* An `expression`

**ALL** statements are to be followed by a semicolon, else it is not a statement.

### Base Class

```cpp
class Statement {
public:
    static try_parse(std::span<std::shared_ptr<token::Base>>) -> std::optional<std::shared_ptr<Statement>>;
}
```

`try_parse` takes an input of a section of the vector of tokens, and then searches for the next semicolon. If it finds one, it will go through the list of statement parsers to see if they match.
