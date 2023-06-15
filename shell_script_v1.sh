#!/bin/bash

MEMORY_LIMIT=${1:-"82400"}
SLEEP_DURATION=${2:-"1"}

function print_and_log() {
    echo -e "$1"
    echo -e "$1" >> log
}

while true; do
    # Variable to store process information that exceeds the memory limit
    exceeded_processes=""

	# Get the memory usage of all processes
	ps_output=$(ps -eo pid,drs --sort=-drs)
	
	while read -r line; do
		pid=$(echo "$line" | awk '{print $1}')
		drs=$(echo "$line" | awk '{print $2}')
		time=$(date +%H:%M:%S)

		if [[ $drs -gt $MEMORY_LIMIT ]]; then
            exceeded_processes="$exceeded_processes\nPID: $pid, DRS: $drs"
		fi
	done <<< $ps_output

    if [[ -n $exceeded_processes ]]; then
        output="$output\n###########################################################################################"
        output="$output\n[$time] Following processes exceed limit $MEMORY_LIMIT\n"
        output="$output$exceeded_processes\n"
        print_and_log "$output"
    fi

	sleep $SLEEP_DURATION
done
