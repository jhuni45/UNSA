.data

.text

main:
	li 		$v0, 5
	syscall
	
	move 	$t0, $v0
	li 		$t1, 1
	li 		$t2, 1
	li 		$t4, 2
	j 		loop

loop:
	blt 	$t4, $t0, end		 
	move 	$t3, $t2

	li 		$v0, 1
	move 	$a0, $t1
	syscall
	add 	$t2, $t2, $t1
	move	$t1, $t3
	add 	$t4, $t4, 1
	j 		loop


end:
	jr 		$ra