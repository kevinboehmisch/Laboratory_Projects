;adc

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; export symbols
        XDEF initADC, convertADC 

; import symbols
        XREF decToASCII
        
; RAM: Variable data section
.data: SECTION

rawTemp: ds.b 7 ;raw formatted string

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

;**************************************************************
; Public interface function: initADC ... Initialize ACD (called
; once in main.c before using the ADC) 
; Parameter: -
; Return: -
; Registers: Unchanged (when function returns
;**************************************************************
initADC:
      MOVB #$C0, ATD0CTL2 ; Enable ATD, no interrupt
      MOVB #$08, ATD0CTL3 ; Single conversion only
      MOVB #$05, ATD0CTL4 ; 10 bit, 2 MHz ATD0 clock
      RTS
  


; Public interface function: convertADC ... Convert analog values 0...1023 into the corresponding temperature -30°C .. 70°C
; string to LCD 
; Parameter:
; Y ... pointer points to adress of result string
; Return: correctly formated result string stored in Register Y
; Registers: Y points to result string address

convertADC:
      MOVB #$87, ATD0CTL5       ; Start conversion on channel 7

wait1:
      ;Wait for End of Conversion (EOC), busy waiting:
      BRCLR ATD0STAT0, #$80, wait1
      LDD ATD0DR0               ; Read conversion result à D 
      ;LDD #100                 ;(for testing and debugging with different values) 





; Calculation: Convert the 10-bit analog value in register D, (range 0...1023) to a temperature value in the range -30°C to 70°C.              
; 1. Multiply the ADC result by 100 to maintain precision.
; 2. Divide the result by the maximum ADC range (1023) to normalize it.
; 3. Subtract 30 to adjust the range to -30°C ... 70°C.


      PSHY                     ; Save Y register on the stack (preserve its value)
      PSHX                     ; Save X register on the stack (preserve its value)
        
      LDY #100                 ; Load 100 into Y (used to multiply by 100 for precision)
      EMULS                    ; Multiply D (ADC value) by Y (100). Result is stored in Y:D.
      
      LDX #1023                ; Load the maximum ADC range (1023) into X
      EDIV                     ; Divide Y:D (high precision result) by X (1023).
                               ; Quotient (normalized value) is stored in D, remainder in X.
      
      TFR Y, D                 ; Transfer the result from Y to D (keep only the integer part)
      SUBD #30                 ; Subtract 30 to map the range to -30°C ... 70°C.
      
      PULX                     ; Restore the original value of X from the stack
      PULY                     ; Restore the original value of Y from the stack

  
  


      ;convert to ASCII String (raw format)
      LDX #rawTemp
      JSR decToASCII
         
        
      ;LDY #result_string
      JSR getFinalTemp
      nop

      ;LDY #result_string
      RTS 

   
  
  
; get the right format for the string e.g -30oC  
getFinalTemp: 

      LDAA #' '  
      STAA 1, Y+
      
      LDAA 1, X+  ;copy sign
      STAA 1, Y+
        
      LDAA 3, +X  ;copy first digit
      STAA 1, Y+
        
      LDAA 1, +X  ;second digit
      STAA 1, Y+
        
      
        
      LDAA #'o'
      STAA 1, Y+
        
      LDAA #'C'
      STAA 1, Y+
        
      LDAA #0    ;null terminator
      STAA 1, Y+
      RTS
