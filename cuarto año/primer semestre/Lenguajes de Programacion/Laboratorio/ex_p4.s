.data
	sucesion : .asciiz "Sucesion: "
	space: .asciiz " "
	entry: .asciiz "Ingrese un valor: "
.text

main:
	li 		$v0, 4
	la 		$a0, entry
	syscall
	
	li 		$v0, 5
	syscall

	move 	$t0, $v0
	li 		$v0, 4
	la 		$a0, sucesion
	syscall
	j 		loop
loop:
	li 		$v0, 1
	move 	$a0, $t0
	syscall
	li 		$v0, 4
	la 		$a0, space
	syscall

	beq 	$t0, 1, end
	div 	$t1, $t0, 2
	mfhi 	$t2
	beq 	$t2, 0, par
	beq 	$t2, 1, impar
	li 		$v0, 1
	move	$a0, $t2
	syscall
	
par:
	div 	$t0, $t0, 2
	j 		loop
impar:
	mul 	$t0, $t0, 3
	add 	$t0, $t0, 1
	j 		loop

end:
	jr 		$ra
