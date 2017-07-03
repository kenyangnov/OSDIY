; haribote-os
; TAB=4

		ORG		0xc200			; 指明装载地址

		MOV		AL,0x13			; 设置VGA显卡模式，320*200*8位彩色
		MOV		AH,0x00
		INT		0x10
fin:
		HLT
		JMP		fin
