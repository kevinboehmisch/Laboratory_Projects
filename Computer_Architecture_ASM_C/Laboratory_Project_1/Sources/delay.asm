; Public interface function: delay_0_5sec
;   Generates an approximate delay of 0.5 seconds.
;   The delay is implemented using nested loops, where the exact time depends on the clock speed.
; Parameters: -
; Returns: -
; Registers: Unchanged

; RAM: Variable data section
.data: SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

; Export the delay_0_5sec function for external use
  XDEF delay_0_5sec

; Function: delay_0_5sec
;   Implements a delay using two nested loops.
;   The number of iterations in the outer and inner loops determines the duration of the delay.
delay_0_5sec:
        LDX #58                   ; Load the outer loop counter with 58
outer_delay:
        LDY #65000                ; Load the inner loop counter with 65000
inner_delay:
        DBNE Y, inner_delay       ; Decrement Y and branch if not zero
        DBNE X, outer_delay       ; Decrement X and branch if not zero
        RTS                       ; Return from subroutine
