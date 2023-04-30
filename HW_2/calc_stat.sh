#! /bin/bash

ArgNum=1  
Course=$1 #course number

if [[ ! $# -eq ArgNum ]];
then
         echo "Wrong number of arguments" >&2
         exit 1
 else
          
      if [[ ! -e $Course.txt ]];
       then
        echo "Course not found" >&2
         exit 1
      else    
        
         if [[ -d $Course"_stat" ]];  
      then
         rm -r $Course"_stat"
         fi
         fi
         mkdir $Course"_stat"
    fi
      
      gcc -g -Wall hist.c -o hist.exe
      gcc -g -Wall min.c -o min.exe
      gcc -g -Wall max.c -o max.exe
      gcc -g -Wall mean.c -o mean.exe
      gcc -g -Wall median.c -o median.exe
      cat "$Course.txt" | ./hist.exe  - -n_bins 10 >> $Course"_stat"/histogram.txt
      cat "$Course.txt" | ./mean.exe  -  >> $Course"_stat"/statistics.txt
      cat "$Course.txt" | ./median.exe  -  >> $Course"_stat"/statistics.txt
      cat "$Course.txt" | ./min.exe  -  >> $Course"_stat"/statistics.txt
      cat "$Course.txt" | ./max.exe  -  >> $Course"_stat"/statistics.txt
    
	input=$Course.txt
	succeeded=0
	students_num=0
	
	while read -r line
	do
		grade=$(echo "$line" | grep -Eo '^[0-9]+')
	
		if [[ $grade -ge 0 && $grade -le 100 ]]; then
			(( students_num=students_num+1 ))
		fi
		if [[ $grade -gt 54 ]]; then
			(( succeeded=succeeded+1 ))	
		fi	
	done < "$input"
	if [[ ! $students_num -eq 0 ]]; then
	(( success_rate=($succeeded*100)/$students_num ))
	
	echo $success_rate"%" >> $Course"_stat"/statistics.txt 
	fi
