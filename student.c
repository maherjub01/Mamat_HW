#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

elem_t student_clone(elem_t e){

    if (e == NULL){
        return NULL;
    }
    struct student *p_student = (pstudent_t)e;
    struct student *cloned = malloc(sizeof(struct student));
    if (cloned == NULL){
        return NULL;
    }

    cloned->name = malloc(strlen(p_student->name)+1);
    if (cloned->name == NULL){

        free(cloned);
        return NULL;
    }
    strcpy(cloned->name, p_student->name);
    cloned->age = p_student->age;
    cloned->id = p_student->id;

    return cloned;
}


void student_destroy(elem_t e){

    if (e == NULL){

        return;
    }
    free(e);
}

void student_print(elem_t e){

    if (e == NULL){

        return;
    }

    struct student *p_student = (pstudent_t)e;
    printf("student name: %s, age: %d, id: %d.\n", p_student->name, p_student->age, p_student->id);
}
