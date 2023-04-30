#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_GRADE 0
#define MAX_GRADE 100

void mean(FILE *fp);


int main(int argc, char** argv){
    FILE *fp;
    if(argc == 1 || !strcmp("-",argv[1])){
        fp=stdin;
    }
    else{
        fp=fopen(argv[1], "r" );
    }

    // error check
    if(fp == NULL){
        fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
        return 1;
    }
    mean(fp);

    fclose(fp);
}


void mean(FILE *fp){
    int retval;
    int grade;
    int line_num = 1;
    int valid_grades;
    int grades_sum = 0;
    double avg;
    int invalid_grades = 0;


    while (1) {

        retval = fscanf(fp, "%d", &grade);

        if(retval == EOF){
            break; /* finished */
        }

        else if(retval != 1){

            invalid_grades++;
            fprintf(stderr,"invalid input : %d\n",line_num); /*error*/
        }

        else if(grade>MAX_GRADE || grade<MIN_GRADE){

            invalid_grades++;
            fprintf(stderr,"invalid grade, line number is: %d\n",line_num);
        }

        line_num++;
        grades_sum += grade;

    }

    valid_grades = line_num - invalid_grades - 1;
    avg = (double)grades_sum/(double)valid_grades;
    fprintf(stdout, "%.2lf	", avg);

}
