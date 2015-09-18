  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	addi $t7,$zero,-1
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall	
	nop	
	# wait a little
	li	$a0,1000 #ms to wait
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #

hexasc:	
	sll $a0,$a0,28		# Remove everything but LSN (last 4 bits)
	srl $a0,$a0,28
	
	sltiu $t0,$a0,10	# $t0 = $a0<10
	
	bne $t0,1,letters	# if $t0 != 1 jump (A-F)
	nop
	addiu $v0,$a0,0x30 	#$v0 = $a0+0x30
	
	jr $ra			# done here, return
	nop
letters:
	addiu $v0,$a0,0x37	#10-15 -> 'A'-'F'
	
	jr $ra			# done here, return
	nop
	
delay:
	ble $a0,$zero,return #return if $a0 <= 0 	###
	nop 						##
	addi $a0,$a0,-1					##
	add $t0,$zero,$zero # $t0 = 0			##
	loop:						##
		beq $t0,100,delay			#*176# 352
		nop					#*175# 350
		addi $t0,$t0,1				#*175#	.
		j loop					#*175#	.
		nop					#*175# 350

return:
	jr $ra						#
	nop						#
	
time2string:
	# a0 output, a1 16 LSB that represents current time.
	PUSH $ra #store to be able to go deeper
	move $t3,$a0
	
	#andra sekund
	move $a0,$a1 	#a0 = a1
	jal hexasc	#take last 4 bits and convert to number
	nop
	move $t1, $v0	#$t0[4] = $v0
	
	
	srl $a0,$a1,4 #första sekund
	jal hexasc
	nop
	move $t2,$v0
	sll $t2,$t2,8

	
	#add colon 0x3A
	addi $t2,$t2,0x3A
	sll $t2,$t2,8
	
	srl $a0,$a1,8 #andra minut
	jal hexasc
	nop
	add $t2,$v0,$t2 # t0+=v0
	sll $t2,$t2,8
	
	srl $a0,$a1,12 #första minut
	jal hexasc
	nop
	add $t2,$v0,$t2 # t0+=v0
	
	#addi $t3,$t3,1	
	sw $t2,($t3)
	sw $t1,4($t3)
	#write minutes
	#write second
	#0x00 
	POP $ra
	jr $ra
	nop
