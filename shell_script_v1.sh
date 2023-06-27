#!/bin/bash

# TODO: email the admin if the memory limit is exceeded
# based on the defined policies.
# 
# Policies:
# 1. If a process exceeds the lower limit, set the flag to 1.
#    If the flag is already set to 1, ignore the process. Wait 
#    for X period of time and then email the admin, and set the
#    flag to 0.
# 2. If a process exceeds the upper limit, email the admin
#    immediately and set the flag to 0.
# 
# Why not check the flag before checking the memory limit?
# Currently, individual processes are checked for memory limit.
# To check if the processes stay above the lower limit, the
# they need to be tracked independently. While this is possible,
# it is not the current goal of this script. This may change in
# the future.

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
