.data
	print: .asciiz "Promedio:"
.text

main:
	li 		$v0, 5
	syscall
	move 	$t0, $v0
	move	$t4, $t0
	li		$t1, 0
	j 		loop
loop:
	beq		$t0, 0, end
	li		$v0, 5
	syscall
	move 	$t2, $v0
	add		$t1, $t1, $t2
	add		$t0, $t0, -1
	j 		loop

end:
	li		$v0, 4
	la		$a0, print
	syscall
	div 	$t1, $t4 
	mflo 	$a0
	li	 	$v0, 1

	syscall
	
	jr 		$ra