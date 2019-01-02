.data
str1: .asciiz "2 <= 1"
str2: .asciiz "1 == 2"
str3: .asciiz "1 - 1 = true"
str4: .asciiz " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
str5: .asciiz "int_test_input = "
str6: .asciiz "char_test_input = "
.text
li $t9 268501152
move $fp $sp
addiu $sp $fp -0
la $ra label105
j main
label1:
li $t0 0
sw $t0 -0($sp)
lw $t1 -0($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t0 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t0 98
sw $t0 -8($sp)
lw $t1 -8($sp)
lw $t1 -8($sp)
addiu $t0 $t1 1
sw $t0 -12($sp)
li $t0 97
sw $t0 -16($sp)
lw $t1 -16($sp)
lw $t1 -16($sp)
addiu $t0 $t1 1
sw $t0 -20($sp)
lw $t0 -12($sp)
lw $t1 -20($sp)
ble $t0 $t1 label2
label3:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -24($sp)
li $t0 100
sw $t0 -28($sp)
lw $t0 -24($sp)
lw $t1 -28($sp)
bge $t0 $t1 label4
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -32($sp)
lw $t1 -32($sp)
lw $t2 -4($fp)
addu $t0 $t1 $t2
sw $t0 -36($sp)
lw $t1 -36($sp)
move $t0 $t1
sw $t0 -0($fp)
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -40($sp)
lw $t1 -40($sp)
lw $t1 -40($sp)
addiu $t0 $t1 1
sw $t0 -44($sp)
lw $t1 -44($sp)
move $t0 $t1
sw $t0 -4($fp)
j label3
label4:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -48($sp)
lw $t1 -48($sp)
li $t2 100
subu $t0 $t1 $t2
sw $t0 -52($sp)
lw $t1 -52($sp)
li $t2 3
mul $t0 $t1 $t2
sw $t0 -56($sp)
lw $t1 -56($sp)
addiu $t0 $t1 0
sw $t0 -60($sp)
lw $t0 -60($sp)
li $t1 15
bne $t0 $t1 label6
lw $t1 -0($fp)
li $t2 10
mul $t0 $t1 $t2
sw $t0 -64($sp)
li $t1 0
lw $t2 -64($sp)
subu $t0 $t1 $t2
sw $t0 -68($sp)
li $t1 2
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -72($sp)
lw $t1 -68($sp)
lw $t2 -72($sp)
addu $t0 $t1 $t2
sw $t0 -76($sp)
lw $t1 -76($sp)
lw $t1 -76($sp)
addiu $t0 $t1 117
sw $t0 -80($sp)
lw $t1 -80($sp)
li $t2 98
subu $t0 $t1 $t2
sw $t0 -84($sp)
lw $t1 -84($sp)
move $t0 $t1
sw $t0 -0($fp)
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -88($sp)
lw $t1 -88($sp)
lw $t2 -0($fp)
subu $t0 $t1 $t2
sw $t0 -92($sp)
li $t1 10
li $t2 97
mul $t0 $t1 $t2
sw $t0 -96($sp)
lw $t1 -92($sp)
lw $t2 -96($sp)
addu $t0 $t1 $t2
sw $t0 -100($sp)
lw $t1 -100($sp)
li $t2 100
subu $t0 $t1 $t2
sw $t0 -104($sp)
lw $t1 -104($sp)
lw $t1 -104($sp)
addiu $t0 $t1 42
sw $t0 -108($sp)
lw $t1 -108($sp)
lw $t1 -108($sp)
addiu $t0 $t1 34
sw $t0 -112($sp)
li $t1 2
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -116($sp)
lw $t1 -112($sp)
lw $t2 -116($sp)
addu $t0 $t1 $t2
sw $t0 -120($sp)
lw $t1 -120($sp)
move $t0 $t1
sw $t0 -4($fp)
j label5
label6:
lw $t1 -0($fp)
li $t2 4
mul $t0 $t1 $t2
sw $t0 -124($sp)
lw $t1 -124($sp)
addiu $t0 $t1 0
sw $t0 -128($sp)
li $t1 5
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -132($sp)
lw $t1 -128($sp)
lw $t2 -132($sp)
addu $t0 $t1 $t2
sw $t0 -136($sp)
lw $t1 -136($sp)
lw $t1 -136($sp)
addiu $t0 $t1 24
sw $t0 -140($sp)
lw $t1 -140($sp)
li $t2 97
subu $t0 $t1 $t2
sw $t0 -144($sp)
lw $t1 -144($sp)
lw $t1 -144($sp)
addiu $t0 $t1 99
sw $t0 -148($sp)
lw $t1 -148($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 0
lw $t2 -4($fp)
subu $t0 $t1 $t2
sw $t0 -152($sp)
lw $t1 -152($sp)
lw $t2 -0($fp)
addu $t0 $t1 $t2
sw $t0 -156($sp)
li $t1 4
li $t2 97
mul $t0 $t1 $t2
sw $t0 -160($sp)
lw $t1 -156($sp)
lw $t2 -160($sp)
addu $t0 $t1 $t2
sw $t0 -164($sp)
lw $t1 -164($sp)
li $t2 1653
subu $t0 $t1 $t2
sw $t0 -168($sp)
lw $t1 -168($sp)
lw $t1 -168($sp)
addiu $t0 $t1 453
sw $t0 -172($sp)
lw $t1 -172($sp)
lw $t1 -172($sp)
addiu $t0 $t1 555
sw $t0 -176($sp)
li $t1 4
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -180($sp)
lw $t1 -176($sp)
lw $t2 -180($sp)
subu $t0 $t1 $t2
sw $t0 -184($sp)
lw $t1 -184($sp)
move $t0 $t1
sw $t0 -4($fp)
label5:
label2:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -188($sp)
lw $t1 -188($sp)
move $t0 $t1
sw $t0 -192($sp)
lw $s1 -192($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -196($sp)
lw $t1 -196($sp)
move $t0 $t1
sw $t0 -200($sp)
lw $s1 -200($sp)
li $v0 1
move $a0 $s1
syscall
li $t0 0
sw $t0 -204($sp)
lw $t1 -204($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t0 0
sw $t0 -208($sp)
lw $t1 -208($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t0 98
sw $t0 -212($sp)
lw $t1 -212($sp)
lw $t1 -212($sp)
addiu $t0 $t1 1
sw $t0 -216($sp)
li $t0 97
sw $t0 -220($sp)
lw $t1 -220($sp)
lw $t1 -220($sp)
addiu $t0 $t1 1
sw $t0 -224($sp)
lw $t0 -216($sp)
lw $t1 -224($sp)
blt $t0 $t1 label7
label8:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -228($sp)
li $t0 10
sw $t0 -232($sp)
lw $t0 -228($sp)
lw $t1 -232($sp)
bge $t0 $t1 label9
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -236($sp)
li $t0 2
sw $t0 -240($sp)
lw $t0 -236($sp)
lw $t1 -240($sp)
ble $t0 $t1 label10
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -244($sp)
lw $t1 -244($sp)
lw $t2 -4($fp)
addu $t0 $t1 $t2
sw $t0 -248($sp)
lw $t1 -248($sp)
move $t0 $t1
sw $t0 -0($fp)
label10:
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -252($sp)
lw $t1 -252($sp)
lw $t1 -252($sp)
addiu $t0 $t1 1
sw $t0 -256($sp)
lw $t1 -256($sp)
move $t0 $t1
sw $t0 -4($fp)
lw $t1 -0($fp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -260($sp)
lw $t1 -260($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -264($sp)
lw $t1 -264($sp)
addiu $t0 $t1 0
sw $t0 -268($sp)
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -272($sp)
lw $t0 -268($sp)
lw $t1 -272($sp)
bne $t0 $t1 label11
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -276($sp)
lw $t1 -276($sp)
lw $t1 -276($sp)
addiu $t0 $t1 1
sw $t0 -280($sp)
lw $t1 -280($sp)
move $t0 $t1
sw $t0 -4($fp)
label11:
j label8
label9:
label7:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -284($sp)
lw $t1 -284($sp)
move $t0 $t1
sw $t0 -288($sp)
lw $s1 -288($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -292($sp)
lw $t1 -292($sp)
move $t0 $t1
sw $t0 -296($sp)
lw $s1 -296($sp)
li $v0 1
move $a0 $s1
syscall
li $t0 0
sw $t0 -300($sp)
lw $t1 -300($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t0 0
sw $t0 -304($sp)
lw $t1 -304($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t0 1
sw $t0 -308($sp)
li $t0 2
sw $t0 -312($sp)
lw $t0 -308($sp)
lw $t1 -312($sp)
bge $t0 $t1 label12
label13:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -316($sp)
li $t0 20
sw $t0 -320($sp)
lw $t0 -316($sp)
lw $t1 -320($sp)
bge $t0 $t1 label14
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -324($sp)
lw $t1 -0($fp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -328($sp)
lw $t1 -328($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -332($sp)
lw $t1 -324($sp)
lw $t2 -332($sp)
subu $t0 $t1 $t2
sw $t0 -336($sp)
lw $t0 -336($sp)
li $t1 0
bne $t0 $t1 label16
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -340($sp)
lw $t1 -340($sp)
lw $t1 -340($sp)
addiu $t0 $t1 1
sw $t0 -344($sp)
lw $t1 -344($sp)
move $t0 $t1
sw $t0 -0($fp)
j label15
label16:
lw $t0 -336($sp)
li $t1 1
bne $t0 $t1 label17
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -348($sp)
lw $t1 -348($sp)
lw $t2 -4($fp)
addu $t0 $t1 $t2
sw $t0 -352($sp)
lw $t1 -352($sp)
move $t0 $t1
sw $t0 -0($fp)
j label15
label17:
label15:
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -356($sp)
lw $t1 -356($sp)
lw $t1 -356($sp)
addiu $t0 $t1 1
sw $t0 -360($sp)
lw $t1 -360($sp)
move $t0 $t1
sw $t0 -4($fp)
j label13
label14:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -364($sp)
lw $t1 -0($fp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -368($sp)
lw $t1 -368($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -372($sp)
lw $t1 -372($sp)
addiu $t0 $t1 0
sw $t0 -376($sp)
lw $t0 -364($sp)
lw $t1 -376($sp)
bne $t0 $t1 label18
lw $t1 -0($fp)
li $t2 7
mul $t0 $t1 $t2
sw $t0 -380($sp)
lw $t1 -380($sp)
addiu $t0 $t1 0
sw $t0 -384($sp)
li $t1 2
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -388($sp)
lw $t1 -384($sp)
lw $t2 -388($sp)
addu $t0 $t1 $t2
sw $t0 -392($sp)
lw $t1 -392($sp)
lw $t1 -392($sp)
addiu $t0 $t1 99
sw $t0 -396($sp)
lw $t1 -396($sp)
li $t2 97
subu $t0 $t1 $t2
sw $t0 -400($sp)
lw $t1 -400($sp)
lw $t1 -400($sp)
addiu $t0 $t1 103
sw $t0 -404($sp)
lw $t1 -404($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 0
lw $t2 -4($fp)
subu $t0 $t1 $t2
sw $t0 -408($sp)
lw $t1 -408($sp)
lw $t2 -0($fp)
addu $t0 $t1 $t2
sw $t0 -412($sp)
li $t1 2
li $t2 97
mul $t0 $t1 $t2
sw $t0 -416($sp)
lw $t1 -412($sp)
lw $t2 -416($sp)
addu $t0 $t1 $t2
sw $t0 -420($sp)
lw $t1 -420($sp)
li $t2 523
subu $t0 $t1 $t2
sw $t0 -424($sp)
lw $t1 -424($sp)
lw $t1 -424($sp)
addiu $t0 $t1 53
sw $t0 -428($sp)
lw $t1 -428($sp)
lw $t1 -428($sp)
addiu $t0 $t1 355
sw $t0 -432($sp)
li $t1 2
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -436($sp)
lw $t1 -432($sp)
lw $t2 -436($sp)
subu $t0 $t1 $t2
sw $t0 -440($sp)
lw $t1 -440($sp)
move $t0 $t1
sw $t0 -4($fp)
label18:
label12:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -444($sp)
lw $t1 -444($sp)
move $t0 $t1
sw $t0 -448($sp)
lw $s1 -448($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -452($sp)
lw $t1 -452($sp)
move $t0 $t1
sw $t0 -456($sp)
lw $s1 -456($sp)
li $v0 1
move $a0 $s1
syscall
li $t0 2
sw $t0 -460($sp)
li $t0 1
sw $t0 -464($sp)
lw $t0 -460($sp)
lw $t1 -464($sp)
bgt $t0 $t1 label19
li $v0 4
la $a0 str1
syscall
label19:
li $t0 1
sw $t0 -468($sp)
li $t0 2
sw $t0 -472($sp)
lw $t0 -468($sp)
lw $t1 -472($sp)
bne $t0 $t1 label20
li $v0 4
la $a0 str2
syscall
label20:
li $t0 0
sw $t0 -476($sp)
lw $t1 -476($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t0 0
sw $t0 -480($sp)
lw $t1 -480($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t0 1
sw $t0 -484($sp)
li $t0 2
sw $t0 -488($sp)
lw $t0 -484($sp)
lw $t1 -488($sp)
beq $t0 $t1 label21
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -492($sp)
lw $t1 -4($fp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -496($sp)
lw $t1 -492($sp)
lw $t2 -496($sp)
subu $t0 $t1 $t2
sw $t0 -500($sp)
lw $t0 -500($sp)
li $t1 0
bne $t0 $t1 label23
label24:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -504($sp)
li $t0 30
sw $t0 -508($sp)
lw $t0 -504($sp)
lw $t1 -508($sp)
bge $t0 $t1 label25
lw $t1 -0($fp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -512($sp)
lw $t1 -512($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -516($sp)
lw $t1 -516($sp)
addiu $t0 $t1 0
sw $t0 -520($sp)
lw $t1 -520($sp)
lw $t2 -0($fp)
subu $t0 $t1 $t2
sw $t0 -524($sp)
lw $t0 -524($sp)
li $t1 -1
bne $t0 $t1 label27
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -528($sp)
lw $t1 -528($sp)
lw $t1 -528($sp)
addiu $t0 $t1 1
sw $t0 -532($sp)
lw $t1 -532($sp)
move $t0 $t1
sw $t0 -0($fp)
j label26
label27:
lw $t0 -524($sp)
li $t1 0
bne $t0 $t1 label28
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -536($sp)
lw $t1 -536($sp)
lw $t2 -4($fp)
addu $t0 $t1 $t2
sw $t0 -540($sp)
lw $t1 -540($sp)
move $t0 $t1
sw $t0 -0($fp)
j label26
label28:
label26:
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -544($sp)
lw $t1 -544($sp)
lw $t1 -544($sp)
addiu $t0 $t1 1
sw $t0 -548($sp)
lw $t1 -548($sp)
move $t0 $t1
sw $t0 -4($fp)
j label24
label25:
j label22
label23:
li $t0 -1
sw $t0 -552($sp)
lw $t1 -552($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t0 -1
sw $t0 -556($sp)
lw $t1 -556($sp)
move $t0 $t1
sw $t0 -4($fp)
label22:
label21:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -560($sp)
lw $t1 -560($sp)
move $t0 $t1
sw $t0 -564($sp)
lw $s1 -564($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -568($sp)
lw $t1 -568($sp)
move $t0 $t1
sw $t0 -572($sp)
lw $s1 -572($sp)
li $v0 1
move $a0 $s1
syscall
li $t0 1
sw $t0 -576($sp)
lw $t1 -576($sp)
li $t2 1
subu $t0 $t1 $t2
sw $t0 -580($sp)
lw $t0 -580($sp)
li $t1 0
beq $t0 $t1 label29
li $v0 4
la $a0 str3
syscall
label29:
li $t0 -1
sw $t0 -584($sp)
lw $t1 -584($sp)
move $t0 $t1
sw $t0 0($t9)
li $t0 97
sw $t0 -588($sp)
lw $t1 -588($sp)
move $t0 $t1
sw $t0 4($t9)
label30:
jr $ra
label31:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -0($sp)
lw $t0 -0($sp)
li $t1 -1
bne $t0 $t1 label33
label34:
lw $t1 -0($fp)
li $t2 20
mul $t0 $t1 $t2
sw $t0 -4($sp)
lw $t1 -4($sp)
addiu $t0 $t1 0
sw $t0 -8($sp)
li $t1 30
li $t2 5
div $t0 $t1 $t2
sw $t0 -12($sp)
lw $t1 -8($sp)
lw $t2 -12($sp)
addu $t0 $t1 $t2
sw $t0 -16($sp)
li $t0 10
sw $t0 -20($sp)
lw $t0 -16($sp)
lw $t1 -20($sp)
bge $t0 $t1 label35
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -24($sp)
li $t0 0
sw $t0 -28($sp)
lw $t0 -24($sp)
lw $t1 -28($sp)
bgt $t0 $t1 label36
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -32($sp)
lw $t1 -32($sp)
lw $t1 -32($sp)
addiu $t0 $t1 1
sw $t0 -36($sp)
lw $t1 -36($sp)
move $t0 $t1
sw $t0 -0($fp)
label36:
j label34
label35:
j label32
label33:
lw $t0 -0($sp)
li $t1 0
bne $t0 $t1 label37
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -40($sp)
li $t1 1
li $t2 -1
mul $t0 $t1 $t2
sw $t0 -44($sp)
lw $t1 -40($sp)
lw $t2 -44($sp)
subu $t0 $t1 $t2
sw $t0 -48($sp)
li $t0 0
sw $t0 -52($sp)
lw $t0 -48($sp)
lw $t1 -52($sp)
bne $t0 $t1 label38
label39:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -56($sp)
li $t0 0
sw $t0 -60($sp)
lw $t0 -56($sp)
lw $t1 -60($sp)
bgt $t0 $t1 label40
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -64($sp)
lw $t1 -64($sp)
lw $t1 -64($sp)
addiu $t0 $t1 1
sw $t0 -68($sp)
lw $t1 -68($sp)
li $t2 -2
mul $t0 $t1 $t2
sw $t0 -72($sp)
lw $t1 -72($sp)
addiu $t0 $t1 0
sw $t0 -76($sp)
lw $t1 -76($sp)
move $t0 $t1
sw $t0 -0($fp)
j label39
label40:
label38:
j label32
label37:
lw $t0 -0($sp)
li $t1 1
bne $t0 $t1 label41
li $t0 -233
sw $t0 -80($sp)
lw $t1 -80($sp)
move $t0 $t1
sw $t0 -0($fp)
j label32
label41:
li $t0 233
sw $t0 -84($sp)
lw $t1 -84($sp)
move $t0 $t1
sw $t0 -0($fp)
label32:
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -88($sp)
lw $t0 -88($sp)
li $t1 97
bne $t0 $t1 label43
li $t0 97
sw $t0 -92($sp)
lw $t1 -92($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label43:
lw $t0 -88($sp)
li $t1 65
bne $t0 $t1 label44
li $t0 65
sw $t0 -96($sp)
lw $t1 -96($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label44:
lw $t0 -88($sp)
li $t1 57
bne $t0 $t1 label45
li $t0 57
sw $t0 -100($sp)
lw $t1 -100($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label45:
lw $t0 -88($sp)
li $t1 95
bne $t0 $t1 label46
li $t0 95
sw $t0 -104($sp)
lw $t1 -104($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label46:
lw $t0 -88($sp)
li $t1 43
bne $t0 $t1 label47
li $t0 43
sw $t0 -108($sp)
lw $t1 -108($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label47:
lw $t0 -88($sp)
li $t1 42
bne $t0 $t1 label48
li $t0 42
sw $t0 -112($sp)
lw $t1 -112($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label48:
li $t0 119
sw $t0 -116($sp)
lw $t1 -116($sp)
move $t0 $t1
sw $t0 -4($fp)
label42:
li $t0 0
sw $t0 -120($sp)
lw $t0 -120($sp)
li $t1 0
bne $t0 $t1 label50
j label49
label50:
label49:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -124($sp)
lw $t1 -124($sp)
move $t0 $t1
sw $t0 -128($sp)
lw $s1 -128($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -132($sp)
lw $t1 -132($sp)
move $t0 $t1
sw $t0 -136($sp)
lw $s1 -136($sp)
li $v0 11
move $a0 $s1
syscall
li $t0 -2
sw $t0 -140($sp)
lw $t1 -140($sp)
move $t0 $t1
sw $t0 0($t9)
li $t0 98
sw $t0 -144($sp)
lw $t1 -144($sp)
move $t0 $t1
sw $t0 4($t9)
label51:
jr $ra
label52:
li $t0 10
sw $t0 -0($sp)
lw $t1 -0($sp)
move $v0 $t1
jr $ra
label53:
jr $ra
label54:
li $t0 114
sw $t0 -0($sp)
lw $t1 -0($sp)
move $v0 $t1
jr $ra
label55:
jr $ra
label56:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -0($sp)
lw $t0 -0($sp)
li $t1 1
bne $t0 $t1 label58
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label58:
lw $t0 -0($sp)
li $t1 2
bne $t0 $t1 label59
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -8($sp)
lw $t1 -8($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label59:
lw $t0 -0($sp)
li $t1 3
bne $t0 $t1 label60
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label60:
lw $t0 -0($sp)
li $t1 4
bne $t0 $t1 label61
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -16($sp)
lw $t1 -16($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label61:
li $t0 0
sw $t0 -20($sp)
lw $t1 -20($sp)
move $t0 $t1
sw $t0 -20($fp)
label57:
lw $t1 -20($fp)
addiu $t0 $t1 0
sw $t0 -24($sp)
lw $t1 -24($sp)
move $v0 $t1
jr $ra
label62:
jr $ra
label63:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -0($sp)
lw $t0 -0($sp)
li $t1 1
bne $t0 $t1 label65
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $v0 $t1
jr $ra
j label64
label65:
lw $t0 -0($sp)
li $t1 2
bne $t0 $t1 label66
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -8($sp)
lw $t1 -8($sp)
move $v0 $t1
jr $ra
j label64
label66:
lw $t0 -0($sp)
li $t1 3
bne $t0 $t1 label67
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $v0 $t1
jr $ra
j label64
label67:
lw $t0 -0($sp)
li $t1 4
bne $t0 $t1 label68
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -16($sp)
lw $t1 -16($sp)
move $v0 $t1
jr $ra
j label64
label68:
li $t0 48
sw $t0 -20($sp)
lw $t1 -20($sp)
move $v0 $t1
jr $ra
label64:
label69:
jr $ra
label70:
li $t0 10
sw $t0 -0($sp)
li $t0 2
sw $t0 -4($sp)
li $t1 0
li $t2 -1
subu $t0 $t1 $t2
sw $t0 -8($sp)
li $t1 0
li $t2 2
subu $t0 $t1 $t2
sw $t0 -12($sp)
li $t0 10
sw $t0 -16($sp)
sw $ra -20($sp)
sw $fp -24($sp)
addi $fp $sp -28
addiu $sp $fp -0
jal label54
addiu $sp $fp 28
lw $fp -24($sp)
lw $ra -20($sp)
move $t0 $v0
sw $t0 -20($sp)
lw $t1 -20($sp)
addiu $t0 $t1 0
sw $t0 -24($sp)
lw $t1 -24($sp)
li $t2 97
subu $t0 $t1 $t2
sw $t0 -28($sp)
lw $t1 -28($sp)
addiu $t0 $t1 0
sw $t0 -32($sp)
sw $ra -36($sp)
sw $fp -40($sp)
addi $fp $sp -44
# para
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -8($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -16($sp)
move $t0 $t1
sw $t0 -12($fp)
# para
lw $t1 -32($sp)
move $t0 $t1
sw $t0 -16($fp)
addiu $sp $fp -24
jal label56
addiu $sp $fp 44
lw $fp -40($sp)
lw $ra -36($sp)
move $t0 $v0
sw $t0 -36($sp)
li $t0 99
sw $t0 -40($sp)
lw $t1 -40($sp)
li $t2 97
subu $t0 $t1 $t2
sw $t0 -44($sp)
lw $t1 -36($sp)
lw $t2 -44($sp)
mul $t0 $t1 $t2
sw $t0 -48($sp)
lw $t1 -48($sp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -52($sp)
lw $t1 -0($sp)
lw $t2 -52($sp)
addu $t0 $t1 $t2
sw $t0 -56($sp)
lw $t1 -56($sp)
move $t0 $t1
sw $t0 -0($fp)
lw $t1 -0($fp)
li $t2 4
div $t0 $t1 $t2
sw $t0 -60($sp)
lw $t1 -60($sp)
addiu $t0 $t1 0
sw $t0 -64($sp)
lw $t1 -64($sp)
lw $t1 -64($sp)
addiu $t0 $t1 97
sw $t0 -68($sp)
lw $t1 -68($sp)
li $t2 97
subu $t0 $t1 $t2
sw $t0 -72($sp)
lw $t1 -72($sp)
li $t2 2
subu $t0 $t1 $t2
sw $t0 -76($sp)
li $t1 0
li $t2 -2
subu $t0 $t1 $t2
sw $t0 -80($sp)
lw $t0 -76($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t1 $fp $t2
lw $t0 -80($sp)
sw $t0 0($t1)
li $t0 -2
sw $t0 -84($sp)
li $t0 0
sw $t0 -88($sp)
lw $t0 -88($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -92($sp)
lw $t1 -0($fp)
lw $t2 -92($sp)
div $t0 $t1 $t2
sw $t0 -96($sp)
lw $t1 -84($sp)
lw $t2 -96($sp)
addu $t0 $t1 $t2
sw $t0 -100($sp)
sw $ra -104($sp)
sw $fp -108($sp)
addi $fp $sp -112
addiu $sp $fp -0
jal label52
addiu $sp $fp 112
lw $fp -108($sp)
lw $ra -104($sp)
move $t0 $v0
sw $t0 -104($sp)
lw $t1 -100($sp)
lw $t2 -104($sp)
addu $t0 $t1 $t2
sw $t0 -108($sp)
lw $t1 -108($sp)
li $t2 11
subu $t0 $t1 $t2
sw $t0 -112($sp)
sw $ra -116($sp)
sw $fp -120($sp)
addi $fp $sp -124
addiu $sp $fp -0
jal label52
addiu $sp $fp 124
lw $fp -120($sp)
lw $ra -116($sp)
move $t0 $v0
sw $t0 -116($sp)
li $t1 0
lw $t2 -116($sp)
subu $t0 $t1 $t2
sw $t0 -120($sp)
sw $ra -124($sp)
sw $fp -128($sp)
addi $fp $sp -132
addiu $sp $fp -0
jal label54
addiu $sp $fp 132
lw $fp -128($sp)
lw $ra -124($sp)
move $t0 $v0
sw $t0 -124($sp)
lw $t1 -124($sp)
addiu $t0 $t1 0
sw $t0 -128($sp)
lw $t1 -128($sp)
li $t2 97
subu $t0 $t1 $t2
sw $t0 -132($sp)
li $t1 10
lw $t2 -132($sp)
mul $t0 $t1 $t2
sw $t0 -136($sp)
lw $t1 -136($sp)
addiu $t0 $t1 0
sw $t0 -140($sp)
li $t0 4
sw $t0 -144($sp)
li $t1 0
li $t2 98
subu $t0 $t1 $t2
sw $t0 -148($sp)
lw $t1 -148($sp)
lw $t1 -148($sp)
addiu $t0 $t1 99
sw $t0 -152($sp)
sw $ra -156($sp)
sw $fp -160($sp)
addi $fp $sp -164
addiu $sp $fp -0
jal label52
addiu $sp $fp 164
lw $fp -160($sp)
lw $ra -156($sp)
move $t0 $v0
sw $t0 -156($sp)
lw $t1 -156($sp)
addiu $t0 $t1 0
sw $t0 -160($sp)
li $t0 10
sw $t0 -164($sp)
li $t0 97
sw $t0 -168($sp)
lw $t1 -168($sp)
addiu $t0 $t1 0
sw $t0 -172($sp)
sw $ra -176($sp)
sw $fp -180($sp)
addi $fp $sp -184
# para
lw $t1 -144($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -152($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -160($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -164($sp)
move $t0 $t1
sw $t0 -12($fp)
# para
lw $t1 -172($sp)
move $t0 $t1
sw $t0 -16($fp)
addiu $sp $fp -24
jal label56
addiu $sp $fp 184
lw $fp -180($sp)
lw $ra -176($sp)
move $t0 $v0
sw $t0 -176($sp)
lw $t1 -140($sp)
lw $t2 -176($sp)
addu $t0 $t1 $t2
sw $t0 -180($sp)
lw $t1 -120($sp)
lw $t2 -180($sp)
addu $t0 $t1 $t2
sw $t0 -184($sp)
lw $t0 -112($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t1 $fp $t2
lw $t0 -184($sp)
sw $t0 0($t1)
li $t1 0
li $t2 255
subu $t0 $t1 $t2
sw $t0 -188($sp)
li $t0 1
sw $t0 -192($sp)
lw $t0 -192($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -196($sp)
lw $t1 -188($sp)
lw $t2 -196($sp)
addu $t0 $t1 $t2
sw $t0 -200($sp)
li $t1 98
li $t2 2
mul $t0 $t1 $t2
sw $t0 -204($sp)
lw $t1 -200($sp)
lw $t2 -204($sp)
addu $t0 $t1 $t2
sw $t0 -208($sp)
lw $t1 -208($sp)
li $t2 196
subu $t0 $t1 $t2
sw $t0 -212($sp)
li $t1 0
li $t2 98
subu $t0 $t1 $t2
sw $t0 -216($sp)
lw $t1 -216($sp)
lw $t1 -216($sp)
addiu $t0 $t1 99
sw $t0 -220($sp)
lw $t0 -212($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t1 $fp $t2
lw $t0 -220($sp)
sw $t0 0($t1)
sw $ra -224($sp)
sw $fp -228($sp)
addi $fp $sp -232
addiu $sp $fp -0
jal label54
addiu $sp $fp 232
lw $fp -228($sp)
lw $ra -224($sp)
move $t0 $v0
sw $t0 -224($sp)
lw $t1 -224($sp)
addiu $t0 $t1 0
sw $t0 -228($sp)
lw $t1 -228($sp)
move $t0 $t1
sw $t0 -16($fp)
li $t0 0
sw $t0 -232($sp)
li $t0 4
sw $t0 -236($sp)
li $t0 97
sw $t0 -240($sp)
sw $ra -244($sp)
sw $fp -248($sp)
addi $fp $sp -252
addiu $sp $fp -0
jal label54
addiu $sp $fp 252
lw $fp -248($sp)
lw $ra -244($sp)
move $t0 $v0
sw $t0 -244($sp)
lw $t1 -244($sp)
addiu $t0 $t1 0
sw $t0 -248($sp)
sw $ra -252($sp)
sw $fp -256($sp)
addi $fp $sp -260
addiu $sp $fp -0
jal label54
addiu $sp $fp 260
lw $fp -256($sp)
lw $ra -252($sp)
move $t0 $v0
sw $t0 -252($sp)
lw $t1 -252($sp)
addiu $t0 $t1 0
sw $t0 -256($sp)
li $t0 97
sw $t0 -260($sp)
sw $ra -264($sp)
sw $fp -268($sp)
addi $fp $sp -272
# para
lw $t1 -236($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -240($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -248($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -256($sp)
move $t0 $t1
sw $t0 -12($fp)
# para
lw $t1 -260($sp)
move $t0 $t1
sw $t0 -16($fp)
addiu $sp $fp -20
jal label63
addiu $sp $fp 272
lw $fp -268($sp)
lw $ra -264($sp)
move $t0 $v0
sw $t0 -264($sp)
lw $t1 -264($sp)
addiu $t0 $t1 0
sw $t0 -268($sp)
lw $t0 -232($sp)
sll $t2 $t0 2
addiu $t2 $t2 20
subu $t1 $fp $t2
lw $t0 -268($sp)
sw $t0 0($t1)
li $t0 1
sw $t0 -272($sp)
li $t0 0
sw $t0 -276($sp)
lw $t0 -276($sp)
sll $t2 $t0 2
addiu $t2 $t2 20
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -280($sp)
lw $t1 -280($sp)
addiu $t0 $t1 0
sw $t0 -284($sp)
lw $t0 -272($sp)
sll $t2 $t0 2
addiu $t2 $t2 20
subu $t1 $fp $t2
lw $t0 -284($sp)
sw $t0 0($t1)
li $t0 2
sw $t0 -288($sp)
li $t0 120
sw $t0 -292($sp)
lw $t0 -288($sp)
sll $t2 $t0 2
addiu $t2 $t2 20
subu $t1 $fp $t2
lw $t0 -292($sp)
sw $t0 0($t1)
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -296($sp)
lw $t1 -296($sp)
move $t0 $t1
sw $t0 -300($sp)
lw $s1 -300($sp)
li $v0 1
move $a0 $s1
syscall
li $t0 0
sw $t0 -304($sp)
lw $t0 -304($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -308($sp)
lw $t1 -308($sp)
addiu $t0 $t1 0
sw $t0 -312($sp)
lw $t1 -312($sp)
move $t0 $t1
sw $t0 -316($sp)
lw $s1 -316($sp)
li $v0 1
move $a0 $s1
syscall
li $t0 1
sw $t0 -320($sp)
lw $t0 -320($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -324($sp)
lw $t1 -324($sp)
addiu $t0 $t1 0
sw $t0 -328($sp)
lw $t1 -328($sp)
move $t0 $t1
sw $t0 -332($sp)
lw $s1 -332($sp)
li $v0 1
move $a0 $s1
syscall
li $t0 2
sw $t0 -336($sp)
lw $t0 -336($sp)
sll $t2 $t0 2
addiu $t2 $t2 4
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -340($sp)
lw $t1 -340($sp)
addiu $t0 $t1 0
sw $t0 -344($sp)
lw $t1 -344($sp)
move $t0 $t1
sw $t0 -348($sp)
lw $s1 -348($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -352($sp)
lw $t1 -352($sp)
move $t0 $t1
sw $t0 -356($sp)
lw $s1 -356($sp)
li $v0 11
move $a0 $s1
syscall
li $t0 0
sw $t0 -360($sp)
lw $t0 -360($sp)
sll $t2 $t0 2
addiu $t2 $t2 20
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -364($sp)
lw $t1 -364($sp)
addiu $t0 $t1 0
sw $t0 -368($sp)
lw $t1 -368($sp)
move $t0 $t1
sw $t0 -372($sp)
lw $s1 -372($sp)
li $v0 11
move $a0 $s1
syscall
li $t0 1
sw $t0 -376($sp)
lw $t0 -376($sp)
sll $t2 $t0 2
addiu $t2 $t2 20
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -380($sp)
lw $t1 -380($sp)
addiu $t0 $t1 0
sw $t0 -384($sp)
lw $t1 -384($sp)
move $t0 $t1
sw $t0 -388($sp)
lw $s1 -388($sp)
li $v0 11
move $a0 $s1
syscall
li $t0 2
sw $t0 -392($sp)
lw $t0 -392($sp)
sll $t2 $t0 2
addiu $t2 $t2 20
subu $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -396($sp)
lw $t1 -396($sp)
addiu $t0 $t1 0
sw $t0 -400($sp)
lw $t1 -400($sp)
move $t0 $t1
sw $t0 -404($sp)
lw $s1 -404($sp)
li $v0 11
move $a0 $s1
syscall
li $t0 -3
sw $t0 -408($sp)
lw $t1 -408($sp)
move $t0 $t1
sw $t0 0($t9)
li $t0 99
sw $t0 -412($sp)
lw $t1 -412($sp)
move $t0 $t1
sw $t0 4($t9)
label71:
jr $ra
label72:
li $v0 5
syscall
move $t0 $v0
sw $t0 -0($sp)
lw $t1 -0($sp)
move $t0 $t1
sw $t0 -0($fp)
li $v0 12
syscall
move $t0 $v0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -4($fp)
li $v0 4
la $a0 str4
syscall
li $v0 4
la $a0 str5
syscall
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -8($sp)
lw $t1 -8($sp)
move $t0 $t1
sw $t0 -12($sp)
lw $s1 -12($sp)
li $v0 1
move $a0 $s1
syscall
li $v0 4
la $a0 str6
syscall
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -16($sp)
lw $t1 -16($sp)
move $t0 $t1
sw $t0 -20($sp)
lw $s1 -20($sp)
li $v0 11
move $a0 $s1
syscall
li $t0 -4
sw $t0 -24($sp)
lw $t1 -24($sp)
move $t0 $t1
sw $t0 -8($fp)
li $t0 100
sw $t0 -28($sp)
lw $t1 -28($sp)
move $t0 $t1
sw $t0 -12($fp)
label73:
jr $ra
label74:
label75:
jr $ra
label76:
li $t0 0
sw $t0 -0($sp)
lw $t1 -0($sp)
move $t0 $t1
sw $t0 -16($fp)
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -8($sp)
lw $t0 -4($sp)
lw $t1 -8($sp)
bge $t0 $t1 label77
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -16($sp)
lw $t0 -12($sp)
lw $t1 -16($sp)
blt $t0 $t1 label78
li $t0 1
sw $t0 -20($sp)
lw $t1 -20($sp)
move $t0 $t1
sw $t0 -16($fp)
label78:
label77:
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -24($sp)
lw $t1 -24($sp)
move $v0 $t1
jr $ra
label79:
jr $ra
label80:
li $t0 0
sw $t0 -0($sp)
lw $t1 -0($sp)
move $t0 $t1
sw $t0 -16($fp)
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -8($sp)
lw $t0 -4($sp)
lw $t1 -8($sp)
bge $t0 $t1 label81
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -16($sp)
lw $t0 -12($sp)
lw $t1 -16($sp)
bgt $t0 $t1 label82
li $t0 1
sw $t0 -20($sp)
lw $t1 -20($sp)
move $t0 $t1
sw $t0 -16($fp)
label82:
label81:
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -24($sp)
lw $t1 -24($sp)
move $v0 $t1
jr $ra
label83:
jr $ra
label84:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -0($sp)
lw $t1 -0($sp)
move $t0 $t1
sw $t0 -8($fp)
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -12($fp)
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -8($sp)
lw $t0 -8($sp)
sll $t2 $t0 2
addiu $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -12($sp)
lw $t1 -12($sp)
addiu $t0 $t1 0
sw $t0 -16($sp)
lw $t1 -16($sp)
move $t0 $t1
sw $t0 -16($fp)
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -20($sp)
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -24($sp)
lw $t0 -20($sp)
lw $t1 -24($sp)
blt $t0 $t1 label85
jr $ra
label85:
label86:
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -28($sp)
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -32($sp)
lw $t0 -28($sp)
lw $t1 -32($sp)
bge $t0 $t1 label87
label88:
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -36($sp)
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -40($sp)
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -44($sp)
lw $t0 -44($sp)
sll $t2 $t0 2
addiu $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -48($sp)
lw $t1 -48($sp)
addiu $t0 $t1 0
sw $t0 -52($sp)
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -56($sp)
sw $ra -60($sp)
sw $fp -64($sp)
addi $fp $sp -68
# para
lw $t1 -36($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -40($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -52($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -56($sp)
move $t0 $t1
sw $t0 -12($fp)
addiu $sp $fp -20
jal label76
addiu $sp $fp 68
lw $fp -64($sp)
lw $ra -60($sp)
move $t0 $v0
sw $t0 -60($sp)
lw $t1 -60($sp)
addiu $t0 $t1 0
sw $t0 -64($sp)
li $t0 1
sw $t0 -68($sp)
lw $t0 -64($sp)
lw $t1 -68($sp)
bne $t0 $t1 label89
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -72($sp)
lw $t1 -72($sp)
li $t2 1
subu $t0 $t1 $t2
sw $t0 -76($sp)
lw $t1 -76($sp)
move $t0 $t1
sw $t0 -12($fp)
j label88
label89:
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -80($sp)
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -84($sp)
lw $t0 -84($sp)
sll $t2 $t0 2
addiu $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -88($sp)
lw $t1 -88($sp)
addiu $t0 $t1 0
sw $t0 -92($sp)
lw $t0 -80($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -92($sp)
sw $t0 0($t1)
label90:
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -96($sp)
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -100($sp)
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -104($sp)
lw $t0 -104($sp)
sll $t2 $t0 2
addiu $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -108($sp)
lw $t1 -108($sp)
addiu $t0 $t1 0
sw $t0 -112($sp)
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -116($sp)
sw $ra -120($sp)
sw $fp -124($sp)
addi $fp $sp -128
# para
lw $t1 -96($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -100($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -112($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -116($sp)
move $t0 $t1
sw $t0 -12($fp)
addiu $sp $fp -20
jal label80
addiu $sp $fp 128
lw $fp -124($sp)
lw $ra -120($sp)
move $t0 $v0
sw $t0 -120($sp)
lw $t1 -120($sp)
addiu $t0 $t1 0
sw $t0 -124($sp)
li $t0 1
sw $t0 -128($sp)
lw $t0 -124($sp)
lw $t1 -128($sp)
bne $t0 $t1 label91
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -132($sp)
lw $t1 -132($sp)
lw $t1 -132($sp)
addiu $t0 $t1 1
sw $t0 -136($sp)
lw $t1 -136($sp)
move $t0 $t1
sw $t0 -8($fp)
j label90
label91:
lw $t1 -12($fp)
addiu $t0 $t1 0
sw $t0 -140($sp)
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -144($sp)
lw $t0 -144($sp)
sll $t2 $t0 2
addiu $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -148($sp)
lw $t1 -148($sp)
addiu $t0 $t1 0
sw $t0 -152($sp)
lw $t0 -140($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -152($sp)
sw $t0 0($t1)
j label86
label87:
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -156($sp)
lw $t1 -16($fp)
addiu $t0 $t1 0
sw $t0 -160($sp)
lw $t0 -156($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -160($sp)
sw $t0 0($t1)
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -164($sp)
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -168($sp)
lw $t1 -168($sp)
li $t2 1
subu $t0 $t1 $t2
sw $t0 -172($sp)
sw $ra -176($sp)
sw $fp -180($sp)
addi $fp $sp -184
# para
lw $t1 -164($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -172($sp)
move $t0 $t1
sw $t0 -4($fp)
addiu $sp $fp -20
jal label84
addiu $sp $fp 184
lw $fp -180($sp)
lw $ra -176($sp)
lw $t1 -8($fp)
addiu $t0 $t1 0
sw $t0 -176($sp)
lw $t1 -176($sp)
lw $t1 -176($sp)
addiu $t0 $t1 1
sw $t0 -180($sp)
lw $t1 -4($fp)
addiu $t0 $t1 0
sw $t0 -184($sp)
sw $ra -188($sp)
sw $fp -192($sp)
addi $fp $sp -196
# para
lw $t1 -180($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -184($sp)
move $t0 $t1
sw $t0 -4($fp)
addiu $sp $fp -20
jal label84
addiu $sp $fp 196
lw $fp -192($sp)
lw $ra -188($sp)
jr $ra
label92:
jr $ra
label93:
li $t0 0
sw $t0 -0($sp)
li $t0 5
sw $t0 -4($sp)
lw $t0 -0($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -4($sp)
sw $t0 0($t1)
li $t0 1
sw $t0 -8($sp)
li $t0 8
sw $t0 -12($sp)
lw $t0 -8($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -12($sp)
sw $t0 0($t1)
li $t0 2
sw $t0 -16($sp)
li $t0 3
sw $t0 -20($sp)
lw $t0 -16($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -20($sp)
sw $t0 0($t1)
li $t0 3
sw $t0 -24($sp)
li $t0 6
sw $t0 -28($sp)
lw $t0 -24($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -28($sp)
sw $t0 0($t1)
li $t0 4
sw $t0 -32($sp)
li $t0 4
sw $t0 -36($sp)
lw $t0 -32($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -36($sp)
sw $t0 0($t1)
li $t0 5
sw $t0 -40($sp)
li $t0 1
sw $t0 -44($sp)
lw $t0 -40($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -44($sp)
sw $t0 0($t1)
li $t0 6
sw $t0 -48($sp)
li $t0 2
sw $t0 -52($sp)
lw $t0 -48($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -52($sp)
sw $t0 0($t1)
li $t0 7
sw $t0 -56($sp)
li $t0 7
sw $t0 -60($sp)
lw $t0 -56($sp)
sll $t2 $t0 2
addiu $t2 $t2 268501160
addu $t1 $0 $t2
lw $t0 -60($sp)
sw $t0 0($t1)
li $t0 0
sw $t0 -64($sp)
li $t0 7
sw $t0 -68($sp)
sw $ra -72($sp)
sw $fp -76($sp)
addi $fp $sp -80
# para
lw $t1 -64($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -68($sp)
move $t0 $t1
sw $t0 -4($fp)
addiu $sp $fp -20
jal label84
addiu $sp $fp 80
lw $fp -76($sp)
lw $ra -72($sp)
li $t0 0
sw $t0 -72($sp)
lw $t1 -72($sp)
move $t0 $t1
sw $t0 -0($fp)
label94:
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -76($sp)
li $t0 8
sw $t0 -80($sp)
lw $t0 -76($sp)
lw $t1 -80($sp)
bge $t0 $t1 label95
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -84($sp)
lw $t0 -84($sp)
sll $t2 $t0 2
addiu $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -88($sp)
lw $t1 -88($sp)
addiu $t0 $t1 0
sw $t0 -92($sp)
lw $t1 -92($sp)
move $t0 $t1
sw $t0 -96($sp)
lw $s1 -96($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -100($sp)
lw $t1 -100($sp)
lw $t1 -100($sp)
addiu $t0 $t1 1
sw $t0 -104($sp)
lw $t1 -104($sp)
move $t0 $t1
sw $t0 -0($fp)
j label94
label95:
li $t0 -5
sw $t0 -108($sp)
lw $t1 -108($sp)
move $t0 $t1
sw $t0 0($t9)
li $t0 101
sw $t0 -112($sp)
lw $t1 -112($sp)
move $t0 $t1
sw $t0 4($t9)
label96:
jr $ra
label97:
li $v0 5
syscall
move $t0 $v0
sw $t0 -0($sp)
lw $t1 -0($sp)
move $t0 $t1
sw $t0 -0($fp)
lw $t1 -0($fp)
addiu $t0 $t1 0
sw $t0 -4($sp)
lw $t0 -4($sp)
li $t1 0
bne $t0 $t1 label99
sw $ra -8($sp)
sw $fp -12($sp)
addi $fp $sp -16
addiu $sp $fp -8
jal label1
addiu $sp $fp 16
lw $fp -12($sp)
lw $ra -8($sp)
j label98
label99:
lw $t0 -4($sp)
li $t1 1
bne $t0 $t1 label100
li $t0 1
sw $t0 -8($sp)
li $t0 97
sw $t0 -12($sp)
sw $ra -16($sp)
sw $fp -20($sp)
addi $fp $sp -24
# para
lw $t1 -8($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -4($fp)
addiu $sp $fp -8
jal label31
addiu $sp $fp 24
lw $fp -20($sp)
lw $ra -16($sp)
li $t0 -1
sw $t0 -16($sp)
li $t0 43
sw $t0 -20($sp)
sw $ra -24($sp)
sw $fp -28($sp)
addi $fp $sp -32
# para
lw $t1 -16($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -20($sp)
move $t0 $t1
sw $t0 -4($fp)
addiu $sp $fp -8
jal label31
addiu $sp $fp 32
lw $fp -28($sp)
lw $ra -24($sp)
li $t0 0
sw $t0 -24($sp)
li $t0 95
sw $t0 -28($sp)
sw $ra -32($sp)
sw $fp -36($sp)
addi $fp $sp -40
# para
lw $t1 -24($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -28($sp)
move $t0 $t1
sw $t0 -4($fp)
addiu $sp $fp -8
jal label31
addiu $sp $fp 40
lw $fp -36($sp)
lw $ra -32($sp)
li $t0 2
sw $t0 -32($sp)
li $t0 57
sw $t0 -36($sp)
sw $ra -40($sp)
sw $fp -44($sp)
addi $fp $sp -48
# para
lw $t1 -32($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -36($sp)
move $t0 $t1
sw $t0 -4($fp)
addiu $sp $fp -8
jal label31
addiu $sp $fp 48
lw $fp -44($sp)
lw $ra -40($sp)
j label98
label100:
lw $t0 -4($sp)
li $t1 2
bne $t0 $t1 label101
sw $ra -40($sp)
sw $fp -44($sp)
addi $fp $sp -48
addiu $sp $fp -32
jal label70
addiu $sp $fp 48
lw $fp -44($sp)
lw $ra -40($sp)
j label98
label101:
lw $t0 -4($sp)
li $t1 3
bne $t0 $t1 label102
sw $ra -40($sp)
sw $fp -44($sp)
addi $fp $sp -48
addiu $sp $fp -16
jal label72
addiu $sp $fp 48
lw $fp -44($sp)
lw $ra -40($sp)
j label98
label102:
lw $t0 -4($sp)
li $t1 4
bne $t0 $t1 label103
sw $ra -40($sp)
sw $fp -44($sp)
addi $fp $sp -48
addiu $sp $fp -4
jal label93
addiu $sp $fp 48
lw $fp -44($sp)
lw $ra -40($sp)
j label98
label103:
label98:
lw $t1 0($t9)
addiu $t0 $t1 0
sw $t0 -40($sp)
lw $t1 -40($sp)
move $t0 $t1
sw $t0 -44($sp)
lw $s1 -44($sp)
li $v0 1
move $a0 $s1
syscall
lw $t1 4($t9)
addiu $t0 $t1 0
sw $t0 -48($sp)
lw $t1 -48($sp)
move $t0 $t1
sw $t0 -52($sp)
lw $s1 -52($sp)
li $v0 11
move $a0 $s1
syscall
label104:
jr $ra
main:
li $t0 0
sw $t0 -0($sp)
lw $t1 -0($sp)
move $t0 $t1
sw $t0 0($t9)
li $t0 95
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 4($t9)
sw $ra -8($sp)
sw $fp -12($sp)
addi $fp $sp -16
addiu $sp $fp -4
jal label97
addiu $sp $fp 16
lw $fp -12($sp)
lw $ra -8($sp)
sw $ra -8($sp)
sw $fp -12($sp)
addi $fp $sp -16
addiu $sp $fp -0
jal label74
addiu $sp $fp 16
lw $fp -12($sp)
lw $ra -8($sp)
label105:
