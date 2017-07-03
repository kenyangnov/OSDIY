; haribote-os
; TAB=4

;		ORG		0xc200			; 指明程序的装载地址（通过上一节的计算得到）
fin:
		HLT
		JMP		fin
