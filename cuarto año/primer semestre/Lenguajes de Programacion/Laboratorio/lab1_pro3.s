.data
.text

main:
	li 		$v0,5
	syscall
	move 	$t0, $v0
		
	li 		$v0, 5
	syscall
	move 	$t1, $v0
	add 	$t2, $t0, $t1 #sumamos
	
	div  	$t3, $t2, 2
	move 	$a0, $t3
	li 		$v0, 1
	syscall

	jr 		$ra