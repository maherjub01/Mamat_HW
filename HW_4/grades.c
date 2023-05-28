#include "linked-list.h"
#include "grades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE -1

typedef struct course{

    int course_grade;
    char *course_name;
    
} Course;

typedef struct student{
    
    int student_id;
    char *student_name;
    struct list* Course_list;//defining a list of the courses for each student

} Student;

typedef struct grades{

    struct list* students;

} Grade;

int clone_course(const Course *source, Course **dist) {

    Course *copy = malloc(sizeof(Course));
    if (copy == NULL) {
        return FAILURE; // Failed to allocate memory for the copy
    }

    copy->course_grade = source->course_grade;
    copy->course_name = (char*)malloc(strlen(source->course_name) + 1);

    if (copy->course_name == NULL) {
        free(copy);
        return FAILURE; // Failed to allocate memory for the course name
    }

    strcpy(copy->course_name, source->course_name);
    *dist = copy;

    return 0;
}

void destroy_course(Course *Mycourse);
void destroy_student(Student *Mystudent);

int clone_student(Student *source, Student **dist){

    Student* copy = malloc(sizeof(Student));
    if (copy == NULL) {

        return FAILURE; // Failed to allocate memory for the copy
    }

    copy->student_id = source->student_id;
    copy->student_name = (char*)malloc((strlen(source->student_name) + 1));
    if (copy->student_name == NULL) {

        free(copy);
        return FAILURE; // Failed to allocate memory for the course name
    }

    strcpy(copy->student_name,source->student_name);

    copy->Course_list = list_init((element_clone_t)clone_course,
                                     (element_destroy_t)destroy_course );

    struct iterator *source_iterator = list_begin(source-> Course_list);
    struct iterator *check_iterator = list_begin(copy-> Course_list);
    Course *source_course = list_get(source_iterator);
    int size_of_list = (int)list_size(source-> Course_list);
    if(size_of_list){
        list_push_front(copy-> Course_list, source_course);
        check_iterator = list_begin(copy-> Course_list);
    }
    int i=0;
    while(i < size_of_list-1){// copying each index in the list

    	source_iterator = list_next(source_iterator);
        source_course = list_get(source_iterator);
        list_insert(copy-> Course_list,check_iterator,source_course);
        check_iterator = list_next(check_iterator);
        i++;
     }
    *dist=copy;
    return 0;
}

void destroy_course(Course *course){

    free(course->course_name);// we allocated memory for course_name
    free(course);
}

void destroy_student(Student *student){

    list_destroy(student->Course_list);// because we use malloc
    free(student->student_name);
    free(student);
}

void grades_destroy(struct grades *grades){

	list_destroy(grades->students);
	free(grades);
}

struct grades* grades_init(){

    Grade* grades_aux = malloc(sizeof(Grade));

    if (grades_aux == NULL){

        free(grades_aux);
        return FAILURE;
    }

    element_clone_t elem_clone = (element_clone_t)clone_student;
    element_destroy_t elem_destroy = (element_destroy_t)destroy_student;
    grades_aux->students= list_init(elem_clone, elem_destroy);
    return grades_aux;
}

int grades_add_student(struct grades *grades, const char *name, int id){

	if(grades == NULL){

        return FAILURE;
    }

	if (id <= 0){

     	return FAILURE;
    }

    struct iterator *student_index = list_begin(grades->students);

    // this variable contains the current student that we are checking
    Student *curr_student;

    while(student_index != NULL)
    {
        curr_student = list_get(student_index);
        if(curr_student->student_id == id)
        {
            // student_id was inserted
            return FAILURE;
        }
        student_index=list_next(student_index);
    }

    // getting here means that we should add a new student

    Student *New_Student=(struct student*)malloc(sizeof(Student));
    if (New_Student == NULL){

        free(New_Student);
        return FAILURE;
    }

    New_Student->student_name=(char*)malloc((int)strlen(name) + 1);
    if(New_Student->student_name == NULL) {

        free(New_Student->student_name);
        return FAILURE;
    }

    New_Student->student_id = id;
    strcpy(New_Student->student_name,name);

    New_Student -> Course_list = list_init((element_clone_t)clone_course,
                                          (element_destroy_t)destroy_course);

    if((list_push_back(grades->students, New_Student)) == 0){

        free(New_Student->student_name);
        list_destroy(New_Student-> Course_list);
        free(New_Student);

        return 0;
    }

    //if we get here then list_push_back failed
    free(New_Student->student_name);
    list_destroy(New_Student-> Course_list);
    free(New_Student);

    return FAILURE;
}

int grades_add_grade(struct grades *grades, const char *name,
                     int id, int grade){

	if(grades == NULL){

        return FAILURE;
    }

	if (id <= 0){

     return FAILURE;
	}

	if((grade < 0) || (grade > 100)){

 	 return FAILURE;
 	}

    struct iterator *student_index = list_begin(grades->students);
    Student *curr_student;
    Course *curr_course;

    while(student_index != NULL){

        curr_student = list_get(student_index);

        if(curr_student->student_id == id){

            struct iterator *course_index =list_begin(curr_student-> Course_list);
            while(course_index != NULL){

                curr_course = list_get(course_index);
                if(!strcmp(curr_course->course_name, name)){
                    return FAILURE;
                }
                course_index = list_next(course_index);
            }

            // getting here means the course not found
            Course *New_Course=(struct course*)malloc(sizeof(Course));
            if (New_Course == NULL){

                free(New_Course);
                return FAILURE;
            }

            New_Course->course_name=(char*)malloc((int)strlen(name) + 1);
            if (New_Course->course_name == NULL){

                free(New_Course->course_name);
                return FAILURE;
            }

            New_Course->course_grade = grade;
            strcpy(New_Course->course_name, name);
            if((list_push_back(curr_student-> Course_list, New_Course)) == 0){

                free(New_Course->course_name);
                free(New_Course);
                return 0;
            }

            // getting here means list_push_back failed
            else{

                free(New_Course->course_name);
                free(New_Course);
                return FAILURE;
            }
        }

        else {

            student_index = list_next(student_index);
        }
    }
  return FAILURE;
}

int grades_print_student(struct grades *grades, int student_id){

	if(grades == NULL){

        return FAILURE;
	}

	if(student_id <= 0){

        return FAILURE;
	}

	Student *student_aux;
    Course *course_aux;
	struct iterator *student_index = list_begin(grades->students);

    while(student_index != NULL)
    {
        student_aux = list_get(student_index);
        if(student_aux->student_id == student_id)
        {
            printf("%s %d:",student_aux->student_name,student_aux->student_id);
            struct iterator *course_index = list_begin(student_aux->Course_list);

            while(1)
            {
                if(course_index != NULL){

                    course_aux = list_get(course_index);
                    printf(" %s %d",course_aux->course_name, course_aux->course_grade);
                    course_index = list_next(course_index);
                }
                // this check is to prevent printing "," after the last course
                if(course_index == NULL){

                    break;
                }
                else{

                    printf(",");
                }
            }

            printf("\n");// done with printing all the courses
            return 0;
        }
        else
        {
            student_index = list_next(student_index);
        }
    }
    return FAILURE;
}

int grades_print_all(struct grades *grades){

    if(!grades){

        return FAILURE;
    }

    struct iterator *student_index =list_begin(grades->students);

    Student *curr_student;
    while (student_index != NULL){

        curr_student = list_get(student_index);
        grades_print_student(grades, curr_student->student_id);
        student_index= list_next(student_index);
    }
    return 0;
}

float grades_calc_avg(struct grades *grades, int student_id, char **out){

	if(!grades){

        *out=NULL;
        return FAILURE;
	}

	if(student_id <=0){

        *out=NULL;
        return FAILURE;
	}

	int courses_num = 0;
	int sum = 0;

	struct iterator *student_index = list_begin(grades->students);
	Student *student_aux;
	Course *course_aux;

    while(student_index != NULL)
    {
        student_aux = list_get(student_index);

        if(student_aux->student_id == student_id)
        {
        	*out = (char*)malloc((strlen(student_aux->student_name)+1));

            if (out == NULL){

                return FAILURE;
            }

        	// put the student's name in out
        	strcpy(*out,student_aux->student_name);

            struct iterator *course_index = list_begin(student_aux->Course_list);

            // counting grades
            while(course_index != NULL){

                course_aux = list_get(course_index);
    	        sum += course_aux->course_grade;
                courses_num++; //count the grades number.
                course_index = list_next(course_index);
            }
            // no grades
            if(courses_num == 0){

                return 0;
            }

            return ((float)sum/(float)courses_num);
        }
        else
        {
            student_index = list_next(student_index);
        }
    }
    return FAILURE;
}
