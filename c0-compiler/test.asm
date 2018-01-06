.data
cona: .word 10
conb: .word 97
conc: .word 54
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
	 subi $gp, $gp, 0x8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 1
	 sw   $t0, -16($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, 4($gp)
	 sw   $t0, -12($sp)
	 lw   $t0, -8($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffffec
	 sgt  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -20($sp)
	 beq  $t0, $0, $lab0
	 lw   $t0, -8($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffffe8
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $v0, -24($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab0:
	 lw   $t0, -8($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffffe4
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -28($sp)
	 addi $t1, $sp, 0xfffffff8
	 sw   $t0, 0($t1)
	 lw   $t1, -8($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 lw   $t1, -12($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x24
	 jal  f
	 lw   $t0, -8($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xffffffe0
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $v0, -32($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
compare:
	 subi $gp, $gp, 0x8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 1
	 sw   $t0, -20($sp)
	 li   $t0, 95
	 sw   $t0, -32($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, 4($gp)
	 sw   $t0, -12($sp)
	 lw   $t0, -8($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xfffffff0
	 sgt  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -16($sp)
	 beq  $t0, $0, $lab1
	 lw   $v0, -20($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab1:
	 lw   $t0, -8($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xffffffe8
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -24($sp)
	 beq  $t0, $0, $lab2
	 li   $t0, 0
	 lw   $t1, -20($sp)
	 addi $t2, $sp, 0xffffffe4
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $v0, -28($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab2:
	 lw   $v0, -32($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
line:
	 subi $gp, $gp, 0x8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 1
	 sw   $t0, -852($sp)
	 li   $t0, 3
	 sw   $t0, -868($sp)
	 li   $t0, 2
	 sw   $t0, -872($sp)
	 li   $t0, 8
	 sw   $t0, -880($sp)
	 li   $t0, 0
	 sw   $t0, -896($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, 4($gp)
	 sw   $t0, -12($sp)
	 lw   $t0, -852($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
	 lw   $t0, -16($sp)
	 addi $t1, $sp, 0xffffffec
	 sw   $t0, 0($t1)
$lab3:
	 lw   $t0, -16($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffffe8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -16($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xfffffe58
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -16($sp)
	 lw   $t1, -852($sp)
	 addi $t2, $sp, 0xfffffca8
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -856($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
	 lw   $t0, -16($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xfffffca4
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -860($sp)
	 bne  $t0, $0, $lab3
	 lw   $t0, -852($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
$lab4:
	 lw   $t0, -16($sp)
	 lw   $t1, -852($sp)
	 addi $t2, $sp, 0xfffffca0
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -864($sp)
	 beq  $t0, $0, $lab5
	 lw   $t0, -868($sp)
	 addi $t1, $sp, 0xfffffcc8
	 sw   $t0, 0($t1)
	 lw   $t0, -872($sp)
	 addi $t1, $sp, 0xfffffcc4
	 sw   $t0, 0($t1)
$lab5:
	 lw   $t0, -16($sp)
	 lw   $t1, -872($sp)
	 addi $t2, $sp, 0xfffffc94
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -876($sp)
	 beq  $t0, $0, $lab6
	 lw   $t0, -880($sp)
	 addi $t1, $sp, 0xfffffcc8
	 sw   $t0, 0($t1)
	 li   $t0, 0
	 lw   $t1, -868($sp)
	 addi $t2, $sp, 0xfffffc8c
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -884($sp)
	 addi $t1, $sp, 0xfffffcc4
	 sw   $t0, 0($t1)
$lab6:
	 lw   $t0, -16($sp)
	 lw   $t1, -868($sp)
	 addi $t2, $sp, 0xfffffc88
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -888($sp)
	 beq  $t0, $0, $lab7
	 lw   $t0, -868($sp)
	 addi $t1, $sp, 0xfffffcc8
	 sw   $t0, 0($t1)
	 li   $t0, 0
	 lw   $t1, -872($sp)
	 addi $t2, $sp, 0xfffffc84
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -892($sp)
	 addi $t1, $sp, 0xfffffcc4
	 sw   $t0, 0($t1)
$lab7:
	 lw   $t0, -828($sp)
	 lw   $t1, -896($sp)
	 addi $t2, $sp, 0xfffffc7c
	 sne  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -900($sp)
	 beq  $t0, $0, $lab8
	 lw   $t1, -828($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 lw   $t1, -896($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x3c8
	 jal  compare
	 sw   $v0, -904($sp)
	 lw   $t0, -904($sp)
	 addi $t1, $sp, 0xfffffcc0
	 sw   $t0, 0($t1)
	 lw   $t0, -832($sp)
	 lw   $t1, -828($sp)
	 addi $t2, $sp, 0xfffffc74
	 mul  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -908($sp)
	 addi $t1, $sp, 0xfffffcbc
	 sw   $t0, 0($t1)
	 addi $t0, $sp, 0xffffffe8
	 lw   $t1, -824($sp)
	 addi $t3, $sp, 0xfffffc70
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -912($sp)
	 addi $t1, $sp, 0xfffffcb8
	 sw   $t0, 0($t1)
$lab9:
	 lw   $t0, -840($sp)
	 lw   $t1, -832($sp)
	 addi $t2, $sp, 0xfffffc6c
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 addi $t0, $sp, 0xfffffe58
	 lw   $t1, -916($sp)
	 addi $t3, $sp, 0xfffffc68
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -920($sp)
	 addi $t1, $sp, 0xfffffcb0
	 sw   $t0, 0($t1)
	 addi $t0, $sp, 0xffffffe8
	 lw   $t1, -848($sp)
	 addi $t3, $sp, 0xfffffc64
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -848($sp)
	 lw   $t1, -840($sp)
	 addi $t2, $sp, 0xfffffe58
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -840($sp)
	 lw   $t1, -848($sp)
	 addi $t2, $sp, 0xffffffe8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -924($sp)
	 addi $t1, $sp, 0xfffffcb4
	 sw   $t0, 0($t1)
	 lw   $t0, -844($sp)
	 addi $t1, $sp, 0xfffffcb8
	 sw   $t0, 0($t1)
	 lw   $t0, -20($sp)
	 lw   $t1, -852($sp)
	 addi $t2, $sp, 0xfffffc60
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -928($sp)
	 addi $t1, $sp, 0xffffffec
	 sw   $t0, 0($t1)
	 lw   $t0, -20($sp)
	 lw   $t1, -836($sp)
	 addi $t2, $sp, 0xfffffc5c
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -932($sp)
	 bne  $t0, $0, $lab9
	 lw   $t0, -824($sp)
	 lw   $t1, -844($sp)
	 addi $t2, $sp, 0xfffffe58
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffe8
	 lw   $t1, -824($sp)
	 addi $t3, $sp, 0xfffffc58
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -936($sp)
	 lw   $t1, -828($sp)
	 addi $t2, $sp, 0xfffffc54
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -940($sp)
	 lw   $t1, -824($sp)
	 addi $t2, $sp, 0xffffffe8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
$lab8:
	 lw   $t0, -16($sp)
	 lw   $t1, -852($sp)
	 addi $t2, $sp, 0xfffffc50
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -944($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
	 lw   $t0, -16($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xfffffc4c
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -948($sp)
	 bne  $t0, $0, $lab4
	 addi $t0, $sp, 0xfffffe58
	 lw   $t1, -852($sp)
	 addi $t3, $sp, 0xfffffc48
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -952($sp)
	 li   $v0, 1
	 syscall
	 lw   $t0, -872($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
$lab10:
	 addi $t0, $sp, 0xfffffe58
	 lw   $t1, -16($sp)
	 addi $t3, $sp, 0xfffffc44
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -956($sp)
	 li   $v0, 1
	 syscall
	 lw   $t0, -16($sp)
	 lw   $t1, -852($sp)
	 addi $t2, $sp, 0xfffffc40
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -960($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
	 lw   $t0, -16($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xfffffc3c
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -964($sp)
	 bne  $t0, $0, $lab10
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
f2:
	 subi $gp, $gp, 0x4
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 1
	 sw   $t0, -16($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, -16($sp)
	 addi $t1, $sp, 0xfffffff4
	 sw   $t0, 0($t1)
	 lw   $t0, -8($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xffffffec
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -20($sp)
	 addi $t1, $sp, 0xfffffff8
	 sw   $t0, 0($t1)
	 lw   $v0, -8($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
fib:
	 subi $gp, $gp, 0x4
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 0
	 sw   $t0, -16($sp)
	 li   $t0, 1
	 sw   $t0, -24($sp)
	 li   $t0, 2
	 sw   $t0, -40($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, -8($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffffec
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -20($sp)
	 beq  $t0, $0, $lab11
	 lw   $v0, -16($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab11:
	 lw   $t0, -8($sp)
	 lw   $t1, -24($sp)
	 addi $t2, $sp, 0xffffffe4
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -28($sp)
	 beq  $t0, $0, $lab12
	 lw   $v0, -24($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab12:
	 lw   $t0, -8($sp)
	 lw   $t1, -24($sp)
	 addi $t2, $sp, 0xffffffe0
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t1, -32($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x38
	 jal  fib
	 sw   $v0, -36($sp)
	 lw   $t0, -8($sp)
	 lw   $t1, -40($sp)
	 addi $t2, $sp, 0xffffffd4
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t1, -44($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x38
	 jal  fib
	 sw   $v0, -48($sp)
	 lw   $t0, -36($sp)
	 lw   $t1, -48($sp)
	 addi $t2, $sp, 0xffffffcc
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -52($sp)
	 addi $t1, $sp, 0xfffffff4
	 sw   $t0, 0($t1)
	 lw   $v0, -12($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
nest:
	 subi $gp, $gp, 0x0
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 0
	 sw   $t0, -128($sp)
	 li   $t0, 1
	 sw   $t0, -132($sp)
	 li   $t0, 3
	 sw   $t0, -136($sp)
	 li   $t0, 4
	 sw   $t0, -140($sp)
	 li   $t0, 6
	 sw   $t0, -144($sp)
	 li   $t0, 8
	 sw   $t0, -148($sp)
	 li   $t0, 2333
	 sw   $t0, -172($sp)
	 lw   $t0, -132($sp)
	 lw   $t1, -128($sp)
	 addi $t2, $sp, 0xfffffff8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -136($sp)
	 lw   $t1, -132($sp)
	 addi $t2, $sp, 0xffffffbc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -140($sp)
	 lw   $t1, -136($sp)
	 addi $t2, $sp, 0xfffffff8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -148($sp)
	 lw   $t1, -144($sp)
	 addi $t2, $sp, 0xfffffff8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xfffffff8
	 lw   $t1, -128($sp)
	 addi $t3, $sp, 0xffffff68
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -152($sp)
	 addi $t1, $sp, 0xffffff50
	 sw   $t0, 0($t1)
	 lw   $t0, -144($sp)
	 lw   $t1, -140($sp)
	 addi $t2, $sp, 0xffffffbc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffbc
	 lw   $t1, -152($sp)
	 addi $t3, $sp, 0xffffff64
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 addi $t0, $sp, 0xfffffff8
	 lw   $t1, -156($sp)
	 addi $t3, $sp, 0xffffff60
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 addi $t0, $sp, 0xffffffbc
	 lw   $t1, -160($sp)
	 addi $t3, $sp, 0xffffff5c
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 addi $t0, $sp, 0xfffffff8
	 lw   $t1, -164($sp)
	 addi $t3, $sp, 0xffffff58
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -172($sp)
	 lw   $t1, -168($sp)
	 addi $t2, $sp, 0xffffffbc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffbc
	 lw   $t1, -148($sp)
	 addi $t3, $sp, 0xffffff4c
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -152($sp)
	 lw   $t1, -180($sp)
	 addi $t2, $sp, 0xffffff48
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $a0, -184($sp)
	 li   $v0, 1
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
t:
	 subi $gp, $gp, 0x4
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 99
	 sw   $t0, -12($sp)
	 li   $t0, 1
	 sw   $t0, -20($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, -8($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xfffffff0
	 sgt  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -16($sp)
	 beq  $t0, $0, $lab13
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab13:
	 lw   $t0, -8($sp)
	 lw   $t1, -20($sp)
	 addi $t2, $sp, 0xffffffe8
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -24($sp)
	 addi $t1, $sp, 0xfffffff8
	 sw   $t0, 0($t1)
	 lw   $a0, -8($sp)
	 li   $v0, 11
	 syscall
	 lw   $t1, -8($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x1c
	 jal  t
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
main:
	 subi $gp, $gp, 0x0
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 3
	 sw   $t0, -8($sp)
	 li   $t0, 43
	 sw   $t0, -84($sp)
	 li   $t0, 45
	 sw   $t0, -88($sp)
	 li   $t0, 0
	 sw   $t0, -92($sp)
	 li   $t0, 2
	 sw   $t0, -96($sp)
	 li   $t0, 1
	 sw   $t0, -104($sp)
	 li   $t0, 8
	 sw   $t0, -112($sp)
	 li   $t0, 5
	 sw   $t0, -132($sp)
	 li   $t0, 6
	 sw   $t0, -180($sp)
	 li   $t0, 4
	 sw   $t0, -248($sp)
	 li   $t0, 99
	 sw   $t0, -272($sp)
	 li   $t0, -2
	 sw   $t0, -388($sp)
	 lw   $t0, -84($sp)
	 la   $t1, chc
	 sw   $t0, 0($t1)
	 lw   $t0, -88($sp)
	 la   $t1, chd
	 sw   $t0, 0($t1)
	 lw   $t0, -8($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
	 lw   $t0, -92($sp)
	 addi $t1, $sp, 0xffffffe0
	 sw   $t0, 0($t1)
	 li   $t0, 0
	 lw   $t1, -96($sp)
	 addi $t2, $sp, 0xffffff9c
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -100($sp)
	 addi $t1, $sp, 0xffffffec
	 sw   $t0, 0($t1)
	 lw   $t0, -104($sp)
	 addi $t1, $sp, 0xffffffe4
	 sw   $t0, 0($t1)
	 addi $t0, $sp, 0xffffffc8
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 lw   $t0, -56($sp)
	 li   $t1, 0
	 addi $t2, $sp, 0xffffff94
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -108($sp)
	 beq  $t0, $0, $lab14
	 la   $a0, $str0
	 li   $v0, 4
	 syscall
	 lw   $t1, -112($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 lw   $t1, -8($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x18c
	 jal  line
$lab14:
	 lw   $t0, -56($sp)
	 li   $t1, 1
	 addi $t2, $sp, 0xffffff8c
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -116($sp)
	 beq  $t0, $0, $lab15
	 la   $a0, $str1
	 li   $v0, 4
	 syscall
	 lw   $t1, -8($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x18c
	 jal  fib
	 sw   $v0, -120($sp)
	 la   $a0, $str2
	 li   $v0, 4
	 syscall
	 lw   $t0, -120($sp)
	 addi $t1, $sp, 0xffffffe8
	 sw   $t0, 0($t1)
	 lw   $a0, -24($sp)
	 li   $v0, 1
	 syscall
$lab15:
	 lw   $t0, -56($sp)
	 li   $t1, 2
	 addi $t2, $sp, 0xffffff84
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -124($sp)
	 beq  $t0, $0, $lab16
$lab17:
	 la   $t0, conb
	 lw   $t0, 0($t0)
	 lw   $t1, -32($sp)
	 addi $t2, $sp, 0xffffffc4
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -32($sp)
	 lw   $t1, -32($sp)
	 addi $t2, $sp, 0xffffffdc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 lw   $t0, -32($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xffffff80
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -128($sp)
	 addi $t1, $sp, 0xffffffe0
	 sw   $t0, 0($t1)
	 lw   $t0, -32($sp)
	 lw   $t1, -132($sp)
	 addi $t2, $sp, 0xffffff78
	 slt  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -136($sp)
	 bne  $t0, $0, $lab17
	 addi $t0, $sp, 0xffffffe4
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 addi $t0, $sp, 0xfffffff4
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 lw   $t0, -28($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xffffff74
	 slt  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -140($sp)
	 beq  $t0, $0, $lab18
	 lw   $t0, -12($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffff70
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -144($sp)
	 addi $t1, $sp, 0xfffffff4
	 sw   $t0, 0($t1)
	 lw   $a0, -12($sp)
	 li   $v0, 1
	 syscall
$lab18:
	 lw   $t0, -28($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xffffff6c
	 sle  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -148($sp)
	 beq  $t0, $0, $lab19
	 lw   $t0, -16($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xffffff68
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -152($sp)
	 addi $t1, $sp, 0xfffffff0
	 sw   $t0, 0($t1)
	 lw   $a0, -16($sp)
	 li   $v0, 1
	 syscall
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -92($sp)
	 addi $t3, $sp, 0xffffff5c
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -164($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xffffff58
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -168($sp)
	 lw   $t1, -92($sp)
	 addi $t2, $sp, 0xffffffc4
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -92($sp)
	 addi $t3, $sp, 0xffffff54
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -172($sp)
	 li   $v0, 11
	 syscall
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -92($sp)
	 addi $t3, $sp, 0xffffff64
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -156($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffff60
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -160($sp)
	 lw   $t1, -92($sp)
	 addi $t2, $sp, 0xffffffdc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -92($sp)
	 addi $t3, $sp, 0xffffff50
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -176($sp)
	 li   $v0, 1
	 syscall
$lab19:
	 lw   $t0, -28($sp)
	 lw   $t1, -180($sp)
	 addi $t2, $sp, 0xffffff48
	 sgt  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -184($sp)
	 beq  $t0, $0, $lab20
	 lw   $t0, -12($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffff44
	 mul  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -188($sp)
	 addi $t1, $sp, 0xffffffec
	 sw   $t0, 0($t1)
	 lw   $a0, -20($sp)
	 li   $v0, 1
	 syscall
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -104($sp)
	 addi $t3, $sp, 0xffffff38
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -200($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xffffff34
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -204($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xffffffc4
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -104($sp)
	 addi $t3, $sp, 0xffffff30
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -208($sp)
	 li   $v0, 11
	 syscall
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -104($sp)
	 addi $t3, $sp, 0xffffff40
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -192($sp)
	 lw   $t1, -20($sp)
	 addi $t2, $sp, 0xffffff3c
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -196($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xffffffdc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -104($sp)
	 addi $t3, $sp, 0xffffff2c
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -212($sp)
	 li   $v0, 1
	 syscall
$lab20:
	 lw   $t0, -28($sp)
	 lw   $t1, -180($sp)
	 addi $t2, $sp, 0xffffff28
	 sge  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -216($sp)
	 beq  $t0, $0, $lab21
	 lw   $t0, -12($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffff24
	 div  $t0, $t1
	 mflo $t3
	 sw   $t3, 0($t2)
	 lw   $t0, -220($sp)
	 addi $t1, $sp, 0xffffffe8
	 sw   $t0, 0($t1)
	 lw   $a0, -24($sp)
	 li   $v0, 1
	 syscall
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -96($sp)
	 addi $t3, $sp, 0xffffff18
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -232($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xffffff14
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -236($sp)
	 lw   $t1, -96($sp)
	 addi $t2, $sp, 0xffffffc4
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -96($sp)
	 addi $t3, $sp, 0xffffff10
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -240($sp)
	 li   $v0, 11
	 syscall
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -96($sp)
	 addi $t3, $sp, 0xffffff20
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -224($sp)
	 lw   $t1, -24($sp)
	 addi $t2, $sp, 0xffffff1c
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -228($sp)
	 lw   $t1, -96($sp)
	 addi $t2, $sp, 0xffffffdc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -96($sp)
	 addi $t3, $sp, 0xffffff0c
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -244($sp)
	 li   $v0, 1
	 syscall
$lab21:
	 lw   $t0, -28($sp)
	 lw   $t1, -248($sp)
	 addi $t2, $sp, 0xffffff04
	 sne  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -252($sp)
	 beq  $t0, $0, $lab22
	 lw   $t0, -104($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xffffff00
	 div  $t0, $t1
	 mflo $t3
	 sw   $t3, 0($t2)
	 lw   $t0, -12($sp)
	 lw   $t1, -256($sp)
	 addi $t2, $sp, 0xfffffefc
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -260($sp)
	 addi $t1, $sp, 0xfffffff4
	 sw   $t0, 0($t1)
	 lw   $a0, -12($sp)
	 li   $v0, 1
	 syscall
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -8($sp)
	 addi $t3, $sp, 0xfffffee8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -280($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xfffffee4
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -284($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xffffffc4
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -8($sp)
	 addi $t3, $sp, 0xfffffee0
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -288($sp)
	 li   $v0, 11
	 syscall
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -8($sp)
	 addi $t3, $sp, 0xfffffef8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -264($sp)
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xfffffef4
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -268($sp)
	 lw   $t1, -272($sp)
	 addi $t2, $sp, 0xfffffeec
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -276($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xffffffdc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -8($sp)
	 addi $t3, $sp, 0xfffffedc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -292($sp)
	 li   $v0, 1
	 syscall
$lab22:
	 lw   $t0, -28($sp)
	 lw   $t1, -248($sp)
	 addi $t2, $sp, 0xfffffed8
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -296($sp)
	 beq  $t0, $0, $lab23
	 lw   $t0, -96($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xfffffed0
	 mul  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 li   $t0, 0
	 lw   $t1, -12($sp)
	 addi $t2, $sp, 0xfffffed4
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -300($sp)
	 lw   $t1, -304($sp)
	 addi $t2, $sp, 0xfffffecc
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -308($sp)
	 addi $t1, $sp, 0xfffffff4
	 sw   $t0, 0($t1)
	 lw   $a0, -12($sp)
	 li   $v0, 1
	 syscall
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -248($sp)
	 addi $t3, $sp, 0xfffffec8
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $t0, -312($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xfffffec4
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -316($sp)
	 lw   $t1, -248($sp)
	 addi $t2, $sp, 0xffffffc4
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
	 addi $t0, $sp, 0xffffffc4
	 lw   $t1, -248($sp)
	 addi $t3, $sp, 0xfffffec0
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -320($sp)
	 li   $v0, 11
	 syscall
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -248($sp)
	 addi $t3, $sp, 0xfffffebc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -324($sp)
	 li   $v0, 1
	 syscall
$lab23:
	 lw   $t0, -28($sp)
	 beq  $t0, $0, $lab24
	 lw   $a0, -12($sp)
	 li   $v0, 1
	 syscall
$lab24:
$lab16:
	 lw   $t0, -56($sp)
	 li   $t1, 3
	 addi $t2, $sp, 0xfffffeb8
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -328($sp)
	 beq  $t0, $0, $lab25
	 la   $a0, $str3
	 li   $v0, 4
	 syscall
	 lw   $t0, -28($sp)
	 beq  $t0, $0, $lab26
	 li   $t0, 0
	 lw   $t1, -96($sp)
	 addi $t2, $sp, 0xfffffeb4
	 sub  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t1, -332($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 lw   $t1, -8($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x18c
	 jal  f
	 sw   $v0, -336($sp)
	 lw   $t0, -132($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xfffffeac
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -340($sp)
	 lw   $t1, -8($sp)
	 addi $t2, $sp, 0xfffffea8
	 mul  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -336($sp)
	 lw   $t1, -344($sp)
	 addi $t2, $sp, 0xfffffea4
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -348($sp)
	 lw   $t1, -248($sp)
	 addi $t2, $sp, 0xffffffdc
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t2, $t2, $t1
	 sw   $t0, 0($t2)
$lab26:
	 la   $t0, conb
	 lw   $t1, 0($t0)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x18c
	 jal  t
	 la   $t0, conb
	 lw   $t1, 0($t0)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x18c
	 jal  f2
	 sw   $v0, -352($sp)
	 lw   $a0, -352($sp)
	 li   $v0, 11
	 syscall
	 addi $t0, $sp, 0xffffffdc
	 lw   $t1, -248($sp)
	 addi $t3, $sp, 0xfffffe9c
	 li   $at, 4
	 mul  $t1, $t1, $at
	 sub  $t0, $t0, $t1
	 lw   $t2, 0($t0)
	 sw   $t2, 0($t3)
	 lw   $a0, -356($sp)
	 li   $v0, 1
	 syscall
$lab25:
	 lw   $t0, -56($sp)
	 li   $t1, 4
	 addi $t2, $sp, 0xfffffe98
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -360($sp)
	 beq  $t0, $0, $lab27
	 la   $a0, $str4
	 li   $v0, 4
	 syscall
	 addi $t0, $sp, 0xffffffe4
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 lw   $t0, -28($sp)
	 lw   $t1, -104($sp)
	 addi $t2, $sp, 0xfffffe94
	 mul  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -364($sp)
	 li   $t1, 0
	 addi $t2, $sp, 0xfffffe90
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -368($sp)
	 beq  $t0, $0, $lab28
	 la   $a0, $str5
	 li   $v0, 4
	 syscall
$lab28:
	 lw   $t0, -364($sp)
	 li   $t1, 1
	 addi $t2, $sp, 0xfffffe8c
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -372($sp)
	 beq  $t0, $0, $lab29
	 la   $a0, $str6
	 li   $v0, 4
	 syscall
	 lw   $a0, -28($sp)
	 li   $v0, 1
	 syscall
$lab29:
	 lw   $t0, -364($sp)
	 li   $t1, 2
	 addi $t2, $sp, 0xfffffe88
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -376($sp)
	 beq  $t0, $0, $lab30
	 la   $a0, $str7
	 li   $v0, 4
	 syscall
$lab30:
	 addi $t0, $sp, 0xffffffb0
	 li   $v0, 12
	 syscall
	 sw   $v0, 0($t0)
	 lw   $t0, -80($sp)
	 li   $t1, 97
	 addi $t2, $sp, 0xfffffe84
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -380($sp)
	 beq  $t0, $0, $lab31
	 lw   $a0, -96($sp)
	 li   $v0, 1
	 syscall
$lab31:
	 lw   $t0, -80($sp)
	 li   $t1, 98
	 addi $t2, $sp, 0xfffffe80
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -384($sp)
	 beq  $t0, $0, $lab32
	 lw   $t0, -96($sp)
	 lw   $t1, -388($sp)
	 addi $t2, $sp, 0xfffffe78
	 add  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $a0, -392($sp)
	 li   $v0, 1
	 syscall
$lab32:
$lab27:
	 move $fp, $sp
	 subi $sp, $sp, 0x18c
	 jal  nest
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
