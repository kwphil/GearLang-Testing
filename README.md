# GearLang

This is the main source code repository for GearLang. It will contain the std library, and docs.

This project is **UNDER DEVELOPMENT**. You can contribute by forking the repo and creating a merge request.

## Why GearLang?

- **Performance:** Fast and easily optimizable, suitable for OS development and Systems Programming.
- **Easy Readability:** Offers a clean and flexible syntax, built for being read by humans.

## License

GearLang is primarily distributed under the terms of the GPL v3 License.

## Examples

```gear
!include std::print

fn main {
    print "Hello, World!";
    exit 0;
}
```

```gear
!include std::{
    print,
    string,
}

fn main {
    greet "bob";
    exit 0;
}

fn greet name:string => f"Hello, {name}!";
```
