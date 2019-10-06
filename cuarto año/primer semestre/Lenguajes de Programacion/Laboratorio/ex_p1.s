#leer  
.data
	mayor: .asciiz "Mayor: "
	Atext: .asciiz "Ingresa valor A: "
	Btext: .asciiz "Ingresa valor B: " 
.text

main:
	li 		$v0, 4
	la 		$a0, Atext
	syscall
	li 		$v0, 5
	syscall
	move	$t0, $v0
	li 		$v0, 4
	la 		$a0, Btext
	syscall
	li 		$v0, 5
	syscall
	move 	$t1, $v0
	blt 	$t0,  $t1, primero
	li 		$v0, 4 
	la 		$a0, mayor
	syscall
	li 		$v0, 1
	move	$a0, $t0
	syscall
	j 		end


primero:
	li 		$v0, 4 
	la 		$a0, mayor
	syscall
	li 		$v0, 1
	move	$a0, $t1
	syscall

end:
jr 		$ra