#!/bin/bash

wget https://www.ynetnews.com/category/3082

grep -oP "https://www.ynetnews.com/article/[a-zA-Z0-9]+" 3082 |uniq > outputlinks.txt

wget -i outputlinks.txt

grep -o '[^/]\+$' outputlinks.txt > article_end.txt

printf "%s" "$(grep "https://www.ynetnews.com/article/" outputlinks.txt | wc -l)" >> results.csv

while IFS= read -r line 
do
	        printf "\n" >> results.csv
			if [ $(grep -oi "Netanyahu" $line | wc -w) == 0 ] && [ $(grep -oi "Gantz" $line | wc -w) == 0 ] && [ $(grep -oi "Bennett" $line | wc -w) == 0 ] && [ $(grep -oi "Peretz" $line | wc -w) == 0 ]
			then 
			        printf ""https://www.ynetnews.com/article/"$line, -" >> results.csv
			else
				    printf "%s%s%s%s" ""https://www.ynetnews.com/article/"$line, Netanyahu, " "$(grep -oi "Netanyahu" $line | wc -w)" ", Gantz, " "$(grep -oi "Gantz" $line | wc -w)" ", Bennett, " "$(grep -oi "Bennett" $line | wc -w)" ", Peretz, " "$(grep -oi "Peretz" $line | wc -w)" >> results.csv
			fi
			
done <<< $(cat article_end.txt)																 
			
			
			
			
			
			



