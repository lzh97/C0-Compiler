.data
a: .word 0
b: .word 0
c: .word 0
d: .word 0
.text
	 jal  main
	 li   $v0, 10
	 syscall
add:
	 subi $gp, $gp, 8
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 lw   $s0, 0($gp)
	 lw   $s1, 4($gp)
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
main:
	 sw   $fp, 0($sp)
	 sw   $ra, -4($sp)
	 la   $t8, a
	 lw   $t8, 0($t8)
	 la   $t9, b
	 lw   $t9, 0($t9)
	 add  $t8, $t8, $t9
	 sw   $t8, -40($sp)
	 lw   $t8, -40($sp)
	 la   $t9, c
	 sw   $t8, 0($t9)
	 li   $t8, 2
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
	 subi $sp, $sp, 52
	 jal  add
	 move $a1, $v0
	 lw   $t8, -40($sp)
	 move $t9, $a1
	 add  $t8, $t8, $t9
	 la   $t9, d
	 sw   $t8, 0($t9)
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
