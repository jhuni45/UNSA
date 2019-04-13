.data
	primo : .asciiz "Es Primo\n"
	noprimo : .asciiz "No es Primo\n"  
.text

main:
	li  	$v0, 5
	syscall
	move 	$a0, $v0
	move 	$t5 , $ra
	li 		$t1, 2
	li 		$t3, 1
loop:
	div 	$a0, $t1
	mfhi 	$t2 
	beq 	$t1, $a0, primoF
	beqz 	$t2, noPrimoF
	add 	$t1, $t1, $t3
	j loop

primoF:
	li 		$v0, 4 
	la 		$a0, primo
	syscall
	jr		 $t5

noPrimoF:
	li 		$v0, 4 
	la 		$a0, noprimo
	syscall
	jr 		$t5