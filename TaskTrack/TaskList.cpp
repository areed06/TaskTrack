#include "TaskList.h"

/* TaskList:
* -- default constructor
* -- all pointers initialized with nullptr
*/
TaskList::TaskList() {
    list_file = nullptr;
    assignments = nullptr;
    list_name = nullptr;
    categories = nullptr;
    cat_cnt = 0;
    assignment_cnt = 0;
    list_size = 0;
    is_init = false;
}

/* ~TaskList:
* -- all dynamically allocated members must be deallocated
*/
TaskList::~TaskList() {
    
    delete[] assignments;
    
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        delete[] categories[i];
    }
    delete[] categories;

}

/* name:
* @ret list_name --> the name of the list
*/
char* TaskList::name() {
    return list_name;
}

/* assignment_count:
* @ret assignment_cnt --> how many assignments are in the list
*/
int TaskList::assignment_count() {
    return assignment_cnt;
}

/* loadList:
* -- takes a .csv file and parses assignments from it
* @arg fname -> string containing file path
* @ret status -> returns 1 if successfully loaded, 0 if failed
*/
int TaskList::loadList(char* fname) {

    // must delete current list before loading new one
    if (is_init) {

        for (int a = 0; a < assignment_cnt; a++) {
            delete assignments[a].title;
            delete assignments[a].category;
            delete assignments[a].description;
        }
        delete[] assignments;

        for (int i = 0; i < MAX_CATEGORIES; i++) {
            delete[] categories[i];
        }
        delete[] categories;
    }

    // reallocate members
    // DO THESE NEED TO BE DYNAMICALLY ALLOCATED IF THEY ARE ALWAYS THE SAME SIZE?
    assignments = new assignment[MAX_ASSIGNMENTS];
    categories = new char*[MAX_CATEGORIES];
    for (int x=0; x<100; x++) {
        categories[x] = new char[MAX_CATEGORY_WIDTH];
    }

    // open the task list file
    fopen_s(&list_file, fname, "r");
    if (list_file == NULL) {
        return 0;
    }

    // temporary variables
    char* token;
    char buf[200];
    char* next_tok = buf;
    int line_number = 0;
    int line_length = 0;

    // initializing values
    assignment_cnt = 0;
    list_size = 0;
    is_init = 0;

    // parse each line of the task list file
    while(fgets(buf, 200, list_file) != NULL) {

        line_length = strlen(buf);
        buf[line_length - 1] = ',';

        if (line_number == 0) {

            token = strtok_s(buf, ",", &next_tok);
            if (strcmp(token, ">>LISTNAME") == 0) {

                token = strtok_s(NULL, ",", &next_tok);
                list_name = _strdup(token);

            } else {
                return 0;
            }

        } else if (line_number == 1) {

            token = strtok_s(buf, ",", &next_tok);
            if (strcmp(token, ">>CATEGORIES") == 0) {

                cat_cnt = 0;

                token = strtok_s(NULL, ",", &next_tok);
                while (strcmp(next_tok, "\0") != 0) {
                    strcpy_s(categories[cat_cnt], sizeof(categories[cat_cnt]), token);
                    token = strtok_s(NULL, ",", &next_tok);
                    cat_cnt++;
                }

            } else {
                return 0;
            }

        } else if (line_number > 1) {

            token = strtok_s(buf, ",", &next_tok);
            if (strcmp(token, ">>ASSIGNMENT") == 0) {
                token = strtok_s(NULL, ",", &next_tok);
                assignments[assignment_cnt].title = _strdup(token);

                token = strtok_s(NULL, ",", &next_tok);
                assignments[assignment_cnt].description = _strdup(token);

                token = strtok_s(NULL, ",", &next_tok);
                assignments[assignment_cnt].category = _strdup(token);

                token = strtok_s(NULL, ",", &next_tok);
                int prio;
                sscanf_s(token, "%i", &prio);
                assignments[assignment_cnt].priority = prio;

                token = strtok_s(NULL, ",", &next_tok);
                int m;
                int d;
                int y;
                sscanf_s(token, "%02d-%02d-%04d", &m, &d, &y);
                assignments[assignment_cnt].due_month = m;
                assignments[assignment_cnt].due_day = d;
                assignments[assignment_cnt].due_year = y;

                token = strtok_s(NULL, ",", &next_tok);
                int hr;
                int min;
                sscanf_s(token, "%02i:%02i", &hr, &min);
                assignments[assignment_cnt].due_hour = hr;
                assignments[assignment_cnt].due_min = min;

                token = strtok_s(NULL, ",", &next_tok);
                int progress;
                sscanf_s(token, "%02i", &progress);
                assignments[assignment_cnt].progress = progress;

                list_size++;
                assignment_cnt++;
            }
        }

        line_number++;
    }

    fclose(list_file);

    is_init = true;
    return 1;
}

int TaskList::saveList(std::string fname) {
    return 1;
}

/* grow:
 * -- private method
 * -- Dynamically allocate new assignment array with 10 more entries
 * -- Initialize all elements of new array with existing assignments
 *      -- Must copy strings
 * -- Delete all strings from existing array
 * -- Delete current array pointer
 * -- Reassign value of assignments pointer with tmp
*/
void TaskList::grow() {

    assignment* tmp = new assignment[list_size + 10];

    for (int i = 0; i < assignment_cnt; i++) {
        tmp[i] = assignments[i];

        tmp[i].title = _strdup(assignments[i].title);
        tmp[i].description = _strdup(assignments[i].description);
        tmp[i].category = _strdup(assignments[i].category);

        delete assignments[i].title;
        delete assignments[i].description;
        delete assignments[i].category;
    }

    delete[] assignments;
    assignments = tmp;

    list_size += 10;
}

/* add:
* -- appends an assignment to the list
* @arg new_asmnt --> const reference to the new assignment
*/
void TaskList::add(const assignment& new_asmnt) {

    if (assignment_cnt == list_size) {
        grow();
    }

    assignments[assignment_cnt] = new_asmnt;
    assignments[assignment_cnt].title = _strdup(new_asmnt.title);
    assignments[assignment_cnt].description = _strdup(new_asmnt.description);
    assignments[assignment_cnt].category = _strdup(new_asmnt.category);

    assignment_cnt++;
}