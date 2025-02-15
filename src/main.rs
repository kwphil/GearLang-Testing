mod bin_op;
mod num;

use nom::IResult;

pub use bin_op::*;
pub use num::*;

fn main() {

}

pub trait Expression {
    fn new(input: &str) -> IResult<&str, Box<Self>>; 
}

#[cfg(test)]
mod test {
    use crate::*;

    #[test]
    fn parse_num() {
        assert_eq!(Number::new("42"), Ok(("", Box::new(Number::Integer(42)))))
    }

    #[test]
    fn parse_expr() {
        assert_eq!(BinaryOperation::new("42   +12"), Ok(("", Box::new(BinaryOperation {
            left: Box::new(Number::Integer(42)),
            operator: BinaryOperator::Add,
            right: Box::new(Number::Integer(12)),
        }))));
    }
}