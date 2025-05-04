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

        ; Delay for power stabilization
        JSR  delay_10ms                 ; 10ms delay
        JSR  delay_10ms                 ; Another 10ms delay

        ; Initialize LCD and LEDs
        JSR  initLCD                    ; Initialize LCD
        JSR  initLED                    ; Initialize LEDs
        
        ; Initialize counter variable i
        LDD #$7FF0                      ; Load initial value into D
        STD i                           ; Store D in counter variable i

loop:
        ; Display i on LEDs
        LDD i                           ; Load the lower 8 bits of i into D
        JSR setLED                      ; Output value on LEDs

        ; Display decimal value of i on LCD line 0
        LDD     i                       ; Load i into D
        LDX     #asciiDec               ; Load target address for decimal ASCII string
        JSR     decToASCII              ; Convert i to decimal ASCII string
        LDX     #asciiDec               ; Pointer to the converted string
        LDAB    #0                      ; Select line 0
        JSR     writeLine               ; Write string to LCD line 0

        ; Display hexadecimal value of i on LCD line 1
        LDD     i                       ; Load i into D
        LDX     #asciiHex               ; Load target address for hexadecimal ASCII string
        JSR     hexToASCII              ; Convert i to hexadecimal ASCII string
        LDX     #asciiHex               ; Pointer to the converted string
        LDAB    #1                      ; Select line 1
        JSR     writeLine               ; Write string to LCD line 1

        ; 0.5 second delay
        JSR     delay_0_5sec            ; Call delay subroutine

        ; Check if buttons are pressed and adjust i accordingly
        BRCLR PTH, #$01, button0pressed ; Check button 0
        BRCLR PTH, #$02, button1pressed ; Check button 1
        BRCLR PTH, #$04, button2pressed ; Check button 2
        BRCLR PTH, #$08, button3pressed ; Check button 3

        ; Default: Increment counter by 1
        LDD     i                       ; Load current value of i into D
        ADDD    #1                      ; Increment i by 1
        STD     i                       ; Store new value back in i
        BRA     loop                    ; Repeat the loop

button0pressed:
        ; Increment i by 16
        LDD i                           ; Load current value of i into D
        ADDD #16                        ; Increment by 16
        STD i                           ; Store result back in i
        BRA loop                        ; Return to loop

button1pressed:
        ; Increment i by 10
        LDD i                           ; Load current value of i into D
        ADDD #10                        ; Increment by 10
        STD i                           ; Store result back in i
        BRA loop                        ; Return to loop

button2pressed:
        ; Decrement i by 16
        LDD i                           ; Load current value of i into D
        SUBD #16                        ; Decrement by 16
        STD i                           ; Store result back in i
        BRA loop                        ; Return to loop

button3pressed:
        ; Decrement i by 10
        LDD i                           ; Load current value of i into D
        SUBD #10                        ; Decrement by 10
        STD i                           ; Store result back in i
        BRA loop                        ; Return to loop

back:   
      BRA back                          ; Infinite loop to prevent program exit
