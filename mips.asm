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
addi $sp $fp -0
la $ra label105
j main
label1:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t1 1
li $t2 98
mul $t0 $t1 $t2
sw $t0 -16($sp)
lw $t1 -16($sp)
addi $t0 $t1 0
sw $t0 -20($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -24($sp)
lw $t1 -20($sp)
lw $t2 -24($sp)
add $t0 $t1 $t2
sw $t0 -28($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -36($sp)
lw $t2 -40($sp)
add $t0 $t1 $t2
sw $t0 -44($sp)
lw $t0 -28($sp)
lw $t1 -44($sp)
ble $t0 $t1 label2
label3:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -48($sp)
lw $t1 -48($sp)
addi $t0 $t1 0
sw $t0 -52($sp)
li $t1 1
li $t2 100
mul $t0 $t1 $t2
sw $t0 -56($sp)
lw $t1 -56($sp)
addi $t0 $t1 0
sw $t0 -60($sp)
lw $t0 -52($sp)
lw $t1 -60($sp)
bge $t0 $t1 label4
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -64($sp)
lw $t1 -64($sp)
addi $t0 $t1 0
sw $t0 -68($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -72($sp)
lw $t1 -68($sp)
lw $t2 -72($sp)
add $t0 $t1 $t2
sw $t0 -76($sp)
lw $t1 -76($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -80($sp)
lw $t1 -80($sp)
addi $t0 $t1 0
sw $t0 -84($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -88($sp)
lw $t1 -84($sp)
lw $t2 -88($sp)
add $t0 $t1 $t2
sw $t0 -92($sp)
lw $t1 -92($sp)
move $t0 $t1
sw $t0 -4($fp)
j label3
label4:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -96($sp)
lw $t1 -96($sp)
addi $t0 $t1 0
sw $t0 -100($sp)
li $t1 1
li $t2 100
mul $t0 $t1 $t2
sw $t0 -104($sp)
lw $t1 -100($sp)
lw $t2 -104($sp)
sub $t0 $t1 $t2
sw $t0 -108($sp)
li $t1 1
lw $t2 -108($sp)
mul $t0 $t1 $t2
sw $t0 -112($sp)
lw $t1 -112($sp)
li $t2 3
mul $t0 $t1 $t2
sw $t0 -116($sp)
lw $t1 -116($sp)
addi $t0 $t1 0
sw $t0 -120($sp)
lw $t0 -120($sp)
li $t1 15
bne $t0 $t1 label6
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -124($sp)
lw $t1 -124($sp)
li $t2 10
mul $t0 $t1 $t2
sw $t0 -128($sp)
li $t1 0
lw $t2 -128($sp)
sub $t0 $t1 $t2
sw $t0 -132($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -136($sp)
lw $t1 -136($sp)
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -140($sp)
lw $t1 -132($sp)
lw $t2 -140($sp)
add $t0 $t1 $t2
sw $t0 -144($sp)
li $t1 1
li $t2 117
mul $t0 $t1 $t2
sw $t0 -148($sp)
lw $t1 -144($sp)
lw $t2 -148($sp)
add $t0 $t1 $t2
sw $t0 -152($sp)
li $t1 1
li $t2 98
mul $t0 $t1 $t2
sw $t0 -156($sp)
lw $t1 -152($sp)
lw $t2 -156($sp)
sub $t0 $t1 $t2
sw $t0 -160($sp)
lw $t1 -160($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -164($sp)
lw $t1 -164($sp)
addi $t0 $t1 0
sw $t0 -168($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -172($sp)
lw $t1 -168($sp)
lw $t2 -172($sp)
sub $t0 $t1 $t2
sw $t0 -176($sp)
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -180($sp)
lw $t1 -180($sp)
li $t2 97
mul $t0 $t1 $t2
sw $t0 -184($sp)
lw $t1 -176($sp)
lw $t2 -184($sp)
add $t0 $t1 $t2
sw $t0 -188($sp)
li $t1 1
li $t2 100
mul $t0 $t1 $t2
sw $t0 -192($sp)
lw $t1 -188($sp)
lw $t2 -192($sp)
sub $t0 $t1 $t2
sw $t0 -196($sp)
li $t1 1
li $t2 42
mul $t0 $t1 $t2
sw $t0 -200($sp)
lw $t1 -196($sp)
lw $t2 -200($sp)
add $t0 $t1 $t2
sw $t0 -204($sp)
li $t1 1
li $t2 34
mul $t0 $t1 $t2
sw $t0 -208($sp)
lw $t1 -204($sp)
lw $t2 -208($sp)
add $t0 $t1 $t2
sw $t0 -212($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -216($sp)
lw $t1 -216($sp)
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -220($sp)
lw $t1 -212($sp)
lw $t2 -220($sp)
add $t0 $t1 $t2
sw $t0 -224($sp)
lw $t1 -224($sp)
move $t0 $t1
sw $t0 -4($fp)
j label5
label6:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -228($sp)
lw $t1 -228($sp)
li $t2 4
mul $t0 $t1 $t2
sw $t0 -232($sp)
lw $t1 -232($sp)
addi $t0 $t1 0
sw $t0 -236($sp)
li $t1 1
li $t2 5
mul $t0 $t1 $t2
sw $t0 -240($sp)
lw $t1 -240($sp)
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -244($sp)
lw $t1 -236($sp)
lw $t2 -244($sp)
add $t0 $t1 $t2
sw $t0 -248($sp)
li $t1 1
li $t2 24
mul $t0 $t1 $t2
sw $t0 -252($sp)
lw $t1 -248($sp)
lw $t2 -252($sp)
add $t0 $t1 $t2
sw $t0 -256($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -260($sp)
lw $t1 -256($sp)
lw $t2 -260($sp)
sub $t0 $t1 $t2
sw $t0 -264($sp)
li $t1 1
li $t2 99
mul $t0 $t1 $t2
sw $t0 -268($sp)
lw $t1 -264($sp)
lw $t2 -268($sp)
add $t0 $t1 $t2
sw $t0 -272($sp)
lw $t1 -272($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -276($sp)
li $t1 0
lw $t2 -276($sp)
sub $t0 $t1 $t2
sw $t0 -280($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -284($sp)
lw $t1 -280($sp)
lw $t2 -284($sp)
add $t0 $t1 $t2
sw $t0 -288($sp)
li $t1 1
li $t2 4
mul $t0 $t1 $t2
sw $t0 -292($sp)
lw $t1 -292($sp)
li $t2 97
mul $t0 $t1 $t2
sw $t0 -296($sp)
lw $t1 -288($sp)
lw $t2 -296($sp)
add $t0 $t1 $t2
sw $t0 -300($sp)
li $t1 1
li $t2 1653
mul $t0 $t1 $t2
sw $t0 -304($sp)
lw $t1 -300($sp)
lw $t2 -304($sp)
sub $t0 $t1 $t2
sw $t0 -308($sp)
li $t1 1
li $t2 453
mul $t0 $t1 $t2
sw $t0 -312($sp)
lw $t1 -308($sp)
lw $t2 -312($sp)
add $t0 $t1 $t2
sw $t0 -316($sp)
li $t1 1
li $t2 555
mul $t0 $t1 $t2
sw $t0 -320($sp)
lw $t1 -316($sp)
lw $t2 -320($sp)
add $t0 $t1 $t2
sw $t0 -324($sp)
li $t1 1
li $t2 4
mul $t0 $t1 $t2
sw $t0 -328($sp)
lw $t1 -328($sp)
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -332($sp)
lw $t1 -324($sp)
lw $t2 -332($sp)
sub $t0 $t1 $t2
sw $t0 -336($sp)
lw $t1 -336($sp)
move $t0 $t1
sw $t0 -4($fp)
label5:
label2:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -340($sp)
lw $t1 -340($sp)
addi $t0 $t1 0
sw $t0 -344($sp)
lw $t1 -344($sp)
move $t0 $t1
sw $t0 -348($sp)
lw $s1 -348($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -352($sp)
lw $t1 -352($sp)
addi $t0 $t1 0
sw $t0 -356($sp)
lw $t1 -356($sp)
move $t0 $t1
sw $t0 -360($sp)
lw $s1 -360($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -364($sp)
lw $t1 -364($sp)
addi $t0 $t1 0
sw $t0 -368($sp)
lw $t1 -368($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -372($sp)
lw $t1 -372($sp)
addi $t0 $t1 0
sw $t0 -376($sp)
lw $t1 -376($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t1 1
li $t2 98
mul $t0 $t1 $t2
sw $t0 -380($sp)
lw $t1 -380($sp)
addi $t0 $t1 0
sw $t0 -384($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -388($sp)
lw $t1 -384($sp)
lw $t2 -388($sp)
add $t0 $t1 $t2
sw $t0 -392($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -396($sp)
lw $t1 -396($sp)
addi $t0 $t1 0
sw $t0 -400($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -404($sp)
lw $t1 -400($sp)
lw $t2 -404($sp)
add $t0 $t1 $t2
sw $t0 -408($sp)
lw $t0 -392($sp)
lw $t1 -408($sp)
blt $t0 $t1 label7
label8:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -412($sp)
lw $t1 -412($sp)
addi $t0 $t1 0
sw $t0 -416($sp)
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -420($sp)
lw $t1 -420($sp)
addi $t0 $t1 0
sw $t0 -424($sp)
lw $t0 -416($sp)
lw $t1 -424($sp)
bge $t0 $t1 label9
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -428($sp)
lw $t1 -428($sp)
addi $t0 $t1 0
sw $t0 -432($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -436($sp)
lw $t1 -436($sp)
addi $t0 $t1 0
sw $t0 -440($sp)
lw $t0 -432($sp)
lw $t1 -440($sp)
ble $t0 $t1 label10
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -444($sp)
lw $t1 -444($sp)
addi $t0 $t1 0
sw $t0 -448($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -452($sp)
lw $t1 -448($sp)
lw $t2 -452($sp)
add $t0 $t1 $t2
sw $t0 -456($sp)
lw $t1 -456($sp)
move $t0 $t1
sw $t0 -0($fp)
label10:
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -460($sp)
lw $t1 -460($sp)
addi $t0 $t1 0
sw $t0 -464($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -468($sp)
lw $t1 -464($sp)
lw $t2 -468($sp)
add $t0 $t1 $t2
sw $t0 -472($sp)
lw $t1 -472($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -476($sp)
lw $t1 -476($sp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -480($sp)
lw $t1 -480($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -484($sp)
lw $t1 -484($sp)
addi $t0 $t1 0
sw $t0 -488($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -492($sp)
lw $t1 -492($sp)
addi $t0 $t1 0
sw $t0 -496($sp)
lw $t0 -488($sp)
lw $t1 -496($sp)
bne $t0 $t1 label11
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -500($sp)
lw $t1 -500($sp)
addi $t0 $t1 0
sw $t0 -504($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -508($sp)
lw $t1 -504($sp)
lw $t2 -508($sp)
add $t0 $t1 $t2
sw $t0 -512($sp)
lw $t1 -512($sp)
move $t0 $t1
sw $t0 -4($fp)
label11:
j label8
label9:
label7:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -516($sp)
lw $t1 -516($sp)
addi $t0 $t1 0
sw $t0 -520($sp)
lw $t1 -520($sp)
move $t0 $t1
sw $t0 -524($sp)
lw $s1 -524($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -528($sp)
lw $t1 -528($sp)
addi $t0 $t1 0
sw $t0 -532($sp)
lw $t1 -532($sp)
move $t0 $t1
sw $t0 -536($sp)
lw $s1 -536($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -540($sp)
lw $t1 -540($sp)
addi $t0 $t1 0
sw $t0 -544($sp)
lw $t1 -544($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -548($sp)
lw $t1 -548($sp)
addi $t0 $t1 0
sw $t0 -552($sp)
lw $t1 -552($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -556($sp)
lw $t1 -556($sp)
addi $t0 $t1 0
sw $t0 -560($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -564($sp)
lw $t1 -564($sp)
addi $t0 $t1 0
sw $t0 -568($sp)
lw $t0 -560($sp)
lw $t1 -568($sp)
bge $t0 $t1 label12
label13:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -572($sp)
lw $t1 -572($sp)
addi $t0 $t1 0
sw $t0 -576($sp)
li $t1 1
li $t2 20
mul $t0 $t1 $t2
sw $t0 -580($sp)
lw $t1 -580($sp)
addi $t0 $t1 0
sw $t0 -584($sp)
lw $t0 -576($sp)
lw $t1 -584($sp)
bge $t0 $t1 label14
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -588($sp)
lw $t1 -588($sp)
addi $t0 $t1 0
sw $t0 -592($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -596($sp)
lw $t1 -596($sp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -600($sp)
lw $t1 -600($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -604($sp)
lw $t1 -592($sp)
lw $t2 -604($sp)
sub $t0 $t1 $t2
sw $t0 -608($sp)
lw $t0 -608($sp)
li $t1 0
bne $t0 $t1 label16
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -612($sp)
lw $t1 -612($sp)
addi $t0 $t1 0
sw $t0 -616($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -620($sp)
lw $t1 -616($sp)
lw $t2 -620($sp)
add $t0 $t1 $t2
sw $t0 -624($sp)
lw $t1 -624($sp)
move $t0 $t1
sw $t0 -0($fp)
j label15
label16:
lw $t0 -608($sp)
li $t1 1
bne $t0 $t1 label17
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -628($sp)
lw $t1 -628($sp)
addi $t0 $t1 0
sw $t0 -632($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -636($sp)
lw $t1 -632($sp)
lw $t2 -636($sp)
add $t0 $t1 $t2
sw $t0 -640($sp)
lw $t1 -640($sp)
move $t0 $t1
sw $t0 -0($fp)
j label15
label17:
label15:
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -644($sp)
lw $t1 -644($sp)
addi $t0 $t1 0
sw $t0 -648($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -652($sp)
lw $t1 -648($sp)
lw $t2 -652($sp)
add $t0 $t1 $t2
sw $t0 -656($sp)
lw $t1 -656($sp)
move $t0 $t1
sw $t0 -4($fp)
j label13
label14:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -660($sp)
lw $t1 -660($sp)
addi $t0 $t1 0
sw $t0 -664($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -668($sp)
lw $t1 -668($sp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -672($sp)
lw $t1 -672($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -676($sp)
lw $t1 -676($sp)
addi $t0 $t1 0
sw $t0 -680($sp)
lw $t0 -664($sp)
lw $t1 -680($sp)
bne $t0 $t1 label18
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -684($sp)
lw $t1 -684($sp)
li $t2 7
mul $t0 $t1 $t2
sw $t0 -688($sp)
lw $t1 -688($sp)
addi $t0 $t1 0
sw $t0 -692($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -696($sp)
lw $t1 -696($sp)
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -700($sp)
lw $t1 -692($sp)
lw $t2 -700($sp)
add $t0 $t1 $t2
sw $t0 -704($sp)
li $t1 1
li $t2 99
mul $t0 $t1 $t2
sw $t0 -708($sp)
lw $t1 -704($sp)
lw $t2 -708($sp)
add $t0 $t1 $t2
sw $t0 -712($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -716($sp)
lw $t1 -712($sp)
lw $t2 -716($sp)
sub $t0 $t1 $t2
sw $t0 -720($sp)
li $t1 1
li $t2 103
mul $t0 $t1 $t2
sw $t0 -724($sp)
lw $t1 -720($sp)
lw $t2 -724($sp)
add $t0 $t1 $t2
sw $t0 -728($sp)
lw $t1 -728($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -732($sp)
li $t1 0
lw $t2 -732($sp)
sub $t0 $t1 $t2
sw $t0 -736($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -740($sp)
lw $t1 -736($sp)
lw $t2 -740($sp)
add $t0 $t1 $t2
sw $t0 -744($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -748($sp)
lw $t1 -748($sp)
li $t2 97
mul $t0 $t1 $t2
sw $t0 -752($sp)
lw $t1 -744($sp)
lw $t2 -752($sp)
add $t0 $t1 $t2
sw $t0 -756($sp)
li $t1 1
li $t2 523
mul $t0 $t1 $t2
sw $t0 -760($sp)
lw $t1 -756($sp)
lw $t2 -760($sp)
sub $t0 $t1 $t2
sw $t0 -764($sp)
li $t1 1
li $t2 53
mul $t0 $t1 $t2
sw $t0 -768($sp)
lw $t1 -764($sp)
lw $t2 -768($sp)
add $t0 $t1 $t2
sw $t0 -772($sp)
li $t1 1
li $t2 355
mul $t0 $t1 $t2
sw $t0 -776($sp)
lw $t1 -772($sp)
lw $t2 -776($sp)
add $t0 $t1 $t2
sw $t0 -780($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -784($sp)
lw $t1 -784($sp)
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -788($sp)
lw $t1 -780($sp)
lw $t2 -788($sp)
sub $t0 $t1 $t2
sw $t0 -792($sp)
lw $t1 -792($sp)
move $t0 $t1
sw $t0 -4($fp)
label18:
label12:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -796($sp)
lw $t1 -796($sp)
addi $t0 $t1 0
sw $t0 -800($sp)
lw $t1 -800($sp)
move $t0 $t1
sw $t0 -804($sp)
lw $s1 -804($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -808($sp)
lw $t1 -808($sp)
addi $t0 $t1 0
sw $t0 -812($sp)
lw $t1 -812($sp)
move $t0 $t1
sw $t0 -816($sp)
lw $s1 -816($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -820($sp)
lw $t1 -820($sp)
addi $t0 $t1 0
sw $t0 -824($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -828($sp)
lw $t1 -828($sp)
addi $t0 $t1 0
sw $t0 -832($sp)
lw $t0 -824($sp)
lw $t1 -832($sp)
bgt $t0 $t1 label19
li $v0 4
la $a0 str1
syscall
label19:
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -836($sp)
lw $t1 -836($sp)
addi $t0 $t1 0
sw $t0 -840($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -844($sp)
lw $t1 -844($sp)
addi $t0 $t1 0
sw $t0 -848($sp)
lw $t0 -840($sp)
lw $t1 -848($sp)
bne $t0 $t1 label20
li $v0 4
la $a0 str2
syscall
label20:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -852($sp)
lw $t1 -852($sp)
addi $t0 $t1 0
sw $t0 -856($sp)
lw $t1 -856($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -860($sp)
lw $t1 -860($sp)
addi $t0 $t1 0
sw $t0 -864($sp)
lw $t1 -864($sp)
move $t0 $t1
sw $t0 -4($fp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -868($sp)
lw $t1 -868($sp)
addi $t0 $t1 0
sw $t0 -872($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -876($sp)
lw $t1 -876($sp)
addi $t0 $t1 0
sw $t0 -880($sp)
lw $t0 -872($sp)
lw $t1 -880($sp)
beq $t0 $t1 label21
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -884($sp)
lw $t1 -884($sp)
addi $t0 $t1 0
sw $t0 -888($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -892($sp)
lw $t1 -892($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -896($sp)
lw $t1 -888($sp)
lw $t2 -896($sp)
sub $t0 $t1 $t2
sw $t0 -900($sp)
lw $t0 -900($sp)
li $t1 0
bne $t0 $t1 label23
label24:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -904($sp)
lw $t1 -904($sp)
addi $t0 $t1 0
sw $t0 -908($sp)
li $t1 1
li $t2 30
mul $t0 $t1 $t2
sw $t0 -912($sp)
lw $t1 -912($sp)
addi $t0 $t1 0
sw $t0 -916($sp)
lw $t0 -908($sp)
lw $t1 -916($sp)
bge $t0 $t1 label25
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -920($sp)
lw $t1 -920($sp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -924($sp)
lw $t1 -924($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -928($sp)
lw $t1 -928($sp)
addi $t0 $t1 0
sw $t0 -932($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -936($sp)
lw $t1 -932($sp)
lw $t2 -936($sp)
sub $t0 $t1 $t2
sw $t0 -940($sp)
lw $t0 -940($sp)
li $t1 -1
bne $t0 $t1 label27
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -944($sp)
lw $t1 -944($sp)
addi $t0 $t1 0
sw $t0 -948($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -952($sp)
lw $t1 -948($sp)
lw $t2 -952($sp)
add $t0 $t1 $t2
sw $t0 -956($sp)
lw $t1 -956($sp)
move $t0 $t1
sw $t0 -0($fp)
j label26
label27:
lw $t0 -940($sp)
li $t1 0
bne $t0 $t1 label28
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -960($sp)
lw $t1 -960($sp)
addi $t0 $t1 0
sw $t0 -964($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -968($sp)
lw $t1 -964($sp)
lw $t2 -968($sp)
add $t0 $t1 $t2
sw $t0 -972($sp)
lw $t1 -972($sp)
move $t0 $t1
sw $t0 -0($fp)
j label26
label28:
label26:
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -976($sp)
lw $t1 -976($sp)
addi $t0 $t1 0
sw $t0 -980($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -984($sp)
lw $t1 -980($sp)
lw $t2 -984($sp)
add $t0 $t1 $t2
sw $t0 -988($sp)
lw $t1 -988($sp)
move $t0 $t1
sw $t0 -4($fp)
j label24
label25:
j label22
label23:
li $t1 1
li $t2 -1
mul $t0 $t1 $t2
sw $t0 -992($sp)
lw $t1 -992($sp)
addi $t0 $t1 0
sw $t0 -996($sp)
lw $t1 -996($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
li $t2 -1
mul $t0 $t1 $t2
sw $t0 -1000($sp)
lw $t1 -1000($sp)
addi $t0 $t1 0
sw $t0 -1004($sp)
lw $t1 -1004($sp)
move $t0 $t1
sw $t0 -4($fp)
label22:
label21:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -1008($sp)
lw $t1 -1008($sp)
addi $t0 $t1 0
sw $t0 -1012($sp)
lw $t1 -1012($sp)
move $t0 $t1
sw $t0 -1016($sp)
lw $s1 -1016($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -1020($sp)
lw $t1 -1020($sp)
addi $t0 $t1 0
sw $t0 -1024($sp)
lw $t1 -1024($sp)
move $t0 $t1
sw $t0 -1028($sp)
lw $s1 -1028($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -1032($sp)
lw $t1 -1032($sp)
addi $t0 $t1 0
sw $t0 -1036($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -1040($sp)
lw $t1 -1036($sp)
lw $t2 -1040($sp)
sub $t0 $t1 $t2
sw $t0 -1044($sp)
lw $t0 -1044($sp)
li $t1 0
beq $t0 $t1 label29
li $v0 4
la $a0 str3
syscall
label29:
li $t1 1
li $t2 -1
mul $t0 $t1 $t2
sw $t0 -1048($sp)
lw $t1 -1048($sp)
addi $t0 $t1 0
sw $t0 -1052($sp)
lw $t1 -1052($sp)
move $t0 $t1
sw $t0 0($t9)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -1056($sp)
lw $t1 -1056($sp)
addi $t0 $t1 0
sw $t0 -1060($sp)
lw $t1 -1060($sp)
move $t0 $t1
sw $t0 4($t9)
label30:
jr $ra
label31:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t0 -4($sp)
li $t1 -1
bne $t0 $t1 label33
label34:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
li $t2 20
mul $t0 $t1 $t2
sw $t0 -12($sp)
lw $t1 -12($sp)
addi $t0 $t1 0
sw $t0 -16($sp)
li $t1 1
li $t2 30
mul $t0 $t1 $t2
sw $t0 -20($sp)
lw $t1 -20($sp)
li $t2 5
div $t0 $t1 $t2
sw $t0 -24($sp)
lw $t1 -16($sp)
lw $t2 -24($sp)
add $t0 $t1 $t2
sw $t0 -28($sp)
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
lw $t0 -28($sp)
lw $t1 -36($sp)
bge $t0 $t1 label35
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -40($sp)
addi $t0 $t1 0
sw $t0 -44($sp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -48($sp)
lw $t1 -48($sp)
addi $t0 $t1 0
sw $t0 -52($sp)
lw $t0 -44($sp)
lw $t1 -52($sp)
bgt $t0 $t1 label36
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -56($sp)
lw $t1 -56($sp)
addi $t0 $t1 0
sw $t0 -60($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -64($sp)
lw $t1 -60($sp)
lw $t2 -64($sp)
add $t0 $t1 $t2
sw $t0 -68($sp)
lw $t1 -68($sp)
move $t0 $t1
sw $t0 -0($fp)
label36:
j label34
label35:
j label32
label33:
lw $t0 -4($sp)
li $t1 0
bne $t0 $t1 label37
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -72($sp)
lw $t1 -72($sp)
addi $t0 $t1 0
sw $t0 -76($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -80($sp)
lw $t1 -80($sp)
li $t2 -1
mul $t0 $t1 $t2
sw $t0 -84($sp)
lw $t1 -76($sp)
lw $t2 -84($sp)
sub $t0 $t1 $t2
sw $t0 -88($sp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -92($sp)
lw $t1 -92($sp)
addi $t0 $t1 0
sw $t0 -96($sp)
lw $t0 -88($sp)
lw $t1 -96($sp)
bne $t0 $t1 label38
label39:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -100($sp)
lw $t1 -100($sp)
addi $t0 $t1 0
sw $t0 -104($sp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -108($sp)
lw $t1 -108($sp)
addi $t0 $t1 0
sw $t0 -112($sp)
lw $t0 -104($sp)
lw $t1 -112($sp)
bgt $t0 $t1 label40
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -116($sp)
lw $t1 -116($sp)
addi $t0 $t1 0
sw $t0 -120($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -124($sp)
lw $t1 -120($sp)
lw $t2 -124($sp)
add $t0 $t1 $t2
sw $t0 -128($sp)
li $t1 1
lw $t2 -128($sp)
mul $t0 $t1 $t2
sw $t0 -132($sp)
lw $t1 -132($sp)
li $t2 -2
mul $t0 $t1 $t2
sw $t0 -136($sp)
lw $t1 -136($sp)
addi $t0 $t1 0
sw $t0 -140($sp)
lw $t1 -140($sp)
move $t0 $t1
sw $t0 -0($fp)
j label39
label40:
label38:
j label32
label37:
lw $t0 -4($sp)
li $t1 1
bne $t0 $t1 label41
li $t1 1
li $t2 -233
mul $t0 $t1 $t2
sw $t0 -144($sp)
lw $t1 -144($sp)
addi $t0 $t1 0
sw $t0 -148($sp)
lw $t1 -148($sp)
move $t0 $t1
sw $t0 -0($fp)
j label32
label41:
li $t1 1
li $t2 233
mul $t0 $t1 $t2
sw $t0 -152($sp)
lw $t1 -152($sp)
addi $t0 $t1 0
sw $t0 -156($sp)
lw $t1 -156($sp)
move $t0 $t1
sw $t0 -0($fp)
label32:
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -160($sp)
lw $t1 -160($sp)
addi $t0 $t1 0
sw $t0 -164($sp)
lw $t0 -164($sp)
li $t1 97
bne $t0 $t1 label43
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -168($sp)
lw $t1 -168($sp)
addi $t0 $t1 0
sw $t0 -172($sp)
lw $t1 -172($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label43:
lw $t0 -164($sp)
li $t1 65
bne $t0 $t1 label44
li $t1 1
li $t2 65
mul $t0 $t1 $t2
sw $t0 -176($sp)
lw $t1 -176($sp)
addi $t0 $t1 0
sw $t0 -180($sp)
lw $t1 -180($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label44:
lw $t0 -164($sp)
li $t1 57
bne $t0 $t1 label45
li $t1 1
li $t2 57
mul $t0 $t1 $t2
sw $t0 -184($sp)
lw $t1 -184($sp)
addi $t0 $t1 0
sw $t0 -188($sp)
lw $t1 -188($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label45:
lw $t0 -164($sp)
li $t1 95
bne $t0 $t1 label46
li $t1 1
li $t2 95
mul $t0 $t1 $t2
sw $t0 -192($sp)
lw $t1 -192($sp)
addi $t0 $t1 0
sw $t0 -196($sp)
lw $t1 -196($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label46:
lw $t0 -164($sp)
li $t1 43
bne $t0 $t1 label47
li $t1 1
li $t2 43
mul $t0 $t1 $t2
sw $t0 -200($sp)
lw $t1 -200($sp)
addi $t0 $t1 0
sw $t0 -204($sp)
lw $t1 -204($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label47:
lw $t0 -164($sp)
li $t1 42
bne $t0 $t1 label48
li $t1 1
li $t2 42
mul $t0 $t1 $t2
sw $t0 -208($sp)
lw $t1 -208($sp)
addi $t0 $t1 0
sw $t0 -212($sp)
lw $t1 -212($sp)
move $t0 $t1
sw $t0 -4($fp)
j label42
label48:
li $t1 1
li $t2 119
mul $t0 $t1 $t2
sw $t0 -216($sp)
lw $t1 -216($sp)
addi $t0 $t1 0
sw $t0 -220($sp)
lw $t1 -220($sp)
move $t0 $t1
sw $t0 -4($fp)
label42:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -224($sp)
lw $t1 -224($sp)
addi $t0 $t1 0
sw $t0 -228($sp)
lw $t0 -228($sp)
li $t1 0
bne $t0 $t1 label50
j label49
label50:
label49:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -232($sp)
lw $t1 -232($sp)
addi $t0 $t1 0
sw $t0 -236($sp)
lw $t1 -236($sp)
move $t0 $t1
sw $t0 -240($sp)
lw $s1 -240($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -244($sp)
lw $t1 -244($sp)
addi $t0 $t1 0
sw $t0 -248($sp)
lw $t1 -248($sp)
move $t0 $t1
sw $t0 -252($sp)
lw $s1 -252($sp)
li $v0 11
move $a0 $s1
syscall
li $t1 1
li $t2 -2
mul $t0 $t1 $t2
sw $t0 -256($sp)
lw $t1 -256($sp)
addi $t0 $t1 0
sw $t0 -260($sp)
lw $t1 -260($sp)
move $t0 $t1
sw $t0 0($t9)
li $t1 1
li $t2 98
mul $t0 $t1 $t2
sw $t0 -264($sp)
lw $t1 -264($sp)
addi $t0 $t1 0
sw $t0 -268($sp)
lw $t1 -268($sp)
move $t0 $t1
sw $t0 4($t9)
label51:
jr $ra
label52:
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $v0 $t1
jr $ra
label53:
jr $ra
label54:
li $t1 1
li $t2 114
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $v0 $t1
jr $ra
label55:
jr $ra
label56:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t0 -4($sp)
li $t1 1
bne $t0 $t1 label58
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label58:
lw $t0 -4($sp)
li $t1 2
bne $t0 $t1 label59
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -16($sp)
lw $t1 -16($sp)
addi $t0 $t1 0
sw $t0 -20($sp)
lw $t1 -20($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label59:
lw $t0 -4($sp)
li $t1 3
bne $t0 $t1 label60
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -24($sp)
lw $t1 -24($sp)
addi $t0 $t1 0
sw $t0 -28($sp)
lw $t1 -28($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label60:
lw $t0 -4($sp)
li $t1 4
bne $t0 $t1 label61
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
lw $t1 -36($sp)
move $t0 $t1
sw $t0 -20($fp)
j label57
label61:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -40($sp)
addi $t0 $t1 0
sw $t0 -44($sp)
lw $t1 -44($sp)
move $t0 $t1
sw $t0 -20($fp)
label57:
li $t1 1
lw $t2 -20($fp)
mul $t0 $t1 $t2
sw $t0 -48($sp)
lw $t1 -48($sp)
addi $t0 $t1 0
sw $t0 -52($sp)
lw $t1 -52($sp)
move $v0 $t1
jr $ra
label62:
jr $ra
label63:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t0 -4($sp)
li $t1 1
bne $t0 $t1 label65
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $v0 $t1
jr $ra
j label64
label65:
lw $t0 -4($sp)
li $t1 2
bne $t0 $t1 label66
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -16($sp)
lw $t1 -16($sp)
addi $t0 $t1 0
sw $t0 -20($sp)
lw $t1 -20($sp)
move $v0 $t1
jr $ra
j label64
label66:
lw $t0 -4($sp)
li $t1 3
bne $t0 $t1 label67
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -24($sp)
lw $t1 -24($sp)
addi $t0 $t1 0
sw $t0 -28($sp)
lw $t1 -28($sp)
move $v0 $t1
jr $ra
j label64
label67:
lw $t0 -4($sp)
li $t1 4
bne $t0 $t1 label68
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
lw $t1 -36($sp)
move $v0 $t1
jr $ra
j label64
label68:
li $t1 1
li $t2 48
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -40($sp)
addi $t0 $t1 0
sw $t0 -44($sp)
lw $t1 -44($sp)
move $v0 $t1
jr $ra
label64:
label69:
jr $ra
label70:
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
li $t1 1
li $t2 -1
mul $t0 $t1 $t2
sw $t0 -16($sp)
li $t1 0
lw $t2 -16($sp)
sub $t0 $t1 $t2
sw $t0 -20($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -24($sp)
li $t1 0
lw $t2 -24($sp)
sub $t0 $t1 $t2
sw $t0 -28($sp)
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
sw $ra -40($sp)
sw $fp -44($sp)
addi $fp $sp -48
addi $sp $fp -0
jal label54
addi $sp $fp 48
lw $fp -44($sp)
lw $ra -40($sp)
move $t0 $v0
sw $t0 -40($sp)
li $t1 1
lw $t2 -40($sp)
mul $t0 $t1 $t2
sw $t0 -44($sp)
lw $t1 -44($sp)
addi $t0 $t1 0
sw $t0 -48($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -52($sp)
lw $t1 -48($sp)
lw $t2 -52($sp)
sub $t0 $t1 $t2
sw $t0 -56($sp)
li $t1 1
lw $t2 -56($sp)
mul $t0 $t1 $t2
sw $t0 -60($sp)
lw $t1 -60($sp)
addi $t0 $t1 0
sw $t0 -64($sp)
sw $ra -68($sp)
sw $fp -72($sp)
addi $fp $sp -76
# para
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -20($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -28($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -36($sp)
move $t0 $t1
sw $t0 -12($fp)
# para
lw $t1 -64($sp)
move $t0 $t1
sw $t0 -16($fp)
addi $sp $fp -24
jal label56
addi $sp $fp 76
lw $fp -72($sp)
lw $ra -68($sp)
move $t0 $v0
sw $t0 -68($sp)
li $t1 1
lw $t2 -68($sp)
mul $t0 $t1 $t2
sw $t0 -72($sp)
li $t1 1
li $t2 99
mul $t0 $t1 $t2
sw $t0 -76($sp)
lw $t1 -76($sp)
addi $t0 $t1 0
sw $t0 -80($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -84($sp)
lw $t1 -80($sp)
lw $t2 -84($sp)
sub $t0 $t1 $t2
sw $t0 -88($sp)
lw $t1 -72($sp)
lw $t2 -88($sp)
mul $t0 $t1 $t2
sw $t0 -92($sp)
lw $t1 -92($sp)
li $t2 2
div $t0 $t1 $t2
sw $t0 -96($sp)
lw $t1 -4($sp)
lw $t2 -96($sp)
add $t0 $t1 $t2
sw $t0 -100($sp)
lw $t1 -100($sp)
move $t0 $t1
sw $t0 -0($fp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -104($sp)
lw $t1 -104($sp)
li $t2 4
div $t0 $t1 $t2
sw $t0 -108($sp)
lw $t1 -108($sp)
addi $t0 $t1 0
sw $t0 -112($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -116($sp)
lw $t1 -112($sp)
lw $t2 -116($sp)
add $t0 $t1 $t2
sw $t0 -120($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -124($sp)
lw $t1 -120($sp)
lw $t2 -124($sp)
sub $t0 $t1 $t2
sw $t0 -128($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -132($sp)
lw $t1 -128($sp)
lw $t2 -132($sp)
sub $t0 $t1 $t2
sw $t0 -136($sp)
li $t1 1
li $t2 -2
mul $t0 $t1 $t2
sw $t0 -140($sp)
li $t1 0
lw $t2 -140($sp)
sub $t0 $t1 $t2
sw $t0 -144($sp)
lw $t0 -136($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t1 $fp $t2
lw $t0 -144($sp)
sw $t0 0($t1)
li $t1 1
li $t2 -2
mul $t0 $t1 $t2
sw $t0 -148($sp)
lw $t1 -148($sp)
addi $t0 $t1 0
sw $t0 -152($sp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -156($sp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -160($sp)
lw $t1 -160($sp)
addi $t0 $t1 0
sw $t0 -164($sp)
lw $t0 -164($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -168($sp)
lw $t1 -156($sp)
lw $t2 -168($sp)
div $t0 $t1 $t2
sw $t0 -172($sp)
lw $t1 -152($sp)
lw $t2 -172($sp)
add $t0 $t1 $t2
sw $t0 -176($sp)
sw $ra -180($sp)
sw $fp -184($sp)
addi $fp $sp -188
addi $sp $fp -0
jal label52
addi $sp $fp 188
lw $fp -184($sp)
lw $ra -180($sp)
move $t0 $v0
sw $t0 -180($sp)
li $t1 1
lw $t2 -180($sp)
mul $t0 $t1 $t2
sw $t0 -184($sp)
lw $t1 -176($sp)
lw $t2 -184($sp)
add $t0 $t1 $t2
sw $t0 -188($sp)
li $t1 1
li $t2 11
mul $t0 $t1 $t2
sw $t0 -192($sp)
lw $t1 -188($sp)
lw $t2 -192($sp)
sub $t0 $t1 $t2
sw $t0 -196($sp)
sw $ra -200($sp)
sw $fp -204($sp)
addi $fp $sp -208
addi $sp $fp -0
jal label52
addi $sp $fp 208
lw $fp -204($sp)
lw $ra -200($sp)
move $t0 $v0
sw $t0 -200($sp)
li $t1 1
lw $t2 -200($sp)
mul $t0 $t1 $t2
sw $t0 -204($sp)
li $t1 0
lw $t2 -204($sp)
sub $t0 $t1 $t2
sw $t0 -208($sp)
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -212($sp)
sw $ra -216($sp)
sw $fp -220($sp)
addi $fp $sp -224
addi $sp $fp -0
jal label54
addi $sp $fp 224
lw $fp -220($sp)
lw $ra -216($sp)
move $t0 $v0
sw $t0 -216($sp)
li $t1 1
lw $t2 -216($sp)
mul $t0 $t1 $t2
sw $t0 -220($sp)
lw $t1 -220($sp)
addi $t0 $t1 0
sw $t0 -224($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -228($sp)
lw $t1 -224($sp)
lw $t2 -228($sp)
sub $t0 $t1 $t2
sw $t0 -232($sp)
lw $t1 -212($sp)
lw $t2 -232($sp)
mul $t0 $t1 $t2
sw $t0 -236($sp)
lw $t1 -236($sp)
addi $t0 $t1 0
sw $t0 -240($sp)
li $t1 1
li $t2 4
mul $t0 $t1 $t2
sw $t0 -244($sp)
lw $t1 -244($sp)
addi $t0 $t1 0
sw $t0 -248($sp)
li $t1 1
li $t2 98
mul $t0 $t1 $t2
sw $t0 -252($sp)
li $t1 0
lw $t2 -252($sp)
sub $t0 $t1 $t2
sw $t0 -256($sp)
li $t1 1
li $t2 99
mul $t0 $t1 $t2
sw $t0 -260($sp)
lw $t1 -256($sp)
lw $t2 -260($sp)
add $t0 $t1 $t2
sw $t0 -264($sp)
sw $ra -268($sp)
sw $fp -272($sp)
addi $fp $sp -276
addi $sp $fp -0
jal label52
addi $sp $fp 276
lw $fp -272($sp)
lw $ra -268($sp)
move $t0 $v0
sw $t0 -268($sp)
li $t1 1
lw $t2 -268($sp)
mul $t0 $t1 $t2
sw $t0 -272($sp)
lw $t1 -272($sp)
addi $t0 $t1 0
sw $t0 -276($sp)
li $t1 1
li $t2 10
mul $t0 $t1 $t2
sw $t0 -280($sp)
lw $t1 -280($sp)
addi $t0 $t1 0
sw $t0 -284($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -288($sp)
lw $t1 -288($sp)
addi $t0 $t1 0
sw $t0 -292($sp)
li $t1 1
lw $t2 -292($sp)
mul $t0 $t1 $t2
sw $t0 -296($sp)
lw $t1 -296($sp)
addi $t0 $t1 0
sw $t0 -300($sp)
sw $ra -304($sp)
sw $fp -308($sp)
addi $fp $sp -312
# para
lw $t1 -248($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -264($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -276($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -284($sp)
move $t0 $t1
sw $t0 -12($fp)
# para
lw $t1 -300($sp)
move $t0 $t1
sw $t0 -16($fp)
addi $sp $fp -24
jal label56
addi $sp $fp 312
lw $fp -308($sp)
lw $ra -304($sp)
move $t0 $v0
sw $t0 -304($sp)
li $t1 1
lw $t2 -304($sp)
mul $t0 $t1 $t2
sw $t0 -308($sp)
lw $t1 -240($sp)
lw $t2 -308($sp)
add $t0 $t1 $t2
sw $t0 -312($sp)
li $t1 1
lw $t2 -312($sp)
mul $t0 $t1 $t2
sw $t0 -316($sp)
lw $t1 -208($sp)
lw $t2 -316($sp)
add $t0 $t1 $t2
sw $t0 -320($sp)
lw $t0 -196($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t1 $fp $t2
lw $t0 -320($sp)
sw $t0 0($t1)
li $t1 1
li $t2 255
mul $t0 $t1 $t2
sw $t0 -324($sp)
li $t1 0
lw $t2 -324($sp)
sub $t0 $t1 $t2
sw $t0 -328($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -332($sp)
lw $t1 -332($sp)
addi $t0 $t1 0
sw $t0 -336($sp)
lw $t0 -336($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -340($sp)
li $t1 1
lw $t2 -340($sp)
mul $t0 $t1 $t2
sw $t0 -344($sp)
lw $t1 -328($sp)
lw $t2 -344($sp)
add $t0 $t1 $t2
sw $t0 -348($sp)
li $t1 1
li $t2 98
mul $t0 $t1 $t2
sw $t0 -352($sp)
lw $t1 -352($sp)
li $t2 2
mul $t0 $t1 $t2
sw $t0 -356($sp)
lw $t1 -348($sp)
lw $t2 -356($sp)
add $t0 $t1 $t2
sw $t0 -360($sp)
li $t1 1
li $t2 196
mul $t0 $t1 $t2
sw $t0 -364($sp)
lw $t1 -360($sp)
lw $t2 -364($sp)
sub $t0 $t1 $t2
sw $t0 -368($sp)
li $t1 1
li $t2 98
mul $t0 $t1 $t2
sw $t0 -372($sp)
li $t1 0
lw $t2 -372($sp)
sub $t0 $t1 $t2
sw $t0 -376($sp)
li $t1 1
li $t2 99
mul $t0 $t1 $t2
sw $t0 -380($sp)
lw $t1 -376($sp)
lw $t2 -380($sp)
add $t0 $t1 $t2
sw $t0 -384($sp)
lw $t0 -368($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t1 $fp $t2
lw $t0 -384($sp)
sw $t0 0($t1)
sw $ra -388($sp)
sw $fp -392($sp)
addi $fp $sp -396
addi $sp $fp -0
jal label54
addi $sp $fp 396
lw $fp -392($sp)
lw $ra -388($sp)
move $t0 $v0
sw $t0 -388($sp)
li $t1 1
lw $t2 -388($sp)
mul $t0 $t1 $t2
sw $t0 -392($sp)
lw $t1 -392($sp)
addi $t0 $t1 0
sw $t0 -396($sp)
lw $t1 -396($sp)
move $t0 $t1
sw $t0 -16($fp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -400($sp)
lw $t1 -400($sp)
addi $t0 $t1 0
sw $t0 -404($sp)
li $t1 1
li $t2 4
mul $t0 $t1 $t2
sw $t0 -408($sp)
lw $t1 -408($sp)
addi $t0 $t1 0
sw $t0 -412($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -416($sp)
lw $t1 -416($sp)
addi $t0 $t1 0
sw $t0 -420($sp)
sw $ra -424($sp)
sw $fp -428($sp)
addi $fp $sp -432
addi $sp $fp -0
jal label54
addi $sp $fp 432
lw $fp -428($sp)
lw $ra -424($sp)
move $t0 $v0
sw $t0 -424($sp)
li $t1 1
lw $t2 -424($sp)
mul $t0 $t1 $t2
sw $t0 -428($sp)
lw $t1 -428($sp)
addi $t0 $t1 0
sw $t0 -432($sp)
sw $ra -436($sp)
sw $fp -440($sp)
addi $fp $sp -444
addi $sp $fp -0
jal label54
addi $sp $fp 444
lw $fp -440($sp)
lw $ra -436($sp)
move $t0 $v0
sw $t0 -436($sp)
li $t1 1
lw $t2 -436($sp)
mul $t0 $t1 $t2
sw $t0 -440($sp)
lw $t1 -440($sp)
addi $t0 $t1 0
sw $t0 -444($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -448($sp)
lw $t1 -448($sp)
addi $t0 $t1 0
sw $t0 -452($sp)
sw $ra -456($sp)
sw $fp -460($sp)
addi $fp $sp -464
# para
lw $t1 -412($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -420($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -432($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -444($sp)
move $t0 $t1
sw $t0 -12($fp)
# para
lw $t1 -452($sp)
move $t0 $t1
sw $t0 -16($fp)
addi $sp $fp -20
jal label63
addi $sp $fp 464
lw $fp -460($sp)
lw $ra -456($sp)
move $t0 $v0
sw $t0 -456($sp)
li $t1 1
lw $t2 -456($sp)
mul $t0 $t1 $t2
sw $t0 -460($sp)
lw $t1 -460($sp)
addi $t0 $t1 0
sw $t0 -464($sp)
lw $t0 -404($sp)
sll $t2 $t0 2
addi $t2 $t2 20
sub $t1 $fp $t2
lw $t0 -464($sp)
sw $t0 0($t1)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -468($sp)
lw $t1 -468($sp)
addi $t0 $t1 0
sw $t0 -472($sp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -476($sp)
lw $t1 -476($sp)
addi $t0 $t1 0
sw $t0 -480($sp)
lw $t0 -480($sp)
sll $t2 $t0 2
addi $t2 $t2 20
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -484($sp)
li $t1 1
lw $t2 -484($sp)
mul $t0 $t1 $t2
sw $t0 -488($sp)
lw $t1 -488($sp)
addi $t0 $t1 0
sw $t0 -492($sp)
lw $t0 -472($sp)
sll $t2 $t0 2
addi $t2 $t2 20
sub $t1 $fp $t2
lw $t0 -492($sp)
sw $t0 0($t1)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -496($sp)
lw $t1 -496($sp)
addi $t0 $t1 0
sw $t0 -500($sp)
li $t1 1
li $t2 120
mul $t0 $t1 $t2
sw $t0 -504($sp)
lw $t1 -504($sp)
addi $t0 $t1 0
sw $t0 -508($sp)
lw $t0 -500($sp)
sll $t2 $t0 2
addi $t2 $t2 20
sub $t1 $fp $t2
lw $t0 -508($sp)
sw $t0 0($t1)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -512($sp)
lw $t1 -512($sp)
addi $t0 $t1 0
sw $t0 -516($sp)
lw $t1 -516($sp)
move $t0 $t1
sw $t0 -520($sp)
lw $s1 -520($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -524($sp)
lw $t1 -524($sp)
addi $t0 $t1 0
sw $t0 -528($sp)
lw $t0 -528($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -532($sp)
li $t1 1
lw $t2 -532($sp)
mul $t0 $t1 $t2
sw $t0 -536($sp)
lw $t1 -536($sp)
addi $t0 $t1 0
sw $t0 -540($sp)
lw $t1 -540($sp)
move $t0 $t1
sw $t0 -544($sp)
lw $s1 -544($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -548($sp)
lw $t1 -548($sp)
addi $t0 $t1 0
sw $t0 -552($sp)
lw $t0 -552($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -556($sp)
li $t1 1
lw $t2 -556($sp)
mul $t0 $t1 $t2
sw $t0 -560($sp)
lw $t1 -560($sp)
addi $t0 $t1 0
sw $t0 -564($sp)
lw $t1 -564($sp)
move $t0 $t1
sw $t0 -568($sp)
lw $s1 -568($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -572($sp)
lw $t1 -572($sp)
addi $t0 $t1 0
sw $t0 -576($sp)
lw $t0 -576($sp)
sll $t2 $t0 2
addi $t2 $t2 4
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -580($sp)
li $t1 1
lw $t2 -580($sp)
mul $t0 $t1 $t2
sw $t0 -584($sp)
lw $t1 -584($sp)
addi $t0 $t1 0
sw $t0 -588($sp)
lw $t1 -588($sp)
move $t0 $t1
sw $t0 -592($sp)
lw $s1 -592($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -596($sp)
lw $t1 -596($sp)
addi $t0 $t1 0
sw $t0 -600($sp)
lw $t1 -600($sp)
move $t0 $t1
sw $t0 -604($sp)
lw $s1 -604($sp)
li $v0 11
move $a0 $s1
syscall
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -608($sp)
lw $t1 -608($sp)
addi $t0 $t1 0
sw $t0 -612($sp)
lw $t0 -612($sp)
sll $t2 $t0 2
addi $t2 $t2 20
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -616($sp)
li $t1 1
lw $t2 -616($sp)
mul $t0 $t1 $t2
sw $t0 -620($sp)
lw $t1 -620($sp)
addi $t0 $t1 0
sw $t0 -624($sp)
lw $t1 -624($sp)
move $t0 $t1
sw $t0 -628($sp)
lw $s1 -628($sp)
li $v0 11
move $a0 $s1
syscall
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -632($sp)
lw $t1 -632($sp)
addi $t0 $t1 0
sw $t0 -636($sp)
lw $t0 -636($sp)
sll $t2 $t0 2
addi $t2 $t2 20
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -640($sp)
li $t1 1
lw $t2 -640($sp)
mul $t0 $t1 $t2
sw $t0 -644($sp)
lw $t1 -644($sp)
addi $t0 $t1 0
sw $t0 -648($sp)
lw $t1 -648($sp)
move $t0 $t1
sw $t0 -652($sp)
lw $s1 -652($sp)
li $v0 11
move $a0 $s1
syscall
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -656($sp)
lw $t1 -656($sp)
addi $t0 $t1 0
sw $t0 -660($sp)
lw $t0 -660($sp)
sll $t2 $t0 2
addi $t2 $t2 20
sub $t0 $fp $t2
lw $t0 0($t0)
sw $t0 -664($sp)
li $t1 1
lw $t2 -664($sp)
mul $t0 $t1 $t2
sw $t0 -668($sp)
lw $t1 -668($sp)
addi $t0 $t1 0
sw $t0 -672($sp)
lw $t1 -672($sp)
move $t0 $t1
sw $t0 -676($sp)
lw $s1 -676($sp)
li $v0 11
move $a0 $s1
syscall
li $t1 1
li $t2 -3
mul $t0 $t1 $t2
sw $t0 -680($sp)
lw $t1 -680($sp)
addi $t0 $t1 0
sw $t0 -684($sp)
lw $t1 -684($sp)
move $t0 $t1
sw $t0 0($t9)
li $t1 1
li $t2 99
mul $t0 $t1 $t2
sw $t0 -688($sp)
lw $t1 -688($sp)
addi $t0 $t1 0
sw $t0 -692($sp)
lw $t1 -692($sp)
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
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -16($sp)
lw $s1 -16($sp)
li $v0 1
move $a0 $s1
syscall
li $v0 4
la $a0 str6
syscall
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -20($sp)
lw $t1 -20($sp)
addi $t0 $t1 0
sw $t0 -24($sp)
lw $t1 -24($sp)
move $t0 $t1
sw $t0 -28($sp)
lw $s1 -28($sp)
li $v0 11
move $a0 $s1
syscall
li $t1 1
li $t2 -4
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
lw $t1 -36($sp)
move $t0 $t1
sw $t0 -8($fp)
li $t1 1
li $t2 100
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -40($sp)
addi $t0 $t1 0
sw $t0 -44($sp)
lw $t1 -44($sp)
move $t0 $t1
sw $t0 -12($fp)
label73:
jr $ra
label74:
label75:
jr $ra
label76:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -16($fp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -16($sp)
lw $t1 -16($sp)
addi $t0 $t1 0
sw $t0 -20($sp)
lw $t0 -12($sp)
lw $t1 -20($sp)
bge $t0 $t1 label77
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -24($sp)
lw $t1 -24($sp)
addi $t0 $t1 0
sw $t0 -28($sp)
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
lw $t0 -28($sp)
lw $t1 -36($sp)
blt $t0 $t1 label78
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -40($sp)
addi $t0 $t1 0
sw $t0 -44($sp)
lw $t1 -44($sp)
move $t0 $t1
sw $t0 -16($fp)
label78:
label77:
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -48($sp)
lw $t1 -48($sp)
addi $t0 $t1 0
sw $t0 -52($sp)
lw $t1 -52($sp)
move $v0 $t1
jr $ra
label79:
jr $ra
label80:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -16($fp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -16($sp)
lw $t1 -16($sp)
addi $t0 $t1 0
sw $t0 -20($sp)
lw $t0 -12($sp)
lw $t1 -20($sp)
bge $t0 $t1 label81
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -24($sp)
lw $t1 -24($sp)
addi $t0 $t1 0
sw $t0 -28($sp)
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
lw $t0 -28($sp)
lw $t1 -36($sp)
bgt $t0 $t1 label82
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -40($sp)
addi $t0 $t1 0
sw $t0 -44($sp)
lw $t1 -44($sp)
move $t0 $t1
sw $t0 -16($fp)
label82:
label81:
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -48($sp)
lw $t1 -48($sp)
addi $t0 $t1 0
sw $t0 -52($sp)
lw $t1 -52($sp)
move $v0 $t1
jr $ra
label83:
jr $ra
label84:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 -8($fp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $t0 $t1
sw $t0 -12($fp)
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -16($sp)
lw $t1 -16($sp)
addi $t0 $t1 0
sw $t0 -20($sp)
lw $t0 -20($sp)
sll $t2 $t0 2
addi $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -24($sp)
li $t1 1
lw $t2 -24($sp)
mul $t0 $t1 $t2
sw $t0 -28($sp)
lw $t1 -28($sp)
addi $t0 $t1 0
sw $t0 -32($sp)
lw $t1 -32($sp)
move $t0 $t1
sw $t0 -16($fp)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -36($sp)
lw $t1 -36($sp)
addi $t0 $t1 0
sw $t0 -40($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -44($sp)
lw $t1 -44($sp)
addi $t0 $t1 0
sw $t0 -48($sp)
lw $t0 -40($sp)
lw $t1 -48($sp)
blt $t0 $t1 label85
jr $ra
label85:
label86:
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -52($sp)
lw $t1 -52($sp)
addi $t0 $t1 0
sw $t0 -56($sp)
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -60($sp)
lw $t1 -60($sp)
addi $t0 $t1 0
sw $t0 -64($sp)
lw $t0 -56($sp)
lw $t1 -64($sp)
bge $t0 $t1 label87
label88:
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -68($sp)
lw $t1 -68($sp)
addi $t0 $t1 0
sw $t0 -72($sp)
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -76($sp)
lw $t1 -76($sp)
addi $t0 $t1 0
sw $t0 -80($sp)
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -84($sp)
lw $t1 -84($sp)
addi $t0 $t1 0
sw $t0 -88($sp)
lw $t0 -88($sp)
sll $t2 $t0 2
addi $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -92($sp)
li $t1 1
lw $t2 -92($sp)
mul $t0 $t1 $t2
sw $t0 -96($sp)
lw $t1 -96($sp)
addi $t0 $t1 0
sw $t0 -100($sp)
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -104($sp)
lw $t1 -104($sp)
addi $t0 $t1 0
sw $t0 -108($sp)
sw $ra -112($sp)
sw $fp -116($sp)
addi $fp $sp -120
# para
lw $t1 -72($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -80($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -100($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -108($sp)
move $t0 $t1
sw $t0 -12($fp)
addi $sp $fp -20
jal label76
addi $sp $fp 120
lw $fp -116($sp)
lw $ra -112($sp)
move $t0 $v0
sw $t0 -112($sp)
li $t1 1
lw $t2 -112($sp)
mul $t0 $t1 $t2
sw $t0 -116($sp)
lw $t1 -116($sp)
addi $t0 $t1 0
sw $t0 -120($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -124($sp)
lw $t1 -124($sp)
addi $t0 $t1 0
sw $t0 -128($sp)
lw $t0 -120($sp)
lw $t1 -128($sp)
bne $t0 $t1 label89
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -132($sp)
lw $t1 -132($sp)
addi $t0 $t1 0
sw $t0 -136($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -140($sp)
lw $t1 -136($sp)
lw $t2 -140($sp)
sub $t0 $t1 $t2
sw $t0 -144($sp)
lw $t1 -144($sp)
move $t0 $t1
sw $t0 -12($fp)
j label88
label89:
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -148($sp)
lw $t1 -148($sp)
addi $t0 $t1 0
sw $t0 -152($sp)
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -156($sp)
lw $t1 -156($sp)
addi $t0 $t1 0
sw $t0 -160($sp)
lw $t0 -160($sp)
sll $t2 $t0 2
addi $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -164($sp)
li $t1 1
lw $t2 -164($sp)
mul $t0 $t1 $t2
sw $t0 -168($sp)
lw $t1 -168($sp)
addi $t0 $t1 0
sw $t0 -172($sp)
lw $t0 -152($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -172($sp)
sw $t0 0($t1)
label90:
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -176($sp)
lw $t1 -176($sp)
addi $t0 $t1 0
sw $t0 -180($sp)
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -184($sp)
lw $t1 -184($sp)
addi $t0 $t1 0
sw $t0 -188($sp)
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -192($sp)
lw $t1 -192($sp)
addi $t0 $t1 0
sw $t0 -196($sp)
lw $t0 -196($sp)
sll $t2 $t0 2
addi $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -200($sp)
li $t1 1
lw $t2 -200($sp)
mul $t0 $t1 $t2
sw $t0 -204($sp)
lw $t1 -204($sp)
addi $t0 $t1 0
sw $t0 -208($sp)
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -212($sp)
lw $t1 -212($sp)
addi $t0 $t1 0
sw $t0 -216($sp)
sw $ra -220($sp)
sw $fp -224($sp)
addi $fp $sp -228
# para
lw $t1 -180($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -188($sp)
move $t0 $t1
sw $t0 -4($fp)
# para
lw $t1 -208($sp)
move $t0 $t1
sw $t0 -8($fp)
# para
lw $t1 -216($sp)
move $t0 $t1
sw $t0 -12($fp)
addi $sp $fp -20
jal label80
addi $sp $fp 228
lw $fp -224($sp)
lw $ra -220($sp)
move $t0 $v0
sw $t0 -220($sp)
li $t1 1
lw $t2 -220($sp)
mul $t0 $t1 $t2
sw $t0 -224($sp)
lw $t1 -224($sp)
addi $t0 $t1 0
sw $t0 -228($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -232($sp)
lw $t1 -232($sp)
addi $t0 $t1 0
sw $t0 -236($sp)
lw $t0 -228($sp)
lw $t1 -236($sp)
bne $t0 $t1 label91
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -240($sp)
lw $t1 -240($sp)
addi $t0 $t1 0
sw $t0 -244($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -248($sp)
lw $t1 -244($sp)
lw $t2 -248($sp)
add $t0 $t1 $t2
sw $t0 -252($sp)
lw $t1 -252($sp)
move $t0 $t1
sw $t0 -8($fp)
j label90
label91:
li $t1 1
lw $t2 -12($fp)
mul $t0 $t1 $t2
sw $t0 -256($sp)
lw $t1 -256($sp)
addi $t0 $t1 0
sw $t0 -260($sp)
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -264($sp)
lw $t1 -264($sp)
addi $t0 $t1 0
sw $t0 -268($sp)
lw $t0 -268($sp)
sll $t2 $t0 2
addi $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -272($sp)
li $t1 1
lw $t2 -272($sp)
mul $t0 $t1 $t2
sw $t0 -276($sp)
lw $t1 -276($sp)
addi $t0 $t1 0
sw $t0 -280($sp)
lw $t0 -260($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -280($sp)
sw $t0 0($t1)
j label86
label87:
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -284($sp)
lw $t1 -284($sp)
addi $t0 $t1 0
sw $t0 -288($sp)
li $t1 1
lw $t2 -16($fp)
mul $t0 $t1 $t2
sw $t0 -292($sp)
lw $t1 -292($sp)
addi $t0 $t1 0
sw $t0 -296($sp)
lw $t0 -288($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -296($sp)
sw $t0 0($t1)
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -300($sp)
lw $t1 -300($sp)
addi $t0 $t1 0
sw $t0 -304($sp)
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -308($sp)
lw $t1 -308($sp)
addi $t0 $t1 0
sw $t0 -312($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -316($sp)
lw $t1 -312($sp)
lw $t2 -316($sp)
sub $t0 $t1 $t2
sw $t0 -320($sp)
sw $ra -324($sp)
sw $fp -328($sp)
addi $fp $sp -332
# para
lw $t1 -304($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -320($sp)
move $t0 $t1
sw $t0 -4($fp)
addi $sp $fp -20
jal label84
addi $sp $fp 332
lw $fp -328($sp)
lw $ra -324($sp)
li $t1 1
lw $t2 -8($fp)
mul $t0 $t1 $t2
sw $t0 -324($sp)
lw $t1 -324($sp)
addi $t0 $t1 0
sw $t0 -328($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -332($sp)
lw $t1 -328($sp)
lw $t2 -332($sp)
add $t0 $t1 $t2
sw $t0 -336($sp)
li $t1 1
lw $t2 -4($fp)
mul $t0 $t1 $t2
sw $t0 -340($sp)
lw $t1 -340($sp)
addi $t0 $t1 0
sw $t0 -344($sp)
sw $ra -348($sp)
sw $fp -352($sp)
addi $fp $sp -356
# para
lw $t1 -336($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -344($sp)
move $t0 $t1
sw $t0 -4($fp)
addi $sp $fp -20
jal label84
addi $sp $fp 356
lw $fp -352($sp)
lw $ra -348($sp)
jr $ra
label92:
jr $ra
label93:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
li $t1 1
li $t2 5
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
lw $t0 -4($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -12($sp)
sw $t0 0($t1)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -16($sp)
lw $t1 -16($sp)
addi $t0 $t1 0
sw $t0 -20($sp)
li $t1 1
li $t2 8
mul $t0 $t1 $t2
sw $t0 -24($sp)
lw $t1 -24($sp)
addi $t0 $t1 0
sw $t0 -28($sp)
lw $t0 -20($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -28($sp)
sw $t0 0($t1)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -32($sp)
lw $t1 -32($sp)
addi $t0 $t1 0
sw $t0 -36($sp)
li $t1 1
li $t2 3
mul $t0 $t1 $t2
sw $t0 -40($sp)
lw $t1 -40($sp)
addi $t0 $t1 0
sw $t0 -44($sp)
lw $t0 -36($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -44($sp)
sw $t0 0($t1)
li $t1 1
li $t2 3
mul $t0 $t1 $t2
sw $t0 -48($sp)
lw $t1 -48($sp)
addi $t0 $t1 0
sw $t0 -52($sp)
li $t1 1
li $t2 6
mul $t0 $t1 $t2
sw $t0 -56($sp)
lw $t1 -56($sp)
addi $t0 $t1 0
sw $t0 -60($sp)
lw $t0 -52($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -60($sp)
sw $t0 0($t1)
li $t1 1
li $t2 4
mul $t0 $t1 $t2
sw $t0 -64($sp)
lw $t1 -64($sp)
addi $t0 $t1 0
sw $t0 -68($sp)
li $t1 1
li $t2 4
mul $t0 $t1 $t2
sw $t0 -72($sp)
lw $t1 -72($sp)
addi $t0 $t1 0
sw $t0 -76($sp)
lw $t0 -68($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -76($sp)
sw $t0 0($t1)
li $t1 1
li $t2 5
mul $t0 $t1 $t2
sw $t0 -80($sp)
lw $t1 -80($sp)
addi $t0 $t1 0
sw $t0 -84($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -88($sp)
lw $t1 -88($sp)
addi $t0 $t1 0
sw $t0 -92($sp)
lw $t0 -84($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -92($sp)
sw $t0 0($t1)
li $t1 1
li $t2 6
mul $t0 $t1 $t2
sw $t0 -96($sp)
lw $t1 -96($sp)
addi $t0 $t1 0
sw $t0 -100($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -104($sp)
lw $t1 -104($sp)
addi $t0 $t1 0
sw $t0 -108($sp)
lw $t0 -100($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -108($sp)
sw $t0 0($t1)
li $t1 1
li $t2 7
mul $t0 $t1 $t2
sw $t0 -112($sp)
lw $t1 -112($sp)
addi $t0 $t1 0
sw $t0 -116($sp)
li $t1 1
li $t2 7
mul $t0 $t1 $t2
sw $t0 -120($sp)
lw $t1 -120($sp)
addi $t0 $t1 0
sw $t0 -124($sp)
lw $t0 -116($sp)
sll $t2 $t0 2
addi $t2 $t2 268501160
add $t1 $0 $t2
lw $t0 -124($sp)
sw $t0 0($t1)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -128($sp)
lw $t1 -128($sp)
addi $t0 $t1 0
sw $t0 -132($sp)
li $t1 1
li $t2 7
mul $t0 $t1 $t2
sw $t0 -136($sp)
lw $t1 -136($sp)
addi $t0 $t1 0
sw $t0 -140($sp)
sw $ra -144($sp)
sw $fp -148($sp)
addi $fp $sp -152
# para
lw $t1 -132($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -140($sp)
move $t0 $t1
sw $t0 -4($fp)
addi $sp $fp -20
jal label84
addi $sp $fp 152
lw $fp -148($sp)
lw $ra -144($sp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -144($sp)
lw $t1 -144($sp)
addi $t0 $t1 0
sw $t0 -148($sp)
lw $t1 -148($sp)
move $t0 $t1
sw $t0 -0($fp)
label94:
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -152($sp)
lw $t1 -152($sp)
addi $t0 $t1 0
sw $t0 -156($sp)
li $t1 1
li $t2 8
mul $t0 $t1 $t2
sw $t0 -160($sp)
lw $t1 -160($sp)
addi $t0 $t1 0
sw $t0 -164($sp)
lw $t0 -156($sp)
lw $t1 -164($sp)
bge $t0 $t1 label95
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -168($sp)
lw $t1 -168($sp)
addi $t0 $t1 0
sw $t0 -172($sp)
lw $t0 -172($sp)
sll $t2 $t0 2
addi $t0 $t2 268501160
lw $t0 0($t0)
sw $t0 -176($sp)
li $t1 1
lw $t2 -176($sp)
mul $t0 $t1 $t2
sw $t0 -180($sp)
lw $t1 -180($sp)
addi $t0 $t1 0
sw $t0 -184($sp)
lw $t1 -184($sp)
move $t0 $t1
sw $t0 -188($sp)
lw $s1 -188($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -192($sp)
lw $t1 -192($sp)
addi $t0 $t1 0
sw $t0 -196($sp)
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -200($sp)
lw $t1 -196($sp)
lw $t2 -200($sp)
add $t0 $t1 $t2
sw $t0 -204($sp)
lw $t1 -204($sp)
move $t0 $t1
sw $t0 -0($fp)
j label94
label95:
li $t1 1
li $t2 -5
mul $t0 $t1 $t2
sw $t0 -208($sp)
lw $t1 -208($sp)
addi $t0 $t1 0
sw $t0 -212($sp)
lw $t1 -212($sp)
move $t0 $t1
sw $t0 0($t9)
li $t1 1
li $t2 101
mul $t0 $t1 $t2
sw $t0 -216($sp)
lw $t1 -216($sp)
addi $t0 $t1 0
sw $t0 -220($sp)
lw $t1 -220($sp)
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
li $t1 1
lw $t2 -0($fp)
mul $t0 $t1 $t2
sw $t0 -4($sp)
lw $t1 -4($sp)
addi $t0 $t1 0
sw $t0 -8($sp)
lw $t0 -8($sp)
li $t1 0
bne $t0 $t1 label99
sw $ra -12($sp)
sw $fp -16($sp)
addi $fp $sp -20
addi $sp $fp -8
jal label1
addi $sp $fp 20
lw $fp -16($sp)
lw $ra -12($sp)
j label98
label99:
lw $t0 -8($sp)
li $t1 1
bne $t0 $t1 label100
li $t1 1
li $t2 1
mul $t0 $t1 $t2
sw $t0 -12($sp)
lw $t1 -12($sp)
addi $t0 $t1 0
sw $t0 -16($sp)
li $t1 1
li $t2 97
mul $t0 $t1 $t2
sw $t0 -20($sp)
lw $t1 -20($sp)
addi $t0 $t1 0
sw $t0 -24($sp)
sw $ra -28($sp)
sw $fp -32($sp)
addi $fp $sp -36
# para
lw $t1 -16($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -24($sp)
move $t0 $t1
sw $t0 -4($fp)
addi $sp $fp -8
jal label31
addi $sp $fp 36
lw $fp -32($sp)
lw $ra -28($sp)
li $t1 1
li $t2 -1
mul $t0 $t1 $t2
sw $t0 -28($sp)
lw $t1 -28($sp)
addi $t0 $t1 0
sw $t0 -32($sp)
li $t1 1
li $t2 43
mul $t0 $t1 $t2
sw $t0 -36($sp)
lw $t1 -36($sp)
addi $t0 $t1 0
sw $t0 -40($sp)
sw $ra -44($sp)
sw $fp -48($sp)
addi $fp $sp -52
# para
lw $t1 -32($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -40($sp)
move $t0 $t1
sw $t0 -4($fp)
addi $sp $fp -8
jal label31
addi $sp $fp 52
lw $fp -48($sp)
lw $ra -44($sp)
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -44($sp)
lw $t1 -44($sp)
addi $t0 $t1 0
sw $t0 -48($sp)
li $t1 1
li $t2 95
mul $t0 $t1 $t2
sw $t0 -52($sp)
lw $t1 -52($sp)
addi $t0 $t1 0
sw $t0 -56($sp)
sw $ra -60($sp)
sw $fp -64($sp)
addi $fp $sp -68
# para
lw $t1 -48($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -56($sp)
move $t0 $t1
sw $t0 -4($fp)
addi $sp $fp -8
jal label31
addi $sp $fp 68
lw $fp -64($sp)
lw $ra -60($sp)
li $t1 1
li $t2 2
mul $t0 $t1 $t2
sw $t0 -60($sp)
lw $t1 -60($sp)
addi $t0 $t1 0
sw $t0 -64($sp)
li $t1 1
li $t2 57
mul $t0 $t1 $t2
sw $t0 -68($sp)
lw $t1 -68($sp)
addi $t0 $t1 0
sw $t0 -72($sp)
sw $ra -76($sp)
sw $fp -80($sp)
addi $fp $sp -84
# para
lw $t1 -64($sp)
move $t0 $t1
sw $t0 -0($fp)
# para
lw $t1 -72($sp)
move $t0 $t1
sw $t0 -4($fp)
addi $sp $fp -8
jal label31
addi $sp $fp 84
lw $fp -80($sp)
lw $ra -76($sp)
j label98
label100:
lw $t0 -8($sp)
li $t1 2
bne $t0 $t1 label101
sw $ra -76($sp)
sw $fp -80($sp)
addi $fp $sp -84
addi $sp $fp -32
jal label70
addi $sp $fp 84
lw $fp -80($sp)
lw $ra -76($sp)
j label98
label101:
lw $t0 -8($sp)
li $t1 3
bne $t0 $t1 label102
sw $ra -76($sp)
sw $fp -80($sp)
addi $fp $sp -84
addi $sp $fp -16
jal label72
addi $sp $fp 84
lw $fp -80($sp)
lw $ra -76($sp)
j label98
label102:
lw $t0 -8($sp)
li $t1 4
bne $t0 $t1 label103
sw $ra -76($sp)
sw $fp -80($sp)
addi $fp $sp -84
addi $sp $fp -4
jal label93
addi $sp $fp 84
lw $fp -80($sp)
lw $ra -76($sp)
j label98
label103:
label98:
li $t1 1
lw $t2 0($t9)
mul $t0 $t1 $t2
sw $t0 -76($sp)
lw $t1 -76($sp)
addi $t0 $t1 0
sw $t0 -80($sp)
lw $t1 -80($sp)
move $t0 $t1
sw $t0 -84($sp)
lw $s1 -84($sp)
li $v0 1
move $a0 $s1
syscall
li $t1 1
lw $t2 4($t9)
mul $t0 $t1 $t2
sw $t0 -88($sp)
lw $t1 -88($sp)
addi $t0 $t1 0
sw $t0 -92($sp)
lw $t1 -92($sp)
move $t0 $t1
sw $t0 -96($sp)
lw $s1 -96($sp)
li $v0 11
move $a0 $s1
syscall
label104:
jr $ra
main:
li $t1 1
li $t2 0
mul $t0 $t1 $t2
sw $t0 -0($sp)
lw $t1 -0($sp)
addi $t0 $t1 0
sw $t0 -4($sp)
lw $t1 -4($sp)
move $t0 $t1
sw $t0 0($t9)
li $t1 1
li $t2 95
mul $t0 $t1 $t2
sw $t0 -8($sp)
lw $t1 -8($sp)
addi $t0 $t1 0
sw $t0 -12($sp)
lw $t1 -12($sp)
move $t0 $t1
sw $t0 4($t9)
sw $ra -16($sp)
sw $fp -20($sp)
addi $fp $sp -24
addi $sp $fp -4
jal label97
addi $sp $fp 24
lw $fp -20($sp)
lw $ra -16($sp)
sw $ra -16($sp)
sw $fp -20($sp)
addi $fp $sp -24
addi $sp $fp -0
jal label74
addi $sp $fp 24
lw $fp -20($sp)
lw $ra -16($sp)
label105:
