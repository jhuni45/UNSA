# Implementar un programa que lea un número, 
# y después me indique si es par o impar.

.data
	par : .asciiz "Es Par\n"
	impar : .asciiz "Es Impar\n"  
.text

main:
	li 		$v0, 5
	syscall
	move 	$t0, $v0
	div 	$t1, $t0, 2
	mfhi	$t2
	
	beq 	$t2, 0, parF

imparF:
	li		$v0, 4
	la 		$a0, impar 
	syscall
	j 		end

parF:
	li		$v0, 4
	la 		$a0, par 
	syscall
#	j 		end


end:	
	jr $ra