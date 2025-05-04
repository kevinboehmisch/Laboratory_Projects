    XDEF  decToASCII
    
    POSITIVE_SIGN:   equ   ' '           ; ASCII code for positive sign (space)
    NEGATIVE_SIGN:   equ   '-'           ; ASCII code for negative sign
    DIGIT_OFFSET:    equ   '0'           ; ASCII offset for digits ('0')

; RAM: Variable data section
.data: SECTION
  val:    DS.W  1                        ; 16-bit storage for the value

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

; Public interface function: decToASCII
;   Converts a 16-bit signed decimal value into a NUL-terminated ASCII string.
;   Supports both positive and negative values.
; Parameters:
;   D: 16-bit signed decimal value to convert
;   X: Pointer to the destination string (RAM location large enough for result)
; Returns: -
; Registers: Unchanged (D, X, Y preserved)
decToASCII:
    PSHA                                ; Save register A on the stack
    PSHY                                ; Save register Y on the stack
    PSHB                                ; Save register B on the stack
    PSHD                                ; Save register D on the stack
    PSHX                                ; Save register X on the stack (start of string)
    
    STD   val                           ; Store the value in "val"
    
    ; Check the sign of "val"
    TFR   D, Y                          ; Transfer D to Y for comparison
    CPY   #0                            ; Compare Y to zero
    BPL   decToASCII_positive           ; If positive, branch to decToASCII_positive
    BRA   decToASCII_negative           ; If negative, branch to decToASCII_negative
    
; Handle positive values
decToASCII_positive:
    LDAA  #POSITIVE_SIGN                ; Load ASCII code for positive sign (space)
    STAA  1, X+                         ; Store the sign at the beginning of the string
    BRA   decToASCII_loop               ; Jump to the conversion loop
    
; Handle negative values
decToASCII_negative:
    LDAA  #NEGATIVE_SIGN                ; Load ASCII code for negative sign
    STAA  1, X+                         ; Store the sign at the beginning of the string
    LDD    val                          ; Load the value from "val"
    COMA                                ; Take 1's complement of A
    COMB                                ; Take 1's complement of B
    ADDD   #1                           ; Add 1 to perform 2's complement
    STD    val                          ; Store the negated value back in "val"

; Conversion loop: Convert value to ASCII
decToASCII_loop:
    LDD   val                           ; Load the current value of "val"
    TFR   X, Y                          ; Backup the pointer to the string
    LDX   #10000                        ; Load the divisor (10000)
    IDIV                                ; Divide D by 10000
    STD   val                           ; Store the remainder back in "val"
    TFR   X, A                          ; Transfer quotient to A
    ADDA  #DIGIT_OFFSET                 ; Convert to ASCII by adding '0'
    STAA  1, Y+                         ; Store the ASCII character in the string
    
    ; Repeat for smaller divisors
    LDD   val
    LDX   #1000
    IDIV
    STD   val
    TFR   X, A
    ADDA  #DIGIT_OFFSET
    STAA  1, Y+
    
    LDD   val
    LDX   #100
    IDIV
    STD   val
    TFR   X, A
    ADDA  #DIGIT_OFFSET
    STAA  1, Y+
    
    LDD   val
    LDX   #10
    IDIV
    STD   val
    TFR   X, A
    ADDA  #DIGIT_OFFSET
    STAA  1, Y+
    
    LDD   val
    ANDB  #$000F                        ; Mask the lower nibble (last digit)
    ADDB  #DIGIT_OFFSET                 ; Convert to ASCII by adding '0'
    STAB  1, Y+                         ; Store the ASCII character in the string

    CLRA                                ; Clear register A
    STAA  0, Y                          ; Append the NUL terminator

    ; Restore registers from the stack
    PULX                                ; Restore X
    PULD                                ; Restore D
    PULB                                ; Restore B
    PULY                                ; Restore Y
    PULA                                ; Restore A
    RTS                                 ; Return from subroutine
