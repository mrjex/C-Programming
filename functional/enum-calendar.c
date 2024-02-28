#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXBUFFER 200

#define ROUNDS 10 // 1 round is incremented after the 5th week is reached

#define WEEKDAYS 7
#define WEEKS 5


enum Day {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
enum Week {Week1, Week2, Week3, Week4, Week5};

const enum Day dayMap[] = {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
const enum Week weekMap[] = {Week1, Week2, Week3, Week4, Week5};

void readInput(char* s);
void wait(unsigned int secs);
char* getDay(enum Day day);

int main(int argc, char* argv[]) {
    char startWeek[MAXBUFFER];
    readInput(startWeek);
    
    char startDay[MAXBUFFER];
    readInput(startDay);
    
    char* endPointer;
    long startWeekInt = strtol(startWeek, &endPointer, 10);
    
    if (*endPointer != '\0') {
        printf("Invalid Number.\n");
        return 0;
    }
    
    int startDayInt = atoi(startDay);
    
    int currentRound = 0;
    while (currentRound < ROUNDS) {
        enum Day today = dayMap[startDayInt++];
        enum Week week = weekMap[startWeekInt];
        
        printf("Week %d, %s\n", week, getDay(today));
        
        if (startDayInt == WEEKDAYS) {
            startDayInt = Monday;
            startWeekInt++;
            
            printf("\n"); // Space between each week
            
            if (startWeekInt == WEEKS) {
                printf("\n\n");
                printf("----------\n");
                printf("Week 5 reached! Starting from week 1 again...\n");
                printf("----------");
                printf("\n\n");
                
                startWeekInt = 0;
                currentRound++;
            }
        }
        
        wait(1);
    }

    printf("\n");
    printf("Exiting Program...\n");
    return 0;
}

void wait(unsigned int secs) {
    unsigned int retTime = time(0) + secs; // Define the prospective global time in which the delay ceases
    while (time(0) < retTime); // Iterate while the current time hasn't passed the defined end time
}

void readInput(char* s) {
    fgets(s, MAXBUFFER, stdin);
    s[strlen(s) - 1] = '\0';
}

char* getDay(enum Day day) {
    if (day == 0) {
        return "Monday";
    } else if (day == 1) {
        return "Tuesday";
    } else if (day == 2) {
        return "Wednesday";
    } else if (day == 3) {
        return "Thursday";
    } else if (day == 4) {
        return "Friday";
    } else if (day == 5) {
        return "Saturday";
    }
    return "Sunday";
}