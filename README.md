# GearLang

This is the main source code repository for GearLang. It will contain the std library, and docs.

This project is **UNDER DEVELOPMENT**. You can contribute by forking the repo and creating a merge request.

## Why GearLang?

- **Performance:** Fast and easily optimizable, suitable for OS development and Systems Programming.
- **Easy Readability:** Offers a clean and flexible syntax, built for being read by humans.

## Why not C? 

C is an amazing language, don't get me wrong. But it is very easy to shoot your foot off. GearLang attempts to solve this using a few different tactics.

### Comptime Checks 

`comptime checks`, can automatically run tests during the compilation process to prevent as many bugs as possible.

This ensures that there no implications on hindering performance, while still keeping the error handling as much as possible.

```gear
fn main {
    sub a b;

    exit 0;
}

fn sub a:i32, b:i32 {
    comptime assert a > 0;

    return a-b;
}
```

### Native Language Interoperability

One of the things that C has trouble with is keeping native interoperability within different languages. It's very difficult to use C++ classes in C without vastly hindering readability. And forget about Rust with its many, many features it implements. GearLang attempts to solve this by being able to convert to multiple languages.

```gear
!include {
    extern C::printf,
    extern C++::std::{
        allocator as cxx::allocator,
        vector<T, Allocator=cxx::allocator>,
    }
    extern Rust::std::Result,
    error,
};

fn main {
    printf(c"%s", c"Hello, World!");

    mut vec = vector<int>();

    vec.push_back(32);

    Result<void, error>::Err("Whoops!");
}
```

## License

GearLang is primarily distributed under the terms of the GPLv3 License. You are allowed to fork it however you want, AS LONG as you keep it open-sourced. 

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
