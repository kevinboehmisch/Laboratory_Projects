;   Labor 1 - Test program for LCD driver
;
;   Computerarchitektur
;   (C) 2019-2022 J. Friedrich, W. Zimmermann, R. Keller
;   Hochschule Esslingen
;
;   Author:   	   Kevin Böhmisch
; Export symbols
        XDEF Entry, main

; Import symbols
        XREF __SEG_END_SSTACK                   ; End of stack
        XREF initLCD, writeLine, delay_10ms     ; LCD functions
        XREF initLED
        XREF setLED
        XREF delay_0_5sec
        XREF decToASCII 
        XREF hexToASCII
        

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION
i:      DS.W    1           ; Counter variable
asciiDec: DS.B 7            ; Buffer for decimal ASCII string
asciiHex: DS.B 7            ; Buffer for hexadecimal ASCII string

; ROM: Constant data
.const: SECTION
MSG1:   dc.b " Mach mal eine",0
MSG2:   dc.b " kleine Pause", 0
msgA:   DC.B "ABCDEFGHIJKLMnopqrstuvwxyz1234567890", 0
msgB:   DC.B "is this OK?", 0
msgC:   DC.B "Keep texts short!", 0
msgD:   DC.B "Oh yeah!", 0

; ROM: Code section
.init:  SECTION

main:
Entry:
        ; Initialize stack pointer and enable interrupts
        LDS  #__SEG_END_SSTACK          ; Load end of stack address
        CLI                             ; Enable interrupts
        LDD #$1122 
        LDX #$3344 
        PSHD 
        PSHX 
        PULB 
        PULA 
        PULY