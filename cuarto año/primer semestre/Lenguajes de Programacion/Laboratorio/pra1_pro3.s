#Implementar un programa que lea 
#un número retorne si es primo o no

.data
	primo : .asciiz "Es Primo\n"
	noprimo : .asciiz "No es Primo\n"  
.text

main:
	li		$v0, 5
	syscall
	move 	$t0, $v0

	li.s		$t1, 1.0
	li.s		$t4, 0.0
	beq $t1, $t0, bucle
	jr primoF

bucle:
	div.s $t0, $t1
	mfhi $t2
	mflo $t3
	bgt  $t3, 0, noprimoF
	add.s  $t1, $t1, 1.0

	j 		bucle

primoF:
	li 	$v0, 4
	la 	$a0, primo
	syscall
	j 		end

noprimoF:
	li 	$v0, 4
	la 	$a0, noprimo
	syscall

end:	
	jr $ra