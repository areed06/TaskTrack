#ifndef TASKLIST_H
#define TASKLIST_H

/* This define statement prevents compiler from throwing error for using string functions
 * Normal sscanf, strcpy can be unsafe since they do not specify maximum string length
 * Using sscanf_s and strcpy_s, etc to prevent this warning without the define statement
*/
//#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "assignment.h"

// Constants
#define MAX_ASSIGNMENTS 100
#define MAX_CATEGORIES 100
#define MAX_CATEGORY_WIDTH 50

class TaskList {
private:
    FILE* list_file;                            // file object which stores list
    char* list_name;                            // name of list
    char** categories;                          // pointer to array of strings with category names
    int cat_cnt;                                // number of categories
    int assignment_cnt;                         // number of assignments
    int list_size;                              // size of assignments list (which can grow with added assignments)
    bool is_init;                               // tells whether list has been initialized

    void grow();

public:
    struct assignment* assignments;             // array pointer

    TaskList();                                 // default constructor
    ~TaskList();                                // default destructor

    // "getters" for specific variables
    char* name();
    int assignment_count();

    // methods for modifying the list
    int loadList(char* fname);
    int saveList(std::string fname);
    void add(const assignment& add_asmnt);

};

#endif