; clock.asm
; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Export symbols
        XDEF initClock, tickClock 
        XDEF checkMode
        XDEF finalTime
        XDEF secs, mins, hrs
        XDEF currentMode


        
; Import symbols
        XREF decToASCII
        XREF writeLine
        XREF toggleLED, setLED
        XREF delay_0_5sec



        
; RAM: Variable data section
.data: SECTION

hrs:        DS.B 1              ; Hours (0-23)
hrsASCII:   DS.B 3              ; Hours (0-23 + NUL)
mins:       DS.B 1              ; Minutes (0-59)
minsASCII:   DS.B 3             ; Minutes (0-59 + NUL)
secs:       DS.B 1              ; Seconds (0-59)
secsASCII:   DS.B 3             ; Seconds (0-59 + NUL)
asciiConversion: DS.B 6         ; Buffer for ASCII conversion (e.g., "00059")
finalTime: DS.B 11              ; Buffer for final string "HH:MM:SS"

pmFlag: DS.B 1                  ; 0 = AM, 1 = PM

currentMode: DS.B 1                 ; 0 = Normal mode, 1 = Set mode 




; ROM: Code section
.init: SECTION

am: DC.B "am", 0     
pm: DC.B "pm", 0     

SELECT12HOURS: EQU 1 ; 1 = 12h Mode, 0 = 24h Mode



;**************************************************************
; Public interface function: initClock ... Initialize the clock
; Purpose: Initializes the clock with default time values (hours, 
;          minutes, seconds) and prepares the clock system.
; Parameters: -
; Return: -
; Registers: Unchanged (when function returns)
;**************************************************************
initClock:
        ; Initialize time
        LDAB #30                      ; Initialize seconds
        STAB secs                     ; Store seconds 

        LDAB #59                      ; Initialize minutes
        STAB mins                     ; Store minutes  

        LDAB #11                      ; Initialize hours
        STAB hrs                      ; Store hours
        
        ; set the flag to 1 for pm
        LDAB #1                       
        STAB pmFlag


        MOVB #0, currentMode
        
        ; convert hours, minutes, seconds from decimal to ASCII
        JSR convertToASCII

        ; Assemble finalTime with converted hours, minutes, seconds strings 
        JSR assembleFinalTime         

        ; Print final time to LCD
        ;JSR printToLCD ;(only used for debugging, replaced with print function in main.c)
        
        RTS
        
        





;**************************************************************
; Public interface function: tickClock ... Increment the clock
; Purpose: Handles time incrementing by one second, checks 
;          for mode transitions, and updates the display.
; Parameters: -
; Return: -
; Registers: Unchanged (when function returns)
;**************************************************************
tickClock:


        ; increment time only in normal mode
        JSR incrementTime      ; Zeit inkrementieren
        JSR updateDisplay      ; Display aktualisieren
        RTS
  
  





;**************************************************************
; Public interface function: checkMode ... Handle mode toggling
; Purpose: Handles user input for toggling between Normal and 
;          Set Modes and updates the mode state accordingly.
; Parameters: -
; Return: -
; Registers: Unchanged (when function returns)
;************************************************************** 

checkMode:
    BRCLR PTH, #$01, switchMode     ; Polling for button 2
    JSR delay_0_5sec

normalMode:                         ; Return if the button hasn't been pressed 
    RTS
    
switchMode:                         ; Otherwise change the mode    
    PSHB
    
    LDAB currentMode                  
    EORB #1               
    STAB currentMode
    
    LDAB #$80                       ; Toggle LED B.7 to show the mode 
    JSR toggleLED
    JSR delay_0_5sec
    
    LDAB currentMode                  
    CMPB #1                         ; Check if the clock has been set to Set Mode 
    
    PULB
     
    BEQ setMode                     ; If yes, enable the Set Mode features
    BRA normalMode
    
   
    
setMode: 
    JSR delay_0_5sec
    
    BRCLR PTH, #$01, switchMode     ; Button polling for incrementing the time
    BRCLR PTH, #$02, incrementHour
    BRCLR PTH, #$04, incrementMinute
    BRCLR PTH, #$08, incrementSecond
  
    BRA setMode                     ; Endless loop until you change the mode again
        
 
 incrementSecond:
    JSR delay_0_5sec
    LDAB secs
    INCB
    CMPB #60
    BNE storeSecond    ; If seconds < 60, skip reset
    CLRB                ; Reset seconds to 0
    STAB secs
    BEQ incrementMinute


; Increment minutes
incrementMinute:
    JSR delay_0_5sec
    LDAB mins
    INCB
    CMPB #60
    BNE storeMinute    ; If minutes < 60, skip reset
    CLRB                ; Reset minutes to 0
    STAB mins
    BEQ incrementHour


; Increment hours
incrementHour:
    JSR delay_0_5sec
    LDAB hrs
    INCB
    ; Implementation of 12 or 24 hour Check
    IF SELECT12HOURS == 1
        ; implementation of AM/PM and 12 to 1 check
        CMPB #12        ; Check if hours reach 12 in 12-hour mode
        BEQ toggleAMPMs  ; change from AM to PM
        CMPB #13
        BEQ resetTimes   ; if overflow reset to 1 in 12-hour mode
        BRA storeHour    
    ELSE
        CMPB #24        ; Check if hours reach 24 in 24-hour mode
        BNE storeHour
        CLRB            ; Reset to 0 after 23
    ENDIF 
    BRA setMode

toggleAMPMs:
    LDAB #12          ; Reset to 1 after 12
    STAB hrs
    LDAA pmFlag    ; load current AM/PM-Flag
    EORA #1          ; Toggle (0 -> 1, 1 -> 0)
    STAA pmFlag    ; safe new ampm flag 
    BRA setMode
    
storeHour:
    STAB hrs
    JSR updateDisplays
    BRA setMode



storeMinute:
    STAB mins
    JSR updateDisplays
    BRA setMode

storeSecond:
    STAB secs
    JSR updateDisplays
    BRA setMode
    
resetTimes:
    LDAB #1          ; Reset to 1 after 12
    STAB hrs
    JSR updateDisplays
    BRA setMode  
    

updateDisplays:   
       JSR convertToASCII     ; Convert time to ASCII
       JSR assembleFinalTime  ; Assemble final time string
       JSR printToLCD         ; Display time on the LCD (only used for debugging, replaced with print function in main.c)       
       RTS        
       
        
 
               
;**************************************************************
; Public interface function: updateDisplay ... Update the clock display
; Purpose: Converts the current time to ASCII and updates the 
;          final time string for display on the LCD.
; Parameters: -
; Return: -
; Registers: Unchanged (when function returns)
;**************************************************************    
updateDisplay:   
       JSR convertToASCII     ; Convert time to ASCII
       JSR assembleFinalTime  ; Assemble final time string
       ;JSR printToLCD         ; Display time on the LCD (only used for debugging, replaced with print function in main.c)       
       RTS    





;**************************************************************
; Public interface function: incrementTime ... Increment the clock time
; Purpose: Handles the logic for incrementing seconds, minutes, 
;          and hours while checking for overflow conditions.
; Parameters: -
; Return: -
; Registers: Unchanged (when function returns)
;**************************************************************    
incrementTime:
    LDAB currentMode
    CMPB #0
    BEQ incrementSeconds
; Increment seconds
incrementSeconds:
    LDAB secs
    INCB
    CMPB #60
    BNE storeSeconds    ; If seconds < 60, skip reset
    CLRB                ; Reset seconds to 0
    STAB secs
    BEQ incrementMinutes



; Increment minutes
incrementMinutes:
    LDAB mins
    INCB
    CMPB #60
    BNE storeMinutes    ; If minutes < 60, skip reset
    CLRB                ; Reset minutes to 0
    STAB mins
    BEQ incrementHours


; Increment hours
incrementHours:
    LDAB hrs
    INCB
    ; Implementation of 12 or 24 hour Check
    IF SELECT12HOURS == 1
        ; implementation of AM/PM and 12 to 1 check
        CMPB #12        ; Check if hours reach 12 in 12-hour mode
        BEQ toggleAMPM  ; change from AM to PM
        CMPB #13
        BEQ resetTime   ; if overflow reset to 1 in 12-hour mode
        BNE storeHours    
    ELSE
        CMPB #24        ; Check if hours reach 24 in 24-hour mode
        BNE storeHours
        CLRB            ; Reset to 0 after 23
    ENDIF



storeHours:
    STAB hrs
    RTS


storeMinutes:
    STAB mins
    RTS

storeSeconds:
    STAB secs
    RTS


resetTime:
    LDAB #1          ; Reset to 1 after 12
    STAB hrs
    
    RTS
    
toggleAMPM:
    LDAB #12          ; Reset to 1 after 12
    STAB hrs
    LDAA pmFlag    ; load current AM/PM-Flag
    EORA #1          ; Toggle (0 -> 1, 1 -> 0)
    STAA pmFlag    ; safe new ampm flag
    
    RTS


    
     
     
;**************************************************************
; Public interface function: convertToASCII ... Convert time to ASCII
; Purpose: Converts binary-encoded time values (hrs, mins, secs)
;          into ASCII strings for display purposes.
; Parameters: -
; Return: -
; Registers: Unchanged (when function returns)
;**************************************************************     
convertToASCII:

        CLRA                          ; CLRA to prevent Bugs with am/pm
        ; Set pointers for asciiConversion and finalTime
        LDY #finalTime              ; Pointer to finalTime
        LDX #asciiConversion          ; Address of asciiConversion

        
        ; Convert hours
        LDAB hrs                      ; Load hours
        JSR decToASCII                ; Convert to ASCII 
        LDY #hrsASCII
        JSR extractLastTwoChars       ; Extract last two characters 

        ; Convert minutes
        LDAB mins                     ; Load minutes
        JSR decToASCII                ; Convert to ASCII 
        LDY #minsASCII
        JSR extractLastTwoChars       ; Extract last two characters 

        ; Convert seconds
        LDAB secs                     ; Load seconds
        JSR decToASCII                ; Convert to ASCII 
        LDY #secsASCII
        JSR extractLastTwoChars       ; Extract last two characters  
        
        RTS      
        
         
                              


;**************************************************************
; Public interface function: extractLastTwoChars ... Extract ASCII characters
; Purpose: Extracts the last two characters of the ASCII 
;          representation of a value (e.g., from "00059" to "59").
; Parameters:
;   X ... Pointer to the ASCII string buffer
;   Y ... Pointer to the output buffer
; Return: -
; Registers: Unchanged (when function returns)
;**************************************************************
extractLastTwoChars:
        PSHB
        PSHA
        PSHX
        PSHY
        
        ; Extract last two chars only
        LDX #asciiConversion+4          ; Skip to the last two characters (00030 -> 30)
        LDAA 0,X                      ; Load the second-last character
        STAA 0,Y                      ; Store it in the final buffer
        LDAA 1,X                      ; Load the last character
        STAA 1,Y                      ; Store it in the final buffer
        INY                           ; Move Y pointer forward by 2 positions
        INY
        CLRA
        STAA  0, Y                    ; terminate with NUL
        PULY
        PULX
        PULA
        PULB
  
        RTS
        
        
 
;**************************************************************
; Public interface function: assembleFinalTime ... Assemble final time string
; Purpose: Constructs the final time string in the format "HH:MM:SS"
;          with optional AM/PM appended in 12-hour mode.
; Parameters: -
; Return: -
; Registers: Unchanged (when function returns)
;**************************************************************       
assembleFinalTime:
        PSHB
        PSHA
        PSHX
        PSHY

        ; Set pointer to finalTime
        LDY #finalTime
        
        ; Add hours to finalTime
        LDX #hrsASCII
        LDAA 0,X                      ; Load first character of hours
        STAA 0,Y                      ; Store in finalTime
        INX
        INY
        LDAA 0,X                      ; Load second character of hours
        STAA 0,Y                      ; Store in finalTime
        INY

        ; Add first colon
        LDAA #':'                     ; Load colon character
        STAA 0,Y                      ; Store colon
        INY

        ; Add minutes to finalTime
        LDX #minsASCII
        LDAA 0,X                      ; Load first character of minutes
        STAA 0,Y                      ; Store in finalTime
        INX
        INY
        LDAA 0,X                      ; Load second character of minutes
        STAA 0,Y                      ; Store in finalTime
        INY

        ; Add second colon
        LDAA #':'                     ; Load colon character
        STAA 0,Y                      ; Store colon
        INY

        ; Add seconds to finalTime
        LDX #secsASCII
        LDAA 0,X                      ; Load first character of seconds
        STAA 0,Y                      ; Store in finalTime
        INX
        INY
        LDAA 0,X                      ; Load second character of seconds
        STAA 0,Y                      ; Store in finalTime
        INY

        ; Add AM/PM in 12-hour mode
        IF SELECT12HOURS == 1
            ; Add space before AM/PM


            ; Check AM/PM flag and add the corresponding string
            LDAA pmFlag
            CMPA #1
            BEQ addPM
            LDX #am
            BRA appendAMPM
addPM:
            LDX #pm
appendAMPM:
            ; Append "am" or "pm"
            LDAA 0,X
            BEQ finalizeString
            STAA 0,Y
            INX
            INY
            BRA appendAMPM
        ENDIF
        
finalizeString:
        ; Null-terminate finalTime
        CLRA                          ; Null terminator
        STAA 0,Y                      ; Add Null terminator

        PULY
        PULX
        PULA
        PULB

        RTS




;**************************************************************
; Public interface function: printToLCD ... Print the time to the LCD
; Purpose: Displays the current `finalTime` string on the LCD. 
;          Used primarily for debugging to visualize intermediate 
;          results or the current clock state. Is replaced by the 
;          C function call to writeLine in the main program
; Parameters:
;   X ... Pointer to the zero-terminated `finalTime` string
;   B ... LCD row number (fixed to row 1)
; Return: -
; Registers: Unchanged (when function returns)     .
;**************************************************************
 printToLCD:
        ; Print final time to LCD
        LDX   #finalTime              ; Load pointer to the finalTime
        LDAB  #1                      ; Select LCD line 1
        JSR   writeLine               ; Write to LCD

        RTS  
        
        
        
        
      


        


               
