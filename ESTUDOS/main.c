#include <stdio.h>
#include <time.h> //Library needed to work with time in C
#include <unistd.h>

/*useful functions from time.h*/

// Function (difftime) that calculates the difference between two time in seconds since 1970
double difference_between_times(time_t t2, time_t t1){

    double diff = difftime(t2, t1);

    return diff;
}

// Function (ctime) that format the time in seconds since 1970 in string and date format
void date1(time_t t1){

    char *buffer = ctime(&t1);

    printf("date now: %s \n\n", buffer);
} 

// Function (gm_time) that enable us to print just the day, month (considering Jan as 0), year, hour (since 1900), minutes, seconds, etc... in gmtimezone
void date2(time_t t1){

    struct tm *gm_time = gmtime(&t1);

    int second = gm_time->tm_sec;
    int minute = gm_time->tm_min;
    int hour = gm_time->tm_hour - 3;
    int day = gm_time->tm_mday;
    int month = gm_time->tm_mon + 1;
    int year = gm_time->tm_year - 100;

    printf("second: %d\n", second);
    printf("minute: %d\n", minute);
    printf("hour: %d\n", hour);
    printf("day: %d\n", day);
    printf("month: %d\n", month);
    printf("year: %d\n", year);

    printf("\n");

    printf("date: %d/%d/%d - %d:%d:%d \n\n", day, month, year, hour, minute, second);
}

// Function (localtime) that enables us to print all gmtime but in our localtime
void date3(time_t t1){

    struct tm *cur_time = localtime(&t1);

    int second = cur_time->tm_sec;
    int minute = cur_time->tm_min;
    int hour = cur_time->tm_hour;
    int day = cur_time->tm_mday;
    int month = cur_time->tm_mon + 1;
    int year = cur_time->tm_year - 100;

    printf("second: %d\n", second);
    printf("minute: %d\n", minute);
    printf("hour: %d\n", hour);
    printf("day: %d\n", day);
    printf("month: %d\n", month);
    printf("year: %d\n", year);

    printf("\n");

    printf("date: %d/%d/%d - %d:%d:%d \n\n", day, month, year, hour, minute, second);

}

// Function (strftime)
void date4(time_t t1){

    struct tm *time = localtime(&t1);
    char buffer[64];

    strftime(buffer, sizeof(buffer), "%d/%m/%Y - %H:%M:%S", time);

    printf("date-time: %s\n\n", buffer);


}

int main(void){

    // variable that holds the time the moment the program is executed
    time_t t1 = time(NULL);

    // It returns the time in seconds since January 1, 1970 midnight
    printf("Time in seconds now since 1970: %ld \n", t1);

    sleep(2);

    time_t t2 = time(NULL);

    // It returns the time in seconds since 1970 tow seconds later than t1
    printf("Time in seconds two seconds later: %ld \n\n", t2);

    double diff = difference_between_times(t2, t1);

    // It returns the difference in seconds of t1 and t2
    printf("Difference between t1 and t2: %f \n\n", diff);

    // It returns the time in a date in a default format 
    date1(t1);

    date2(t1);

    date3(t1);

    date4(t1);

    return 0;
}