.data
num1: .word 0
$stack: .space 400
$str0: .asciiz "input two numbers(>0):"
$str1: .asciiz "input error."
$str2: .asciiz "input error."
.text
	 la   $t8, $stack
	 li   $t9, 4
	 jal  main
	 li   $v0, 10
	 syscall
mod:
	 subi $t8, $t8, 0x8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $t0, 0($t8)
	 sw   $t0, -8($sp)
	 lw   $t0, 4($t8)
	 sw   $t0, -12($sp)
	 lw   $t0, -8($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xfffffff0
	 div  $t0, $t1
	 mflo $t3
	 sw   $t3, 0($t2)
	 lw   $t0, -16($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xffffffec
	 mul  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -8($sp)
	 lw   $t1, -20($sp)
	 addi $t2, $sp, 0xffffffe8
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $v0, -24($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
gcd:
	 subi $t8, $t8, 0x8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $t0, 0($t8)
	 sw   $t0, -8($sp)
	 lw   $t0, 4($t8)
	 sw   $t0, -12($sp)
	 lw   $t0, -12($sp)
	 li   $t1, 0
	 addi $t2, $sp, 0xfffffff0
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -16($sp)
	 beq  $t0, $0, $lab0
	 lw   $v0, -8($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab0:
	 lw   $t1, -12($sp)
	 sw   $t1, 0($t8)
	 add  $t8, $t8, $t9
	 lw   $t1, -8($sp)
	 sw   $t1, 0($t8)
	 add  $t8, $t8, $t9
	 lw   $t1, -12($sp)
	 sw   $t1, 0($t8)
	 add  $t8, $t8, $t9
	 move $fp, $sp
	 subi $sp, $sp, 0x1c
	 jal  mod
	 sw   $v0, -20($sp)
	 lw   $t1, -20($sp)
	 sw   $t1, 0($t8)
	 add  $t8, $t8, $t9
	 move $fp, $sp
	 subi $sp, $sp, 0x1c
	 jal  gcd
	 sw   $v0, -24($sp)
	 lw   $v0, -24($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
main:
	 subi $t8, $t8, 0x0
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 la   $a0, $str0
	 li   $v0, 4
	 syscall
	 la   $t0, num1
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 addi $t0, $sp, 0xfffffff8
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 la   $t0, num1
	 lw   $t0, 0($t0)
	 li   $t1, 0
	 addi $t2, $sp, 0xfffffff4
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -12($sp)
	 beq  $t0, $0, $lab1
	 la   $a0, $str1
	 li   $v0, 4
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab1:
	 lw   $t0, -8($sp)
	 li   $t1, 0
	 addi $t2, $sp, 0xfffffff0
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -16($sp)
	 beq  $t0, $0, $lab2
	 la   $a0, $str2
	 li   $v0, 4
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab2:
	 la   $t0, num1
	 lw   $t1, 0($t0)
	 sw   $t1, 0($t8)
	 add  $t8, $t8, $t9
	 lw   $t1, -8($sp)
	 sw   $t1, 0($t8)
	 add  $t8, $t8, $t9
	 move $fp, $sp
	 subi $sp, $sp, 0x18
	 jal  gcd
	 sw   $v0, -20($sp)
	 lw   $a0, -20($sp)
	 li   $v0, 1
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
