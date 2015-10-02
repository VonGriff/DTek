  # labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2015-2016.
  # The macros PUSH and POP are in the public domain.

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  # You can add your own code here
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

.global delay	
delay:
	ble $a0,$zero,return #return if $a0 <= 0 	###
	nop 						##
	addi $a0,$a0,-1					##
	add $t0,$zero,$zero # $t0 = 0			##
	loop:						##
		beq $t0,11500,delay			#*176# 352
		nop					#*175# 350
		addi $t0,$t0,1				#*175#	.
		j loop					#*175#	.
		nop					#*175# 350

return:
	jr $ra						#
	nop						#

.global time2string
time2string:
	# a0 output, a1 16 LSB that represents current time.
	PUSH $ra #store to be able to go deeper
	PUSH $s0
	PUSH $s1
	PUSH $s2
	move $s0,$a0
	
	#andra sekund
	move $a0,$a1 	#a0 = a1
	jal hexasc	#take last 4 bits and convert to number
	nop
	move $s2, $v0	#$t0[4] = $v0
	
	srl $a0,$a1,4 #f�rsta sekund
	jal hexasc
	nop
	move $s1,$v0
	sll $s1,$s1,8
	
	#add colon 0x3A
	addi $s1,$s1,0x3A
	sll $s1,$s1,8
	
	srl $a0,$a1,8 #andra minut
	jal hexasc
	nop
	add $s1,$v0,$s1 # t0+=v0
	sll $s1,$s1,8
	
	srl $a0,$a1,12 #forsta minut
	jal hexasc
	nop
	add $s1,$v0,$s1 # t0+=v0
	
	bne $s2,0x00000032,WRITE
	nop
	
	li $s2,0x004F5754 #t1 = \0 O W T 
	
WRITE:	
	sw $s1,($s0)
	sw $s2,4($s0)
	#write minutes
	#write second
	#0x00 
	POP $s2
	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop

.global enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop
