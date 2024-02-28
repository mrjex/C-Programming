/*
    --   ---   --   ---   --   ---   --   ---   --   ---   --   ---   --   ---   --   ---
    
    - Joel Mattsson's Timer Interrupt Algorithm (2024-03-16)
    
    - A way for programmers to quickly retrieve the associated
      prescalar and time register when developing embedded
      systems using timer interrupts.
    
    
    - Combine with Ardino Uno's Timer0 (8 bit), Timer1
      (16 bit) and Timer2 (8 bit) to set registers using
      OCR1A, OCR2A, TCCR1B, TCCR2B, (1 << CS20),
      (1 << CS12), ... , etc.
      
      --   ---   --   ---   --   ---   --   ---   --   ---   --   ---   --   ---   --   ---
*/

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Input settings
#define HELPFLAG "-h"
#define TIMER0 "Timer0"
#define TIMER1 "Timer1"
#define TIMER2 "Timer2"

// Backend settings
#define SYSTEMCLOCK 16000000 // The system clock is 16 Mega Hertz on Arduino Uno
#define NUMPRESCALARS 5


/*
    The allowed error margins in the calculations of the frequencies. This is necessary
    to efficiently account for the vast amount of decimals that arise in the equations.
*/
#define ERRORMARGINS 0.1


/*
    This program is centered around the general equation:
        * x(Hz) = System Clock / ((TR + 1) * Prescalar)   ----->   Target Frequency = System Clock / ((Time Register + 1) * Prescalar)
*/

/*
    Target Frequency:
        * Lower boundary: 61.05 Hz (Timer0 & Timer2)
        * Lower boundary: 0.2385 Hz (Timer 1)
*/
#define TARGETFREQUENCY 61.05 // Hertz

const int PRESCALARS[] = {1, 8, 64, 256, 1024};

// Function Prototypes
double getFrequency(int timeReg, int prescalar);
int getPrescalarIdx(int prescalar);

int getMaxDecimal(int x);
double getAbsoluteDistance(double a, double b);

double* calculateRegisterPrescalarRelation(double frequency, int maxTimeRegValue, int maxPrescalar);
bool frequencyIsOutsideTimerBounds(int maxTimeRegValue, int maxPrescalar);


// Variables
double timeRegister;
double prescalar;
int maxTimeRegisterValue;


int main(int argc, char* argv[]) {
    
    if (argc > 1 && strcmp(argv[1], HELPFLAG) == 0) {
        printf("An integer argument (0-2) that represents the timer is expected.\n");
        return 0;
    }
    
    if (argc != 2) {
        printf("Only one argument is expected.\n");
        return 0;
    }
    
    if (strcmp(argv[1], TIMER0) == 0) { // Timer0 is 8 bit
        // maxTimeRegisterValue = log2(8) - 1;
        maxTimeRegisterValue = getMaxDecimal(8);
    } else if (strcmp(argv[1], TIMER1) == 0) { // Timer1 is 16 bit
        // maxTimeRegisterValue = log2(16) - 1;
        maxTimeRegisterValue = getMaxDecimal(16);
    } else if (strcmp(argv[1], TIMER2) == 0) { // Timer2 is 8 bit
        // maxTimeRegisterValue = log2(8) - 1;
        maxTimeRegisterValue = getMaxDecimal(8);
    } else {
        printf("No timer was selected. ('%s', '%s', '%s')\n", TIMER0, TIMER1, TIMER2);
        return 0;
    }
    
    int maxPrescalar = PRESCALARS[NUMPRESCALARS - 1];
    if (frequencyIsOutsideTimerBounds(maxTimeRegisterValue, maxPrescalar)) {
        printf("The target frequency is outside of bounds, since it doesn't allow for the resulting values of the time register and presclar.\n");
        return 0;
    }
    
    double* output = malloc(sizeof(double) * 2);
    output = calculateRegisterPrescalarRelation(TARGETFREQUENCY, maxTimeRegisterValue, maxPrescalar);
    printf("Time Register: %.3f, Prescalar: %.3f\n", output[0], output[1]);

    return 0;
}

/*
    Returns the maximal decimal number than can be generated,
    where its binary consists of 'x' number of '1's.
    
    Input/Output instances:
        * x = 3   -->   Return  7       (111)
        * x = 4   -->   Return  15      (1111)
        * x = 8   -->   Return  255     (11111111)
        * x = 16  -->   Return  65535   (1111111111111111)
*/
int getMaxDecimal(int x) {
    int outputDec = 0;
    int currentDec = 1;
    
    for (int i = 0; i < x; i++) {
        outputDec |= currentDec;
        currentDec <<= 1;
    }
    
    return outputDec;
}

// Returns the frequency in Hertz
double getFrequency(int timeReg, int prescalar) {
    return (double)SYSTEMCLOCK / ((double)(timeReg + 1) * (double)prescalar);
}


/*
    FUNCTION DESCRIPTION:
        - Returns a double pointer that points to the prescalar and time register value,
          that are valid to the inputted target frequency
        
        PARAMETERS:
            - 'targetFrequency' is the frequency in which the prescalar and register
               shall be adjusted to
               
            - 'maxTimeRegValue' is the maximum register value of the selected
               hardware timer's supported range (8 or 16 bit)
            
            - 'maxPrescalar' is the maximum prescalar supported (1024)


        MATHEMATICAL APPROACH:
            - Start from maximal values of the variables in the denominator (time register and prescalar)
              and systematically decrease their values with respect to their established dependencies and
              boundaries to find the target frequency. In other words, it's a relational equation between
              the two variables to satisfy the general equation:
              
                'frequency = system clock / ((timeRegister + 1) * prescalar)'
              
              This makes the algorithmic solution a dynamic programming issue, where sub-problems are
              contained in a larger problem.
            
            
            TIME COMPLEXITY:
                - T: Time register (max value is 65535 or 255 depending on selected timer)
                - Np: Number of distinct prescalar-values (always 5 distinct values ranging from 1 to 1024)
                
                - Complexity: O(T^(Np))   --->   O(1)
                    - Since the algorithmic solution is based on an iteration that goes through all possible
                      timer register values, we are working with a O(T) loop. Inside of this loop, we manage
                      another variable, the current prescalar, which we also try all combinations for. Thus,
                      we run T Np times with unique combinations, leaving us with O(T^(Np). Lastly, we simply
                      this to O(1) due to the constat upper bounds of the time registers and prescalars.
*/
double* calculateRegisterPrescalarRelation(double targetFrequency, int maxTimeRegValue, int maxPrescalar) {
    
    bool exitIteration = false;
    int currentTimeReg = maxTimeRegValue;
    int currentPrescalar = maxPrescalar;
    
    int pIdx = getPrescalarIdx(maxPrescalar); // Start from max index of the prescalars (the index representing 1024)
    double* output = malloc(sizeof(double) * 2);
    
    double currentFrequency;
    double currentErrorMargins;
    
    while (!exitIteration) { // O(T)
        
        currentFrequency = getFrequency(currentTimeReg, currentPrescalar);
        currentErrorMargins = getAbsoluteDistance(currentFrequency, targetFrequency);
        
        if (currentErrorMargins <= ERRORMARGINS) {
            output[0] = currentTimeReg;
            output[1] = currentPrescalar;
            printf("Matched!\n");
            break;
        }
        
        /*
            If no combination of time registers with the current prescalar yieleded the desired frequency,
            then decrease the prescalar and reset timer value.
        */
        if (--currentTimeReg == 0) {
            if (--pIdx == -1) { // Perform the O(T) iteration O(Np) times, then break out of it
                output[0] = -1;
                output[1] = -1;
                break;
            }
            currentTimeReg = maxTimeRegValue;
        }
    }
    
    return output;
}

/*
    Return true or false based on whether the target frequency is accessible by
    the timer (timer0, timer1 or timer2), considering its avaiable values on the
    time register OCR1A or OCR2A, and its avaiable prescalars.
*/
bool frequencyIsOutsideTimerBounds(int maxTimeRegValue, int maxPrescalar) {
    /*
        Upper boundary check: Ensure that high frequencies can be reached.
            
        Upper boundary for Timer1:
            0.238 Hz = (16 * 10^6) / ((65535 + 1) * 1024)
        
        Upper boundary for Timer0 and Timer2:
            61 Hz = (16 * 10^6) / ((255 + 1) * 1024)
    */
    if (getFrequency(maxTimeRegValue, maxPrescalar) < TARGETFREQUENCY) {
        return false;
    }
    
    /*
        Lower boundary check: Ensure that low frequencies can be reached.
        
        Lower boundary for Timer2:
            8000000 Hz = (16 * 10^6) / ((1 + 1) * 1)
    */
    
    if (TARGETFREQUENCY > 8000000) {
        return false;
    }
    
    return true;
}


// Returns the corresponding index of the inputted value 'prescalar'
int getPrescalarIdx(int prescalar) {
    int left = 0;
    int right = NUMPRESCALARS - 1;
    int mid;
    
    while (left <= right) {
        mid = (left + right) / 2;
        if (PRESCALARS[mid] == prescalar) {
            return mid;
        } else if (PRESCALARS[mid] < prescalar) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return -1;
}

double getAbsoluteDistance(double a, double b) {
    return a - b < 0 ? (a - b) * -1 : (a - b);
}