.data
base: .space 800
exp: .space 800
cnt: .word 0
$str0: .asciiz "Number is out of range."
$str1: .asciiz "Number is out of range."
$str2: .asciiz "="
$str3: .asciiz "*"
$str4: .asciiz "^"
$str5: .asciiz "Number is out of range."
$str6: .asciiz "Number is out of range."
$str7: .asciiz "Prime numbers:"
$str8: .asciiz " "
.text
	 jal  main
	 li   $v0, 10
	 syscall
mod:
	 subi $gp, $gp, 8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s0, 0($gp)
	 lw   $s1, 4($gp)
	 move $t8, $s0
	 move $t9, $s1
	 div  $t8, $t9
	 mflo $t8
	 move $a1, $t8
	 move $t8, $a1
	 move $t9, $s1
	 mul  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $s0
	 move $t9, $a2
	 sub  $t8, $t8, $t9
	 move $a3, $t8
	 move $v0, $a3
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
init:
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t8, 2
	 move $s0, $t8
	 li   $t8, 0
	 la   $t9, cnt
	 sw   $t8, 0($t9)
$lab0:
	 addi $t8, $sp, -40
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 1
	 sw   $t9, 0($t8)
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $t8, $s0
	 li   $t9, 1000
	 sle  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 bne  $t8, $0, $lab0
	 li   $t8, 2
	 move $s0, $t8
$lab1:
	 addi $t8, $sp, -40
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab3
	 la   $t8, base
	 la   $t9, cnt
	 lw   $t9, 0($t9)
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 move $t9, $s0
	 sw   $t9, 0($t8)
	 la   $t8, exp
	 la   $t9, cnt
	 lw   $t9, 0($t9)
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 li   $t9, 0
	 sw   $t9, 0($t8)
	 la   $t8, cnt
	 lw   $t8, 0($t8)
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 la   $t9, cnt
	 sw   $t8, 0($t9)
	 li   $t8, 2
	 move $s1, $t8
	 move $t8, $s0
	 move $t9, $s1
	 mul  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 li   $t9, 1000
	 sle  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 beq  $t8, $0, $lab3
$lab4:
	 move $t8, $s0
	 move $t9, $s1
	 mul  $t8, $t8, $t9
	 move $a1, $t8
	 addi $t8, $sp, -40
	 move $t9, $a1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 0
	 sw   $t9, 0($t8)
	 move $t8, $s1
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s1, $t8
	 move $t8, $s0
	 move $t9, $s1
	 mul  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 li   $t9, 1000
	 sle  $t8, $t8, $t9
	 move $a3, $t8
	 move $t8, $a3
	 bne  $t8, $0, $lab4
$lab3:
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $t8, $s0
	 li   $t9, 1000
	 sle  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 bne  $t8, $0, $lab1
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
resolve:
	 subi $gp, $gp, 8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s1, 0($gp)
	 lw   $s0, 4($gp)
	 move $t8, $s1
	 li   $t9, 1
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab5
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
$lab5:
	 sw   $s1, 0($gp)
	 addi $gp, $gp, 4
	 la   $t8, base
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 addi $t9, $sp, -40
	 sw   $t8, 0($t9)
	 lw   $t8, -40($sp)
	 sw   $t8, 0($gp)
	 addi $gp, $gp, 4
	 sw   $s0, -8($sp)
	 sw   $s1, -12($sp)
	 sw   $s2, -16($sp)
	 sw   $s3, -20($sp)
	 sw   $s4, -24($sp)
	 sw   $s5, -28($sp)
	 sw   $s6, -32($sp)
	 sw   $s7, -36($sp)
	 move $fp, $sp
	 subi $sp, $sp, 64
	 jal  mod
	 move $a1, $v0
	 move $t8, $a1
	 li   $t9, 0
	 seq  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 beq  $t8, $0, $lab6
	 la   $t8, exp
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 addi $t9, $sp, -44
	 sw   $t8, 0($t9)
	 lw   $t8, -44($sp)
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 sw   $t8, -48($sp)
	 la   $t8, exp
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t9, -48($sp)
	 sw   $t9, 0($t8)
	 la   $t8, base
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 addi $t9, $sp, -52
	 sw   $t8, 0($t9)
	 move $t8, $s1
	 lw   $t9, -52($sp)
	 div  $t8, $t9
	 mflo $t8
	 sw   $t8, -56($sp)
	 lw   $t8, -56($sp)
	 sw   $t8, 0($gp)
	 addi $gp, $gp, 4
	 sw   $s0, 0($gp)
	 addi $gp, $gp, 4
	 sw   $s0, -8($sp)
	 sw   $s1, -12($sp)
	 sw   $s2, -16($sp)
	 sw   $s3, -20($sp)
	 sw   $s4, -24($sp)
	 sw   $s5, -28($sp)
	 sw   $s6, -32($sp)
	 sw   $s7, -36($sp)
	 move $fp, $sp
	 subi $sp, $sp, 64
	 jal  resolve
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
$lab6:
	 sw   $s1, 0($gp)
	 addi $gp, $gp, 4
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 sw   $t8, -60($sp)
	 lw   $t8, -60($sp)
	 sw   $t8, 0($gp)
	 addi $gp, $gp, 4
	 sw   $s0, -8($sp)
	 sw   $s1, -12($sp)
	 sw   $s2, -16($sp)
	 sw   $s3, -20($sp)
	 sw   $s4, -24($sp)
	 sw   $s5, -28($sp)
	 sw   $s6, -32($sp)
	 sw   $s7, -36($sp)
	 move $fp, $sp
	 subi $sp, $sp, 64
	 jal  resolve
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
main:
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 sw   $s0, -8($sp)
	 sw   $s1, -12($sp)
	 sw   $s2, -16($sp)
	 sw   $s3, -20($sp)
	 sw   $s4, -24($sp)
	 sw   $s5, -28($sp)
	 sw   $s6, -32($sp)
	 sw   $s7, -36($sp)
	 move $fp, $sp
	 subi $sp, $sp, 48
	 jal  init
	 li   $v0, 12
	 syscall
	 move $s2, $v0
	 li   $v0, 5
	 syscall
	 move $s1, $v0
	 move $t8, $s2
	 li   $t9, 114
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab7
	 move $t8, $s1
	 li   $t9, 2
	 slt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab8
	 la   $a0, $str0
	 li   $v0, 4
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
$lab8:
	 move $t8, $s1
	 li   $t9, 1000
	 sgt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab9
	 la   $a0, $str1
	 li   $v0, 4
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
$lab9:
	 sw   $s1, 0($gp)
	 addi $gp, $gp, 4
	 li   $t8, 0
	 sw   $t8, 0($gp)
	 addi $gp, $gp, 4
	 sw   $s0, -8($sp)
	 sw   $s1, -12($sp)
	 sw   $s2, -16($sp)
	 sw   $s3, -20($sp)
	 sw   $s4, -24($sp)
	 sw   $s5, -28($sp)
	 sw   $s6, -32($sp)
	 sw   $s7, -36($sp)
	 move $fp, $sp
	 subi $sp, $sp, 48
	 jal  resolve
	 move $a0, $s1
	 li   $v0, 1
	 syscall
	 la   $a0, $str2
	 li   $v0, 4
	 syscall
	 li   $t8, 0
	 move $s3, $t8
	 li   $t8, 0
	 move $s0, $t8
$lab10:
	 la   $t8, exp
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $t8, $a1
	 li   $t9, 0
	 sgt  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 beq  $t8, $0, $lab11
	 move $t8, $s3
	 beq  $t8, $0, $lab12
	 la   $a0, $str3
	 li   $v0, 4
	 syscall
$lab12:
	 la   $t8, base
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $a0, $a1
	 li   $v0, 1
	 syscall
	 la   $t8, exp
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a2, $t8
	 move $t8, $a2
	 li   $t9, 1
	 sgt  $t8, $t8, $t9
	 move $a3, $t8
	 move $t8, $a3
	 beq  $t8, $0, $lab13
	 la   $a0, $str4
	 li   $v0, 4
	 syscall
	 la   $t8, exp
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $a0, $a1
	 li   $v0, 1
	 syscall
$lab13:
	 li   $t8, 1
	 move $s3, $t8
$lab11:
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $t8, $s0
	 la   $t9, cnt
	 lw   $t9, 0($t9)
	 slt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 bne  $t8, $0, $lab10
$lab7:
	 move $t8, $s2
	 li   $t9, 116
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab14
	 move $t8, $s1
	 li   $t9, 2
	 slt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab15
	 la   $a0, $str5
	 li   $v0, 4
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
$lab15:
	 move $t8, $s1
	 li   $t9, 1000
	 sgt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab16
	 la   $a0, $str6
	 li   $v0, 4
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
$lab16:
	 la   $a0, $str7
	 li   $v0, 4
	 syscall
	 li   $t8, 0
	 move $s0, $t8
$lab17:
	 la   $a0, $str8
	 li   $v0, 4
	 syscall
	 la   $t8, base
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $a0, $a1
	 li   $v0, 1
	 syscall
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $t8, $s0
	 la   $t9, cnt
	 lw   $t9, 0($t9)
	 sge  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 beq  $t8, $0, $lab18
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
$lab18:
	 la   $t8, base
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 add  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $t8, $a1
	 move $t9, $s1
	 sle  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 bne  $t8, $0, $lab17
$lab14:
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 lw   $s0, -8($sp)
	 lw   $s1, -12($sp)
	 lw   $s2, -16($sp)
	 lw   $s3, -20($sp)
	 lw   $s4, -24($sp)
	 lw   $s5, -28($sp)
	 lw   $s6, -32($sp)
	 lw   $s7, -36($sp)
	 jr   $ra
