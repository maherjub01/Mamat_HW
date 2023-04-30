#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_GRADE 0
#define MAX_GRADE 100

void median(FILE* fp);


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
        return 1 ;
    }
    median(fp);

    fclose(fp);
}


void median(FILE* fp) {
    int counter = 0;
    int valid_grades;
    int grade;
    int hist[MAX_GRADE+1] = {0};
    int line_num = 1;
    int retval;
    int median_grade = 0;
    int median_index;
    int invalid_grades = 0 ;

    while(1){

        retval=fscanf(fp,"%d",&grade);

        if(retval == EOF){
            break; //finished
        }

        else if(retval != 1){ /*error*/

            invalid_grades++;
            fprintf(stderr,"invalid input : %d\n",line_num);
        }

        else if(grade>MAX_GRADE || grade<MIN_GRADE){

            invalid_grades++;
            fprintf(stderr,"invalid grade, line number is: %d\n",line_num);
        }

        hist[grade]++;
        line_num++;
    }
    valid_grades = line_num - invalid_grades - 1;
    median_index = (valid_grades +1) / 2;

    int i = 0;
    while (i != MAX_GRADE+1){
        counter += hist[i];
        if(counter>=median_index){
            median_grade=i;
            break;
        }
        i++;
    }

    fprintf(stdout,"%d	",median_grade);

}
