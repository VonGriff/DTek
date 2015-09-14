  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,10		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
  
hexasc:	
	sll $a0,$a0,28		# Remove everything but LSN (last 4 bits)
	srl $a0,$a0,28
	
	sltiu $t0,$a0,10	# $t0 = $a0<10
	
	bne $t0,1,letters	# if $t0 != 1 jump (A-F)
	
	addiu $v0,$a0,0x30 	#$v0 = $a0+0x30
	
	jr $ra			# done here, return
letters:
	addiu $v0,$a0,0x37	#10-15 -> 'A'-'F'
	
	jr $ra			# done here, return

