/*  Lab 2 - Main C file for Clock program

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann
    Hochschule Esslingen

    Author:  W.Zimmermann, July 19, 2017
*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


// PLEASE NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:
// Files lcd.asm and ticker.asm do contain SOFTWARE BUGS. Please overwrite them
// with the lcd.asm file, which you bug fixed in lab 1, and with file ticker.asm
// which you bug fixed in prep task 2.1 of this lab 2.
//
// To use decToASCII you must insert file decToASCII from the first lab into
// this project
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// ****************************************************************************
// Function prototype(s)
// Note: Only void Fcn(void) assembler functions can be called from C directly.
//       For non-void functions a C wrapper function is required.
void initTicker(void);
void initClock(void);
void initThermo(void);
void initADC(void);

void tickClock(void);

void checkMode(void);

void updateThermo(void);



// Prototypes and wrapper functions for dec2ASCII (from lab 1)
void decToASCII(void);

void decToASCII_Wrapper(char *txt, int val)
{   asm
    {  	LDX txt
        LDD val
        JSR decToASCII
    }
}

// Prototypes and wrapper functions for LCD driver (from lab 1)
void initLCD(void);
void writeLine(void);

void WriteLine_Wrapper(char *text, char line)
{   asm
    {	LDX  text
        LDAB line
        JSR  writeLine
    }
}

void disableSeven(void){
  
  DDRP = 0xff;
  PTP = 0xff;
}



// *****************************************************************************
// Function: updateLCDContent
// Description: Updates the LCD content every 10 seconds, toggling between
//              displaying the name and a copyright text.
// Parameters: None
// Returns: None
// *****************************************************************************
char lcdTimer = 0;   // Timer for the 10-second interval
char lcdToggle = 0;  // Toggle value: 0 = Name, 1 = "© IT WS2024/2025"

void updateLCDContent(void) {
    lcdTimer++;                  // Increment the timer
    if (lcdTimer >= 10) {        // After 10 seconds...
        lcdTimer = 0;            // Reset the timer
        if (lcdToggle == 0) {    // Toggle between Name and IT text
            lcdToggle = 1;       // Set toggle to 1 if currently 0
        } else {
            lcdToggle = 0;       // Set toggle to 0 if currently 1
        }
    }

    // Update the LCD content based on the toggle value
    if (lcdToggle == 0) {
        WriteLine_Wrapper("Kevin Boehmisch", 0); // First line: Name
    } 
    else {
        WriteLine_Wrapper("© IT WS2024/2025", 0); // First line: IT text
    }
}






// ****************************************************************************

void initLED_C(void)
{   DDRJ_DDRJ1  = 1;	  	// Port J.1 as output
    PTIJ_PTIJ1  = 0;		
    DDRB        = 0xFF;		// Port B as output
    PORTB       = 0x01;
}


// ****************************************************************************

// Global variables
unsigned char clockEvent = 0;

extern char finalTime[11];
extern char finalTemp[7];
extern char currentMode;

extern char currentMode;


// ****************************************************************************
// Function: combineTimeAndTemp
// Description: Combines the time (`finalTime`) and temperature (`finalTemp`) 
//              into a single string (`combinedOutput`) for display on the LCD.
//              The time is left-aligned, and the temperature is right-aligned 
//              with padding spaces in between.
// Parameters: None
// Returns: None
// *****************************************************************************

char combinedOutput[17]; // 16 characters + NUL

void combineTimeAndTemp(void) {
    int i = 0;  // Index for `combinedOutput`
    int j = 0;  // Index for `finalTime`
    int k = 0;  // Index for `finalTemp`
    int timeLength = 0; // Length of `finalTime`
    int tempLength = 0; // Length of `finalTemp`
    int padding; // Number of spaces between time and temperature
    int p;

    // Calculate the length of `finalTime`
    while (finalTime[timeLength] != '\0') {
        timeLength++;
    }

    // Calculate the length of `finalTemp`
    while (finalTemp[tempLength] != '\0') {
        tempLength++;
    }

    // Calculate the padding (spaces) for right alignment
    padding = 16 - timeLength - tempLength;

    // Copy `finalTime` into `combinedOutput`
    while (j < timeLength) {
        combinedOutput[i++] = finalTime[j++];
    }

    // Add padding spaces to align temperature to the right
    for (p = 0; p < padding; p++) {
        combinedOutput[i++] = ' ';
    }

    // Copy `finalTemp` into `combinedOutput`
    while (k < tempLength) {
        combinedOutput[i++] = finalTemp[k++];
    }

    // Null-terminate `combinedOutput`
    combinedOutput[i] = '\0';  // Null-termination
}







void main(void){
    EnableInterrupts;                           // Global interrupt enable

    initLED_C();                    		        // Initialize the LEDs
    initLCD();                    	          	// Initialize the LCD
    initThermo();                               // Initialize thermo and adc
    initClock();                                // Initialize clock
    initTicker();                               // Initialize the time ticker
    disableSeven();

    
    //WriteLine_Wrapper("Clock Template", 0);
    //WriteLine_Wrapper("(C) HE Prof. Z", 1);    



   
    for(;;){                                     // Endless loop
      
      
        if (clockEvent){ 
    	      clockEvent = 0;

            updateThermo();
    	      
    	      
            combineTimeAndTemp();
    	      WriteLine_Wrapper(combinedOutput, 1);
    	      
    	      updateLCDContent();
    	      
    	      tickClock();
    	      
    	      checkMode();
    	             
 
    }
    
}
}