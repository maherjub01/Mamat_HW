#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN_GRADE 0
#define MAX_GRADE 100
#define N_BINS 10


void hist(FILE *fp, int n_bins);


int main(int argc, char**argv){
    FILE *fp;
    fp = stdin;
    int n_bins = N_BINS;
    for(int i = 1; i < argc-1; i++){

        if(!strcmp(argv[i], "-"))
        {
            fp = stdin;
        }
        else if(!strcmp(argv[i], "-n_bins"))
        {
            n_bins = i < argc-1 ? atoi(argv[i+1]):N_BINS;
            i++;
        }
        else
        {
            fp = fopen(argv[i], "r");
        }
    }

    if(!fp){

        fprintf(stderr,"Find not found: \%s\"\n",argv[1]);
        return 1;
    }

    hist(fp,n_bins);
    fclose(fp);
    return 0;
}


void hist(FILE *fp, int n_bins) {

    int grade;
    int retval;
    int line_num = 1;
    int r = MAX_GRADE / n_bins;

    int *bins = malloc(sizeof(int)*(n_bins));

    while (1) {
        retval = fscanf(fp, "%d", &grade);
        if (retval == EOF) {
            break;
        }

        if ((grade < MIN_GRADE) || (grade > MAX_GRADE)){
            fprintf(stderr, "invalid grade, line number is: %d \n", line_num);
        }
        else{
            if ((grade == MIN_GRADE) || (grade == MAX_GRADE)){
                if (grade == MIN_GRADE){
                    bins[0]++;
                }
                else{
                    bins[n_bins - 1]++;
                }

            }
            else {
                int k = grade / r;
                if (k < n_bins) {
                    bins[k]++;
                }
            }
        }
        line_num++;
    }

    // Calculate the width of each bin
    int bin_width = (MAX_GRADE - MIN_GRADE) / n_bins;


    for (int i = 0; i < n_bins ; i++) {
        // Calculate the boundaries of the bin
        int left_bin = MIN_GRADE + (i * bin_width);
        int right_bin = MIN_GRADE + ((i+1) * bin_width - 1);

        // If this is the last bin, include any grades that are exactly equal to the right boundary
        if (i == n_bins - 1) {
            right_bin = MAX_GRADE;
        }

        // Print the bin boundaries and the number of grades in the bin
        fprintf(stdout,"%d-%d	%d\n",left_bin,right_bin,bins[i]);
    }

    free(bins);
}
