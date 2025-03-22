;thermometer
; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; export symbols
        XDEF initThermo
        XDEF updateThermo
        XDEF finalTemp
        
; import symbols
        XREF initADC
        XREF convertADC
        XREF writeLine
   
; RAM: Variable data section
.data: SECTION

rawTemp: ds.b 7
finalTemp: ds.b 7 ;correctly formatted string

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

 
initThermo:
        JSR initADC  
        RTS
  

; Public interface function: updateThermo ... reads and converts Analog value of thermometer
; string to LCD 
; Parameter:
; Y ... pointer points to adress where result string is to be stored
; Return: -
; Registers: X points to result string address
updateThermo:                 ;once per second convertADC is called
          PSHB
          PSHY
          PSHX
          
          LDY #finalTemp
          JSR convertADC
          
          LDX #finalTemp
          ;LDAB  #0
          ;JSR writeLine      ;(only for debugging)

          PULX
          PULY
          PULB
         
          RTS
  

  