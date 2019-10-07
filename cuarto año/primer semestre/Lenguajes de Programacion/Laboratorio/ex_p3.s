.data
	result: .asciiz "La division entre 4 es: "
	entry: .asciiz "Ingrese un valor: "
.text

main:
	li 		$v0, 4
	la 		$a0, entry
	syscall
	li 		$v0, 5
	syscall
	move 	$t0, $v0
	ror 	$t1, $t0, 2

	li 		$v0, 4
	la 		$a0, result
	syscall
	li 		$v0, 1
	move	$a0, $t1
	syscall


end:
jr 		$ra
