.data
	ingreso :.asciiz "\nIngrese el numero\n"
	mayor : .asciiz "El numero es mayor o igual a 10\n"
	menor : .asciiz "El numero es menor a 10\n"
.text

main:
	li		$v0, 4
	la		$a0, ingreso
	syscall
	li 		$v0, 5
	syscall
	move 	$t0, $v0
	#comparaciones
	bgt 	$t0, 10, mayorF
	blt 	$t0, 10, menorF

mayorF:
	li		$v0, 4
	la		$a0, mayor
	syscall
	j 		end

menorF:
	li		$v0, 4
	la		$a0, menor
	syscall

end:
	jr $ra