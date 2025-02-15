use crate::{Number, Expression};

use nom::{
    branch::alt, 
    bytes::complete::tag, 
    character::complete::space0, 
    combinator::map, 
    sequence::tuple, 
    IResult
};

#[derive(Debug, PartialEq)]
pub struct BinaryOperation {
    pub left: Box<Number>,
    pub operator: BinaryOperator,
    pub right: Box<Number>,
}

#[derive(Debug, PartialEq)]
pub enum BinaryOperator {
    Add,
    Subtract,
    Multiply,
    Divide
}

impl BinaryOperator {
    fn new(input: &str) -> IResult<&str, Self> {
        let (input, operator) = alt((
            map(tag("+"), |_| Self::Add),
            map(tag("-"), |_| Self::Subtract),
            map(tag("*"), |_| Self::Multiply),
            map(tag("/"), |_| Self::Divide),
        ))(input)?;

        Ok((input, operator))        
    }
}

impl Expression for BinaryOperation {
    fn new(input: &str) -> IResult<&str, Box<Self>> {
        map(
            tuple((
                Number::new,
                space0, 
                BinaryOperator::new,
                space0, 
                Number::new
            )),
            |(left, _, operator, _, right)| {
                Box::new(Self {left, operator, right})
            }
        )(input)
    }
}