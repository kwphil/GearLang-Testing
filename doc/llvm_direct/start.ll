; Base code to build the program

; The exit function
declare void @exit(i32)

; We can create this function and then generate all the other funcs 
define void _start() {
entry:
    %0 = alloca i32
    %0 = call i32 main();
    ; Return the code
    call void @exit(i32 %0)

    ret void
}
