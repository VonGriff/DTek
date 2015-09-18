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


.global hexasc:	
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
	
.global delay:
	ble $a0,$zero,returnDelay #return if $a0 <= 0 	###
	nop 						##
	addi $a0,$a0,-1					##
	add $t0,$zero,$zero # $t0 = 0			##
	loop:						##
		beq $t0,175,delay			#*176# 352
		nop					#*175# 350
		addi $t0,$t0,1				#*175#	.
		j loop					#*175#	.
		nop					#*175# 350

returnDelay:
	jr $ra						#
	nop						#
	
.global time2string:
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