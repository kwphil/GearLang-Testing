use std::str::FromStr;

use nom::{
    character::complete::digit1, 
    combinator::map, 
    IResult
};

use crate::Expression;

#[derive(Debug, PartialEq)]
pub enum Number {
    Integer(i32),
    Float(f32)
}

impl Expression for Number {
    fn new(input: &str) -> IResult<&str, Box<Self>> {
        map(digit1, |n| Box::new(Number::Integer(i32::from_str(n).unwrap())))(input)
    }
}