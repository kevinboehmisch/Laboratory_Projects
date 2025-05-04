;   Labor 1 - hexToASCII Conversion Routine
;   Converts a 16-bit hexadecimal number to an ASCII string.

; Export symbols
        XDEF hexToASCII
; Include derivative-specific macros
        INCLUDE 'mc9s12dp256.inc'

;**************************************************************
; RAM: Variable data section
;**************************************************************
.data: SECTION
val:        DS.W    1                   ; Memory space for the 16-bit value

;**************************************************************
; ROM: Constant data
;**************************************************************
.const: SECTION
H2A: DC.B "0123456789ABCDEF"           ; Lookup table for Hex-to-ASCII conversion

;**************************************************************
; ROM: Code section
;**************************************************************
.init: SECTION
hexToASCII:
    ;**********************************************************
    ; Description: Converts a 16-bit value in D to a hex ASCII string.
    ; Input:
    ;   - Register D: 16-bit value to convert.
    ;   - Register X: Pointer to memory where ASCII string is stored.
    ; Output:
    ;   - ASCII string stored in memory pointed to by X.
    ;**********************************************************

    ; Save registers to stack
    PSHX                 ; Save X
    PSHY                 ; Save Y
    PSHA                 ; Save A
    PSHB                 ; Save B
    
    STD     val          ; Store the 16-bit value in `val`

    ; Add "0x" prefix to the result string
    LDAA    #'0'         ; Load ASCII for '0' into A
    STAA    1, X+        ; Store '0' at the first position and increment X
    LDAA    #'x'         ; Load ASCII for 'x' into A
    STAA    1, X+        ; Store 'x' at the second position and increment X

    ; Convert each nibble (4 bits) of the hex value to ASCII and store in the string

    ;**********************************************************
    ; Convert the first nibble (high 4 bits of the high byte)
    ;**********************************************************
    LDY     #H2A         ; Load the address of the ASCII lookup table into Y
    LDD     val          ; Load the 16-bit value into D
    ; Shift D 12 positions to the right to isolate the first nibble
    LSRD                 ; Logical Shift Right
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    ANDB    #$0F         ; Mask all but the lower 4 bits
    ABY                  ; Add offset to the lookup table base
    LDAB    0, Y         ; Load the ASCII character corresponding to the nibble
    STAB    1, X+        ; Store the character in the result string and increment X

    ;**********************************************************
    ; Convert the second nibble (low 4 bits of the high byte)
    ;**********************************************************
    LDY     #H2A         ; Reload the ASCII lookup table base
    LDD     val          ; Reload the 16-bit value
    LSRD                 ; Shift D 8 positions to the right
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    LSRD
    ANDB    #$0F         ; Mask all but the lower 4 bits
    ABY                  ; Add offset to the lookup table base
    LDAB    0, Y         ; Load the ASCII character corresponding to the nibble
    STAB    1, X+        ; Store the character in the result string and increment X

    ;**********************************************************
    ; Convert the third nibble (high 4 bits of the low byte)
    ;**********************************************************
    LDY     #H2A         ; Reload the ASCII lookup table base
    LDD     val          ; Reload the 16-bit value
    LSRD                 ; Shift D 4 positions to the right
    LSRD
    LSRD
    LSRD
    ANDB    #$0F         ; Mask all but the lower 4 bits
    ABY                  ; Add offset to the lookup table base
    LDAB    0, Y         ; Load the ASCII character corresponding to the nibble
    STAB    1, X+        ; Store the character in the result string and increment X

    ;**********************************************************
    ; Convert the fourth nibble (low 4 bits of the low byte)
    ;**********************************************************
    LDY     #H2A         ; Reload the ASCII lookup table base
    LDD     val          ; Reload the 16-bit value
    ANDB    #$0F         ; Mask all but the lower 4 bits
    ABY                  ; Add offset to the lookup table base
    LDAB    0, Y         ; Load the ASCII character corresponding to the nibble
    STAB    1, X+        ; Store the character in the result string and increment X

    ;**********************************************************
    ; Add NULL terminator to the end of the string
    ;**********************************************************
    CLRB                 ; Set B to 0 (ASCII NULL)
    STAB    0, X         ; Store the NULL terminator

    ; Restore registers from stack
    PULB                 ; Restore B
    PULA                 ; Restore A
    PULY                 ; Restore Y
    PULX                 ; Restore X
    
    RTS                  ; Return from subroutine
