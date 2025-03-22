;led

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; export symbols
        XDEF initLED, setLED, getLED, toggleLED  
        
; RAM: Variable data section
.data: SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

;**************************************************************
; Function: initLED
; Description: Initializes the LEDs by configuring the necessary ports.
; Parameters: None
; Returns: None
;**************************************************************
initLED:
  BSET DDRJ, #2            ; Set bit 2 of DDRJ to configure it as output (for controlling LEDs)
  BCLR PTJ, #2             ; Clear bit 2 of PTJ to enable LEDs

  MOVB #$0F, DDRP          ; Set lower 4 bits of DDRP as outputs
  MOVB #$0F, PTP           ; Turn on lower 4 LEDs on port P

  MOVB #$FF, DDRB          ; Configure all pins of PORTB as outputs (for LEDs)
  MOVB #$00, PORTB         ; Turn off all LEDs by clearing PORTB
  RTS                      ; Return from subroutine

;**************************************************************
; Function: setLED
; Description: Sets the LEDs (PORTB) to the value in accumulator B.
; Parameters: B - Value to display on LEDs.
; Returns: None
;**************************************************************
setLED:
  STAB PORTB               ; Store the value from accumulator B into PORTB
  RTS                      ; Return from subroutine

;**************************************************************
; Function: getLED
; Description: Retrieves the current state of PORTB (LEDs).
; Parameters: None
; Returns: D - Current state of PORTB.
;**************************************************************
getLED:
  LDD PORTB                ; Load the value of PORTB into register D
  RTS                      ; Return from subroutine

;**************************************************************
; Function: toggleLED
; Description: Toggles the LEDs (PORTB) based on the current state.
; Parameters: None
; Returns: None
;**************************************************************
toggleLED:
  EORB PORTB               ; XOR the current value of PORTB with accumulator B to toggle bits
  STAB PORTB               ; Store the toggled value back into PORTB
  RTS                      ; Return from subroutine

