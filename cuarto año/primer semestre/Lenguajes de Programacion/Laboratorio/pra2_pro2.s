.data
.text

main:
	li 		$v0, 5
	syscall
	move 	$t0, $v0
	
	li 		$v0, 5
	syscall
	move 	$t1, $v0
	

	mtc1	$t0, $f0
	mtc1	$t1, $f1
	div.s 	$f12, $f0, $f1

	li 		$v0, 2
	syscall

end:
	jr 		$ra