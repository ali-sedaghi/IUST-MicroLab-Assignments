;Ali Sedaghi
;97521378
; dip switch on = slower
; dip switch off = faster

.include "m32def.inc"
	;Init stack pointer
	LDI		R16,HIGH(RAMEND)
	OUT		SPH,R16
	LDI		R16,LOW(RAMEND)
	OUT		SPL,R16
	

	;Set port A as input to read dip switch
	LDI		R16,0x00
	OUT		DDRA,R16


	;Set port B as output
	LDI		R16,0xFF
	OUT		DDRB,R16


	;Starting point
	LDI		R16,0x01

UPDOWN:
	OUT		PORTB,R16
	CALL	DELAY
	LSL		R16
	CPI		R16,0
	BRNE	UPDOWN
	LDI		R16,0x40

DOWNUP:
	OUT		PORTB,R16
	CALL	DELAY
	LSR		R16
	CPI		R16,0
	BRNE	DOWNUP
	LDI		R16,0x02
	JMP		UPDOWN	

DELAY:
	;Read dip switch and store IT
	IN		R17,PINA
	NEG		R17
L1:	MOV		R18,R17
L2:	MOV		R19,R17
L3:	DEC		R19
	BRNE	L3
	DEC		R18
	BRNE	L2
	DEC		R17
	BRNE	L1
	RET






