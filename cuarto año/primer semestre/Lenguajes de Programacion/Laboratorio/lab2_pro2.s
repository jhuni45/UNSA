.data
	valido: .asciiz "Es valido\n"
	novalido: .asciiz "No es valido\n"
.text

main:
	li 		$v0, 5
	syscall
	move 	$t0, $v0
	
	li 		$v0, 5
	syscall
	move 	$t1, $v0
	
	li 		$v0, 5
	syscall
	move 	$t2, $v0
	
	add		$t3, $t0, $t1
	bge 	$t3, $t2, siguiente 	
	j 		novalidoF

siguiente:
	add		$t3, $t0, $t2
	bge 	$t3, $t2, ssiguiente
	j 		novalidoF

ssiguiente:
	add		$t3, $t1, $t2
	bge 	$t3, $t2, validoF 

validoF:
	li 		$v0, 4
	la 		$a0, valido
	syscall
	j 		end

novalidoF:
	li 		$v0, 4
	la 		$a0, novalido
	syscall

end:

	jr 		$ra