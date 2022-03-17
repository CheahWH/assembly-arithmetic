/* CMPE102 - HW#1 template */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long rotate(long op1, int i, long op2);

/* Example - add function */
long add(long op1, long op2) {
    long output = 0;
    asm
    (
    "movq %1, %%rax;"
    "addq %2, %%rax;"
    : "=a" (output)
    : "m" (op1), "m" (op2)
    :
    ); /* add the second operand to eax, eax has result */
    return output;
}

/*
1. long mult (long op1, long op2)
- Can t use the MULQ/IMULQ instructions, meaning you use ADD repeatedly�
- If there are overflow, return the overflowed values in EAX register
*/
long mult(long op1, long op2) {
    long output = 0;
    asm
    (
    "movq %1, %%rdx;"
    "movq %2, %%rbx;"

    "loop1:"
        "addq %%rdx, %%rax;"
        "dec %%rbx;"
        "cmp $1, %%rbx;"
        "jg loop1;"

    : "=a" (output)
    : "m" (op1), "m" (op2)
    :
    ); /* multiple the second operand to eax, eax has result */
    return output;
}

long XOR(long op1, long op2) {
    long output = 0;
    asm
    (
    "movq %1, %%rax;"
    "xor %2, %%rax;"
    : "=a" (output)
    : "m" (op1), "m" (op2)
    :
    ); /* add the second operand to eax, eax has result */
    return output;
}


/*
2. long mod (long op1, long op2)
- mod will return the remainder of op1 / op2
- can use IDIVQ instruction
*/
long mod(long op1, long op2) {
    long output = 0;
    long local_op2 = op2;
    asm
    (
    "movq %1, %%rax;"
    "movq %2, %%rbx;"
    "cdq;"
    "idivq %%rbx;"
    "movq %%rdx, %%rax;"
    : "=a" (output)
    : "m" (op1), "m" (local_op2)
    :
    );
    return output;
}

/*
3. long shift (long op1, long direction, long number_of_bits)
- shift will perform arithmetic (SAR or SAL) bit-shifting of the input operand
(op1)
- direction = 0 for left and 1 for right
- number_of_bits will dictate how many bits to shift left or right
*/
long shift(long op1, long direction, long number_of_bits) {
    long output = 0;
    long is_left = direction == 0 ? 1 : 0;
// printf("direction=%ld\n",is_left);
/*  move first operand to eax  */
/* move direction flag to ebx  */
/* move bit count to ecx, but use cl only on sar or sal commands */
/* check if 0 (Left) */
/* shift right if not 0  */
    asm
    (
    "movq %1, %%rax;"
    "movq %2, %%rbx;"
    "movq %3, %%rcx;"
    "cmpq $1, %%rbx;"
    "jz Shift_Left ;"
    "sarq %%cl, %%rax ;"
    "jmp done;"
    "Shift_Left:"
    "salq %%cl, %%rax;"
    "done:"
    : "=a" (output)
    : "m" (op1), "m" (is_left), "m" (number_of_bits)
    :
    );
    return output;
}



/*
4. int factorial ( int op1 )
- Input a positive integer (>0) and return the result of op1!
- Must use a loop to compute the result (no recursion)
*/
long factorial(long n) {
    long output = 0;

    asm
    (
    "movq %1, %%rdx;"
    "movq %1, %%rax;"

    "loop2:"
    "dec %%rdx;"
    "imulq %%rdx, %%rax;"
    "cmp $1, %%rdx;"
    "jg loop2;"

    : "=a" (output)
    : "m" (n)
    ); /* add the second operand to eax, eax has result */
    return output;
}

long rotate(long op1, int direction, long number_of_bits) {
    long output = 0;
    long is_left = direction == 0 ? 1 : 0;
// printf("direction=%ld\n",is_left);
/*  move first operand to eax  */
/* move direction flag to ebx  */
/* move bit count to ecx, but use cl only on sar or sal commands */
/* check if 0 (Left) */
/* shift right if not 0  */
    asm
    (
    "movq %1, %%rax;"
    "movq %2, %%rbx;"
    "movq %3, %%rcx;"
    "cmpq $1, %%rbx;"
    "jz Rotate_Left ;"

    "rorq %%cl, %%rax ;"
    "jmp done2;"

    "Rotate_Left:"
    "rolq %%cl, %%rax;"

    "done2:"
    : "=a" (output)
    : "m" (op1), "m" (is_left), "m" (number_of_bits)
    :
    );
    return output;}

int main(int argc, char **argv) {
    long op1, op2, result;
    op1 = op2 = result = 0;
    if (argc != 3) {
        printf("Usage: %s op1 op2 (two integers)\n", argv[0]);
        return 1;
    }
    op1 = atol(argv[1]);
    op2 = atol(argv[2]);
    printf("Operand 1 = %ld x%016lx  Operand 2 = %ld x%016lx\n", op1, op1, op2, op2);
    result = add(op1, op2);
    printf("Add():\t%10ld   x%016lx\n", result, result);

result = XOR(op1, op2);
printf("XOR():\t%10ld   x%016lx\n", result, result);

    result = mult(op1, op2);
    printf("Mult():\t%10ld   x%016lx\n", result, result);
    if (op2 == 0) {
        printf("Mod Error: Divide by 0\n");
        result = 0;
    } else {
        result = mod(op1, op2);
        printf("Mod():\t%10ld   x%016lx\n", result, result);
    }
    if (op2 < 0) {
        printf("Error: Shift count must be >= 0\n");
        result = 0;
    } else {
        result = shift(op1, 0, op2);
        printf("ShiftL:\t%10ld   x%016lx\n", result, result);
        result = shift(op1, 1, op2);
        printf("ShiftR:\t%10ld   x%016lx\n", result, result);
    }

if (op2 < 0)
{
  printf("Error: Rotate count must be >= 0\n");
  result = 0;
}
else
{
     result = rotate(op1, 0, op2);
  printf("RotateL:%10ld   x%016lx\n", result, result);
  result = rotate(op1, 1, op2);
  printf("RotateR:%10ld   x%016lx\n", result, result);
    }

    if (op1 <= 0) {
        printf("Error: Factorial input must be a positive integer >=1\n");
        result = 0;
    } else {
        result = factorial(op1);
        printf("Fact():\t%10ld   x%016lx\n\n", result, result);
    }
    return 0;
}


