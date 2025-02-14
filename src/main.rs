use nom::{
    character::complete::{char, digit1},
    combinator::{map_res, recognize},
    IResult,
};

fn parse_number(input: &str) -> IResult<&str, i32> {
    map_res(recognize(digit1), str::parse)(input)
}

fn parse_addition(input: &str) -> IResult<&str, i32> {
    let (input, (lhs, _, rhs)) = tupl((parse_number, char('+'), parse_number))(input)?;
    Ok((input, lhs + rhs))
}

fn main() {
    let expr = "12+34";

    match parse_addition(expr) {
        Ok((_, result)) => println!("Result: {}", result),
        Err(err) => println!("Error: {:?}", err),
    }
}
