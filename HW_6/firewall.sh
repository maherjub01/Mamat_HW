#! /bin/bash
pkts=$(cat | tr -d ' ')

while read line
do
	#delete "," and spaces in the rule line
	rule1=$(echo "$line" | tr -d ',' | tr -d ' ' )
	
	#delete the comments in the rule line
	
	rule2=$(echo "$rule1" | sed -e 's/#.*//' ) 
	#replace the field with *field in order to split the rule 
	
	rule3=$(echo "$rule2" | sed -e 's/dst-ip/*dst-ip/g')
	
	rule4=$(echo "$rule3" | sed -e 's/src-port/*src-port/g')
	
	split_rule=$(echo "$rule4" | sed -e 's/dst-port/*dst-port/g')
	
	if [[ "$split_rule" != "" ]]; then
			
		src_ip=$(echo $split_rule | awk -F* '{print $1}')	
		dst_ip=$(echo $split_rule | awk -F* '{print $2}')	
		src_port=$(echo $split_rule | awk -F* '{print $3}')	
		dst_port=$(echo $split_rule | awk -F* '{print $4}')
		#Hint that we tried to minimize the length of this line 
		#but didnt succeed cause we had to pipe the outputs.		
       corr_pkts+=$(echo "$pkts" | ./firewall.exe "$src_ip" | ./firewall.exe "$dst_ip" | ./firewall.exe "$src_port" | ./firewall.exe "$dst_port" )
		corr_pkts+="\n"
	fi


done < "$1"

echo -e "$corr_pkts" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort -u