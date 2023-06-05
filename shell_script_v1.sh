#!/bin/bash

MEMORY_LIMIT=${1:-"102400"}
SLEEP_DURATION=${2:-"1"}

echo "Memory limit specified: $MEMORY_LIMIT"

while true; do
	# Get the memory usage of all processes
	ps_output=$(ps -eo pid,rss --sort=-rss)
	
	while read -r line; do
		pid=$(echo "$line" | awk '{print $1}')
		rss=$(echo "$line" | awk '{print $2}')
		time=$(date +%H:%M:%S)

		if [[ $rss -gt $MEMORY_LIMIT ]]; then
		 	echo "[$time] Process with PID $pid exceeded the memory limit"
		fi
	done <<< $ps_output

	sleep $SLEEP_DURATION
done
