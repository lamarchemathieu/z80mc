	.module crt0
	.globl	_main
	.globl _irq_vec
	INT_VEC .equ 0xFFCE
	STACK .equ 0xFF80
	.area	_HEADER (ABS)

	.org 	0x8000
init:
	di
	im 1
	ld hl,#irq
	ld (#INT_VEC),hl
	ei
	call	gsinit
	ld sp, #STACK
	call	_main
	ret

irq:
;ex af,af'
;exx
;ld hl,(#INT_VEC)
;jp (hl)
	di
	push	iy
	call _irq_vec
	pop	iy
	exx
	ex af,af'
	ei
	ret

.area   _HOME
	.area	_CODE
	.area   _INITIALIZER
	.area   _GSINIT
	.area   _GSFINAL
	.area	_DATA
	.area   _INITIALIZED
	.area   _BSEG
	.area   _BSS
	.area   _HEAP

	.area   _GSINIT
gsinit::
	ld      bc, #l__INITIALIZER
	ld      a, b
	or      a, c
	jr      Z, gsinit_next
	ld      de, #s__INITIALIZED
	ld      hl, #s__INITIALIZER
	ldir
gsinit_next:
        .area   _GSFINAL
        ret
