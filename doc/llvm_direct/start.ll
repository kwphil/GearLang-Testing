; Base code to build the program

; We can create this function and then generate all the other funcs 
define i32 _start() {
entry:
    %0 = alloca i32
    %0 = call i32 main();

    ret %0
}
