.data
	primo : .asciiz "Es Primo\n"  
.text

main:
	li  	$v0, 5
	syscall
	#move 	$t5 , $ra
	move 	$t5, $v0
	li 		$t1, 2
	li 		$t3, 1

	li 		$t4, 2
	move 	$a0, $t4
	li 		$t6, 0
	
loop:
	beq 	$t6, $t5, end
	div 	$a0, $t1
	
	mfhi 	$t2 
	beq 	$t1, $a0, primoF
	beqz 	$t2, noPrimoF
	add 	$t1, $t1, $t3
		
	j  		loop

primoF:
	li 		$v0, 1
	#la 		$a0, primo
	syscall
	add 	$t6, $t6, 1
	add		$a0, $a0, 1
	li 		$t1, 2
	li 		$t3, 1
	#move 	$a0, $t4
	#jr		 $t5
	j 		loop

noPrimoF:
	li 		$v0, 4 
	#la 		$a0, noprimo
	#syscall
	add		$a0, $a0, 1
	li 		$t1, 2
	li 		$t3, 1
	#move	$a0, $t4
	j 		loop
	
end: 
	jr 		$ra