.data
num1: .word 0
.text
	 jal  main
	 li   $v0, 10
	 syscall
mod:
	 subi $gp, $gp, 0x8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, 4($gp)
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
	 subi $gp, $gp, 0x8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 li   $t0, 0
	 sw   $t0, -16($sp)
	 lw   $t0, 0($gp)
	 sw   $t0, -8($sp)
	 lw   $t0, 4($gp)
	 sw   $t0, -12($sp)
	 lw   $t0, -12($sp)
	 lw   $t1, -16($sp)
	 addi $t2, $sp, 0xffffffec
	 seq  $t3, $t0, $t1
	 sw   $t3, 0($t2)
	 lw   $t0, -20($sp)
	 beq  $t0, $0, $lab0
	 lw   $v0, -8($sp)
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
$lab0:
	 lw   $t1, -12($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 lw   $t1, -8($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 lw   $t1, -12($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x20
	 jal  mod
	 sw   $v0, -24($sp)
	 lw   $t1, -24($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x20
	 jal  gcd
	 sw   $v0, -28($sp)
	 lw   $v0, -28($sp)
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
	 la   $t0, num1
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 addi $t0, $sp, 0xfffffff8
	 li   $v0, 5
	 syscall
	 sw   $v0, 0($t0)
	 la   $t0, num1
	 lw   $t1, 0($t0)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 lw   $t1, -8($sp)
	 sw   $t1, 0($gp)
	 addi $gp, $gp, 0x4
	 move $fp, $sp
	 subi $sp, $sp, 0x10
	 jal  gcd
	 sw   $v0, -12($sp)
	 lw   $a0, -12($sp)
	 li   $v0, 1
	 syscall
	 lw   $ra, -4($sp)
	 lw   $sp, 0($sp)
	 jr   $ra
