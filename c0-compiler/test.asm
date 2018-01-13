.data
_cha: .word 0
chb: .space 24
chc: .word 95
chd: .word 95
$str0: .asciiz "test line:"
$str1: .asciiz "test fib:"
$str2: .asciiz "fib="
$str3: .asciiz "test function:"
$str4: .asciiz "test switch:"
$str5: .asciiz "key is 0"
$str6: .asciiz "key is "
$str7: .asciiz "key is 2"
.text
	 jal  main
	 li   $v0, 10
	 syscall
f:
	 subi $gp, $gp, 8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s0, 0($gp)
	 lw   $s1, 4($gp)
	 move $t8, $s0
	 li   $t9, 1
	 sgt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab0
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $a1, $t8
	 move $v0, $a1
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
$lab0:
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 sw   $s0, 0($gp)
	 addi $gp, $gp, 4
	 sw   $s1, 0($gp)
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
	 subi $sp, $sp, 44
	 jal  f
	 move $t8, $s0
	 move $t9, $s1
	 add  $t8, $t8, $t9
	 move $a1, $t8
	 move $v0, $a1
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
compare:
	 subi $gp, $gp, 8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s0, 0($gp)
	 lw   $s1, 4($gp)
	 move $t8, $s0
	 move $t9, $s1
	 sgt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab1
	 li   $v0, 1
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
$lab1:
	 move $t8, $s0
	 move $t9, $s1
	 sle  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab2
	 li   $a1, -1
	 move $v0, $a1
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
$lab2:
	 li   $v0, 95
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
line:
	 subi $gp, $gp, 8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $t8, 0($gp)
	 sw   $t8, -40($sp)
	 lw   $t8, 4($gp)
	 sw   $t8, -44($sp)
	 li   $t8, 1
	 move $s0, $t8
	 li   $t8, 1
	 move $s3, $t8
$lab3:
	 addi $t8, $sp, -48
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $s0
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -448
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $s0
	 sw   $t9, 0($t8)
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $t8, $s0
	 lw   $t9, -40($sp)
	 sle  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 bne  $t8, $0, $lab3
	 li   $t8, 1
	 move $s0, $t8
$lab4:
	 move $t8, $s0
	 li   $t9, 1
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab5
	 li   $t8, 3
	 move $s4, $t8
	 li   $t8, 2
	 move $s5, $t8
$lab5:
	 move $t8, $s0
	 li   $t9, 2
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab6
	 li   $t8, 8
	 move $s4, $t8
	 li   $s5, -3
$lab6:
	 move $t8, $s0
	 li   $t9, 3
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab7
	 li   $t8, 3
	 move $s4, $t8
	 li   $s5, -2
$lab7:
	 move $t8, $s5
	 li   $t9, 0
	 sne  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab8
	 sw   $s5, 0($gp)
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
	 subi $sp, $sp, 896
	 jal  compare
	 move $s7, $v0
	 move $t8, $s7
	 move $t9, $s5
	 mul  $t8, $t8, $t9
	 sw   $t8, -848($sp)
	 addi $t8, $sp, -48
	 move $t9, $s4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $s1, $t8
$lab9:
	 move $t8, $s1
	 move $t9, $s7
	 add  $t8, $t8, $t9
	 move $a1, $t8
	 addi $t8, $sp, -448
	 move $t9, $a1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $s2, $t8
	 addi $t8, $sp, -48
	 move $t9, $s2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $s6, $t8
	 addi $t8, $sp, -448
	 move $t9, $s1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $s2
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -48
	 move $t9, $s2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $s1
	 sw   $t9, 0($t8)
	 move $t8, $s6
	 move $s1, $t8
	 move $t8, $s3
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s3, $t8
	 move $t8, $s3
	 lw   $t9, -848($sp)
	 sle  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 bne  $t8, $0, $lab9
	 addi $t8, $sp, -448
	 move $t9, $s6
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $s4
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -48
	 move $t9, $s4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $t8, $a1
	 move $t9, $s5
	 add  $t8, $t8, $t9
	 move $a2, $t8
	 addi $t8, $sp, -48
	 move $t9, $s4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $a2
	 sw   $t9, 0($t8)
$lab8:
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $t8, $s0
	 lw   $t9, -44($sp)
	 sle  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 bne  $t8, $0, $lab4
	 addi $t8, $sp, -448
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $a0, $a1
	 li   $v0, 1
	 syscall
	 li   $t8, 2
	 move $s0, $t8
$lab10:
	 addi $t8, $sp, -448
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
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
	 lw   $t9, -40($sp)
	 sle  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 bne  $t8, $0, $lab10
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
f2:
	 subi $gp, $gp, 4
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s0, 0($gp)
	 li   $t8, 1
	 move $s1, $t8
	 move $t8, $s0
	 move $t9, $s1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $v0, $s0
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
fib:
	 subi $gp, $gp, 4
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s0, 0($gp)
	 move $t8, $s0
	 li   $t9, 0
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab11
	 li   $v0, 0
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
$lab11:
	 move $t8, $s0
	 li   $t9, 1
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab12
	 li   $v0, 1
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
$lab12:
	 move $t8, $s0
	 li   $t9, 1
	 sub  $t8, $t8, $t9
	 move $a1, $t8
	 sw   $a1, 0($gp)
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
	 subi $sp, $sp, 44
	 jal  fib
	 move $a2, $v0
	 move $t8, $s0
	 li   $t9, 2
	 sub  $t8, $t8, $t9
	 move $a3, $t8
	 sw   $a3, 0($gp)
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
	 subi $sp, $sp, 44
	 jal  fib
	 move $t0, $v0
	 move $t8, $a2
	 move $t9, $t0
	 add  $t8, $t8, $t9
	 move $s1, $t8
	 move $v0, $s1
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
nest:
	 subi $gp, $gp, 0
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 addi $t8, $sp, -40
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 1
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -100
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 3
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -40
	 li   $t9, 3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 4
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -100
	 li   $t9, 4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 6
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -40
	 li   $t9, 6
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 8
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -40
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 addi $t8, $sp, -100
	 move $t9, $a1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a2, $t8
	 addi $t8, $sp, -40
	 move $t9, $a2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a3, $t8
	 addi $t8, $sp, -100
	 move $t9, $a3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t0, $t8
	 addi $t8, $sp, -40
	 move $t9, $t0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t1, $t8
	 addi $t8, $sp, -100
	 move $t9, $t1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 2333
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -100
	 li   $t9, 8
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t2, $t8
	 move $t8, $a1
	 move $t9, $t2
	 add  $t8, $t8, $t9
	 move $t3, $t8
	 move $a0, $t3
	 li   $v0, 1
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
t:
	 subi $gp, $gp, 4
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s0, 0($gp)
	 move $t8, $s0
	 li   $t9, 99
	 sgt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab13
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
$lab13:
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $a0, $s0
	 li   $v0, 11
	 syscall
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
	 subi $sp, $sp, 44
	 jal  t
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
	 subi $gp, $gp, 0
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t8, 43
	 la   $t9, chc
	 sw   $t8, 0($t9)
	 li   $t8, 45
	 la   $t9, chd
	 sw   $t8, 0($t9)
	 li   $t8, 3
	 move $s4, $t8
	 li   $t8, 0
	 move $s0, $t8
	 li   $s5, -2
	 li   $t8, 1
	 move $s1, $t8
	 li   $v0, 5
	 syscall
	 move $s2, $v0
	 move $t8, $s2
	 li   $t9, 0
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab14
	 la   $a0, $str0
	 li   $v0, 4
	 syscall
	 li   $t8, 8
	 sw   $t8, 0($gp)
	 addi $gp, $gp, 4
	 li   $t8, 3
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
	 subi $sp, $sp, 116
	 jal  line
$lab14:
	 move $t8, $s2
	 li   $t9, 1
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab15
	 la   $a0, $str1
	 li   $v0, 4
	 syscall
	 li   $t8, 3
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
	 subi $sp, $sp, 116
	 jal  fib
	 move $s6, $v0
	 la   $a0, $str2
	 li   $v0, 4
	 syscall
	 move $a0, $s6
	 li   $v0, 1
	 syscall
$lab15:
	 move $t8, $s2
	 li   $t9, 2
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab24
$lab17:
	 addi $t8, $sp, -60
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 li   $t9, 97
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -40
	 move $t9, $s0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $s0
	 sw   $t9, 0($t8)
	 move $t8, $s0
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $s0, $t8
	 move $t8, $s0
	 li   $t9, 5
	 slt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 bne  $t8, $0, $lab17
	 li   $v0, 5
	 syscall
	 move $s1, $v0
	 li   $v0, 5
	 syscall
	 move $s3, $v0
	 move $t8, $s1
	 li   $t9, 3
	 slt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab18
	 move $t8, $s3
	 move $t9, $s4
	 add  $t8, $t8, $t9
	 move $s3, $t8
	 move $a0, $s3
	 li   $v0, 1
	 syscall
$lab18:
	 move $t8, $s1
	 li   $t9, 3
	 sle  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab19
	 move $t8, $s4
	 move $t9, $s3
	 sub  $t8, $t8, $t9
	 move $s4, $t8
	 addi $t8, $sp, -40
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $t8, $a1
	 move $t9, $s4
	 add  $t8, $t8, $t9
	 move $a2, $t8
	 addi $t8, $sp, -40
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $a2
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -60
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a3, $t8
	 move $t8, $a3
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $t0, $t8
	 addi $t8, $sp, -60
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $t0
	 sw   $t9, 0($t8)
	 move $a0, $s4
	 li   $v0, 1
	 syscall
	 addi $t8, $sp, -60
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t1, $t8
	 move $a0, $t1
	 li   $v0, 11
	 syscall
	 addi $t8, $sp, -40
	 li   $t9, 0
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t2, $t8
	 move $a0, $t2
	 li   $v0, 1
	 syscall
$lab19:
	 move $t8, $s1
	 li   $t9, 6
	 sgt  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab20
	 move $t8, $s3
	 move $t9, $s4
	 mul  $t8, $t8, $t9
	 move $s5, $t8
	 addi $t8, $sp, -40
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $t8, $a1
	 move $t9, $s5
	 add  $t8, $t8, $t9
	 move $a2, $t8
	 addi $t8, $sp, -40
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $a2
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -60
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a3, $t8
	 move $t8, $a3
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $t0, $t8
	 addi $t8, $sp, -60
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $t0
	 sw   $t9, 0($t8)
	 move $a0, $s5
	 li   $v0, 1
	 syscall
	 addi $t8, $sp, -60
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t1, $t8
	 move $a0, $t1
	 li   $v0, 11
	 syscall
	 addi $t8, $sp, -40
	 li   $t9, 1
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t2, $t8
	 move $a0, $t2
	 li   $v0, 1
	 syscall
$lab20:
	 move $t8, $s1
	 li   $t9, 6
	 sge  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab21
	 move $t8, $s3
	 move $t9, $s4
	 div  $t8, $t9
	 mflo $t8
	 move $s6, $t8
	 addi $t8, $sp, -40
	 li   $t9, 2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a1, $t8
	 move $t8, $a1
	 move $t9, $s6
	 add  $t8, $t8, $t9
	 move $a2, $t8
	 addi $t8, $sp, -40
	 li   $t9, 2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $a2
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -60
	 li   $t9, 2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a3, $t8
	 move $t8, $a3
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $t0, $t8
	 addi $t8, $sp, -60
	 li   $t9, 2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $t0
	 sw   $t9, 0($t8)
	 move $a0, $s6
	 li   $v0, 1
	 syscall
	 addi $t8, $sp, -60
	 li   $t9, 2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t1, $t8
	 move $a0, $t1
	 li   $v0, 11
	 syscall
	 addi $t8, $sp, -40
	 li   $t9, 2
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t2, $t8
	 move $a0, $t2
	 li   $v0, 1
	 syscall
$lab21:
	 move $t8, $s1
	 li   $t9, 4
	 sne  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab22
	 li   $a1, 0
	 move $t8, $s3
	 move $t9, $a1
	 sub  $t8, $t8, $t9
	 move $s3, $t8
	 addi $t8, $sp, -40
	 li   $t9, 3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a2, $t8
	 move $t8, $a2
	 move $t9, $s3
	 add  $t8, $t8, $t9
	 move $a3, $t8
	 move $t8, $a3
	 li   $t9, 99
	 add  $t8, $t8, $t9
	 move $t0, $t8
	 addi $t8, $sp, -40
	 li   $t9, 3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $t0
	 sw   $t9, 0($t8)
	 addi $t8, $sp, -60
	 li   $t9, 3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t1, $t8
	 move $t8, $t1
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $t2, $t8
	 addi $t8, $sp, -60
	 li   $t9, 3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $t2
	 sw   $t9, 0($t8)
	 move $a0, $s3
	 li   $v0, 1
	 syscall
	 addi $t8, $sp, -60
	 li   $t9, 3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t3, $t8
	 move $a0, $t3
	 li   $v0, 11
	 syscall
	 addi $t8, $sp, -40
	 li   $t9, 3
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t4, $t8
	 move $a0, $t4
	 li   $v0, 1
	 syscall
$lab22:
	 move $t8, $s1
	 li   $t9, 4
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab23
	 li   $a1, 6
	 addi $t8, $sp, -60
	 li   $t9, 4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a2, $t8
	 move $t8, $a2
	 li   $t9, 1
	 add  $t8, $t8, $t9
	 move $a3, $t8
	 addi $t8, $sp, -60
	 li   $t9, 4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $a3
	 sw   $t9, 0($t8)
	 li   $t8, 0
	 move $t9, $s3
	 sub  $t8, $t8, $t9
	 move $t0, $t8
	 move $t8, $t0
	 move $t9, $a1
	 add  $t8, $t8, $t9
	 move $s3, $t8
	 move $a0, $s3
	 li   $v0, 1
	 syscall
	 addi $t8, $sp, -60
	 li   $t9, 4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t1, $t8
	 move $a0, $t1
	 li   $v0, 11
	 syscall
	 addi $t8, $sp, -40
	 li   $t9, 4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $t2, $t8
	 move $a0, $t2
	 li   $v0, 1
	 syscall
$lab23:
	 move $t8, $s1
	 beq  $t8, $0, $lab24
	 move $a0, $s3
	 li   $v0, 1
	 syscall
$lab24:
	 move $t8, $s2
	 li   $t9, 3
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab25
	 la   $a0, $str3
	 li   $v0, 4
	 syscall
	 move $t8, $s1
	 beq  $t8, $0, $lab26
	 li   $a1, -2
	 sw   $a1, 0($gp)
	 addi $gp, $gp, 4
	 li   $t8, 3
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
	 subi $sp, $sp, 116
	 jal  f
	 move $a2, $v0
	 li   $a3, 6
	 move $t8, $a3
	 li   $t9, 3
	 mul  $t8, $t8, $t9
	 move $t0, $t8
	 move $t8, $a2
	 move $t9, $t0
	 add  $t8, $t8, $t9
	 move $t1, $t8
	 addi $t8, $sp, -40
	 li   $t9, 4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 move $t9, $t1
	 sw   $t9, 0($t8)
$lab26:
	 li   $t8, 97
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
	 subi $sp, $sp, 116
	 jal  t
	 li   $t8, 97
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
	 subi $sp, $sp, 116
	 jal  f2
	 move $a1, $v0
	 move $a0, $a1
	 li   $v0, 11
	 syscall
	 addi $t8, $sp, -40
	 li   $t9, 4
	 li   $at, 4
	 mul  $t9, $t9, $at
	 sub  $t8, $t8, $t9
	 lw   $t8, 0($t8)
	 move $a2, $t8
	 move $a0, $a2
	 li   $v0, 1
	 syscall
$lab25:
	 move $t8, $s2
	 li   $t9, 4
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab32
	 la   $a0, $str4
	 li   $v0, 4
	 syscall
	 li   $v0, 5
	 syscall
	 move $s1, $v0
	 move $t8, $s1
	 li   $t9, 1
	 mul  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 li   $t9, 0
	 seq  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 beq  $t8, $0, $lab28
	 la   $a0, $str5
	 li   $v0, 4
	 syscall
$lab28:
	 move $t8, $a1
	 li   $t9, 1
	 seq  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 beq  $t8, $0, $lab29
	 la   $a0, $str6
	 li   $v0, 4
	 syscall
	 move $a0, $s1
	 li   $v0, 1
	 syscall
$lab29:
	 move $t8, $a1
	 li   $t9, 2
	 seq  $t8, $t8, $t9
	 move $a2, $t8
	 move $t8, $a2
	 beq  $t8, $0, $lab30
	 la   $a0, $str7
	 li   $v0, 4
	 syscall
$lab30:
	 li   $v0, 12
	 syscall
	 move $s7, $v0
	 move $t8, $s7
	 li   $t9, 97
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab31
	 li   $a0, 2
	 li   $v0, 1
	 syscall
$lab31:
	 move $t8, $s7
	 li   $t9, 98
	 seq  $t8, $t8, $t9
	 move $a1, $t8
	 move $t8, $a1
	 beq  $t8, $0, $lab32
	 li   $a1, 0
	 move $a0, $a1
	 li   $v0, 1
	 syscall
$lab32:
	 sw   $s0, -8($sp)
	 sw   $s1, -12($sp)
	 sw   $s2, -16($sp)
	 sw   $s3, -20($sp)
	 sw   $s4, -24($sp)
	 sw   $s5, -28($sp)
	 sw   $s6, -32($sp)
	 sw   $s7, -36($sp)
	 move $fp, $sp
	 subi $sp, $sp, 116
	 jal  nest
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
