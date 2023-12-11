#include <stdio.h>
/*
Semester Project - Perpetual Calendar
By Jack Wilson
Submitted 11 Dec 2023
*/

int zellerCongruence(int dayOfMonth, int month, int yearOfCentury, int firstTwoDigitsOfYear){
    int dayOfWeek;
    dayOfWeek = (dayOfMonth +(13*(month+1))/5 + yearOfCentury + yearOfCentury/4 + firstTwoDigitsOfYear/4 - 2*firstTwoDigitsOfYear)%7;
    //algorithm for Zeller's congruence sourced from Wikipedia
    //Integer division automatically truncates so the floor function is unneccessary
    return dayOfWeek;
}

void printMonth(int month, int year){
    int daysInMonth = 31;
    switch(month){
        case 1: printf("JANUARY "); break;
        case 2: printf("FEBRUARY ");
        if(year%4==0){//im sure theres a more elegant way to do this but...
            daysInMonth=29;
            if(year%100==0){
                daysInMonth=28;
                if(year%400==0){
                    daysInMonth=29;
                }
            }
        }
        break;
        case 3: printf("MARCH "); break;
        case 4: printf("APRIL "); daysInMonth--;break;
        case 5: printf("MAY "); break;
        case 6: printf("JUNE "); daysInMonth--; break;
        case 7: printf("JULY "); break;
        case 8: printf("AUGUST "); break;
        case 9: printf("SEPTEMBER "); daysInMonth--; break;
        case 10: printf("OCTOBER "); break;
        case 11: printf("NOVEMBER "); daysInMonth--; break;
        case 12: printf("DECEMBER "); break;
    }
    if(month == 1 || month == 2)month+=12;//adjusting input for zeller's congruence
    printf(" %d",year);
    printf("\n");
    printf("SUNDAY      MONDAY      TUESDAY     WEDNESDAY   THURSDAY    FRIDAY      SATURDAY\n");
    int dayOfWeekOfFirstDay = zellerCongruence(1,month,year%100,year/100)-1;
    int i;
    for(i = 0; i < dayOfWeekOfFirstDay; i++){//print any necessary preceding spaces
        printf("           |");
    }
    for(int j = 1; j <=daysInMonth; j++){
        printf("%10d |",j);

        if (++i>6){//if the column counter ticks past the end of the week
            i=0;printf("\n");//reset the column counter and go to the next line
        }
    }
    printf("\n");
}

void printYear(int year){
    for(int i = 1; i < 13; i++){
        printMonth(i,year);
    }
}

void addEvent(FILE* fptr){
    printf("Please enter a short description of the event (<100 characters)");
    char description[100];
    scanf("%s ",&description);

    printf("Enter the time of the event as an integer (e.g. 0700,1230,1845)");
    int time;
    scanf("%d",&time);

    printf("Enter the day of the event as an integer");
    int day;
    scanf("%d",&day);

    printf("Enter the month of the event as an integer from 1-12");
    int month;
    scanf("%d", &month);

    printf("Enter the year of the event as an integer");
    int year;
    scanf("%d", &year);

    fseek(fptr, 0, SEEK_END);
    fprintf(fptr,"%d    %d    %s    %d    %d\n",month,year,description,time,day);
}

int main(){
    printf("Please enter your username: ");
    char user[50];
    scanf("%s",&user);
    FILE* events;
    events = fopen(user,"a+");
    rewind(events);
    printf("Here are the events this user has saved: \n");
    char c = fgetc(events); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(events); 
    }
    rewind(events);
    printf("\nPlease input 1 if you would like to add an event or 0 if not.");
    int addEvents;
    scanf("%d ",&addEvents);
    if(addEvents==1){
        addEvent(events);
    }

    int month;
    int year;
    printf("CALENDAR\n");
    monthInput:
        printf("Please input the month (a number from 1-12), or input 13 to display a yearly calendar: ");
        scanf("%d", &month);
    if(month<1||month>13){
        printf("Invalid input.\n");
        goto monthInput;
    }
    yearInput:
        printf("Please input the year: ");
        scanf("%d", &year);
    if(year<1582){
        printf("Years before 1582 are not supported.");
        goto yearInput;
    }
    if(month==13){
        printYear(year);
    }
    else printMonth(month,year);
}