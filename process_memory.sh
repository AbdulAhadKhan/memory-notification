#!/bin/bash

MEMORY_LIMIT=${1:-"82400"}
SLEEP_DURATION=${2:-"1"}
rm log
echo "Memory limit specified: $MEMORY_LIMIT"
echo "Memory limit specified: $MEMORY_LIMIT" >> log

while true; do
	time=$(date +%H:%M:%S)
	echo -e "\n###########################################################################################"
	echo -e "[$time] Following processes exceed limit $MEMORY_LIMIT\n"
	
	echo -e "\n###########################################################################################" >> log
	echo -e "[$time] Following processes exceed limit $MEMORY_LIMIT\n" >> log
	
	# Run pstree -p and store the output in a variable
	pstree_output=$(pstree -p)

	# Extract the PIDs using grep and awk
	pids=$(echo "$pstree_output" | grep -oP '\(\K\d+(?=\))' | awk '{print $1}')

	# Iterate over each PID and retrieve memory consumption and PPID
	for pid in $pids; do
		rss=$(ps -p $pid -o rss=)
		ppid=$(ps -p $pid -o ppid=)
		
		if [[ $rss -gt $MEMORY_LIMIT ]]; then
			echo "PID: $pid,   PPID: $ppid,   RSS: $rss" 
			echo "PID: $pid,   PPID: $ppid,   RSS: $rss"  >> log
		fi
	done
	
	sleep $SLEEP_DURATION
done

echo "Script execution completed."
echo "Script execution completed." >> log
