#edad de una persona dado la fecha de su nacimiento
.data
	edad: .asciiz "Tu edad es: "
.text

main:
	li 		$v0, 5
	syscall
	li 		$t1, 2019
	move 	$t0, $v0
	sub 	$t1, $t1, $t0
	li 		$v0, 4
	la		$a0, edad
	syscall
	move	$a0, $t1
	li 		$v0, 1
	syscall
end:

jr  	$ra