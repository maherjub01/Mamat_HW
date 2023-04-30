#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_GRADE 0
#define MAX_GRADE 100

void min(FILE *fp);

int main(int argc, char** argv){

    FILE *fp;
    if(argc == 1 || !strcmp("-",argv[1])){
        fp=stdin;
    }
    else{
        fp=fopen(argv[1], "r" );
    }

    //error check
    if(fp == NULL){
        fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    min(fp);

    fclose(fp);
}


void min(FILE *fp){

    int retval;
    int grade;
    int line_num = 0;
    int min_grade = MAX_GRADE;

    while(1){

        retval=fscanf(fp,"%d",&grade);
        line_num++;

        if(retval == EOF){ /*finished*/
            break;
        }

        else if(retval != 1){ /*error*/

            fprintf(stderr,"invalid input : %d\n",line_num);
            continue;
        }

        else if(grade>MAX_GRADE || grade<MIN_GRADE){

            fprintf(stderr,"invalid grade, line number is: %d\n",line_num);
            continue;
        }


        min_grade = min_grade > grade ? grade : min_grade;
    }

    fprintf(stdout,"%d	",min_grade);

}

