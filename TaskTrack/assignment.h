#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <time.h>

/* Assignment:
* -- structure which stores important characteristics of an assignment
*/

struct assignment {
    char* title;            // assignment's name
    char* description;      // brief description of the assignment
    char* category;         // the category, course, or label of the assignment
    int priority;           // priority level

    // due date of the assignment
    int due_month;
    int due_day;
    int due_year;

    // due time of the assignment
    int due_hour;
    int due_min;

    int progress;           // percent completion of the assignment
};

#endif