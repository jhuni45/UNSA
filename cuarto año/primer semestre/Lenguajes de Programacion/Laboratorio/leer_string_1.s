.data
	buffer: .space 20 #"buffer" es un vector con espacio (.space) de 20
.text

main:

	li $a1, 10		#maximo numero de caracteres a leer
	li $v0, 8			#para leer un string
	la $a0, buffer
	syscall
	
	li $v0, 4			#para mostrar un string
	syscall
	
	jr $ra