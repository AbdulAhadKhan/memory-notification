#!/bin/bash

limiter_value=10
interval=5

while true; do
  # Generate a random value for the parameter
  parameter_value=$((RANDOM % 20))  # Modify the range as per your requirement

  echo "Parameter Value: $parameter_value"

  if [ $parameter_value -gt $limiter_value ]; then
    echo "Value exceeds limiter_value!"

    # Get the current timestamp
    start_time=$(date +%s)

    # Continuously check if the value has gone back below the limit or the interval has passed
    while true; do
      # Generate a new random value for the parameter
      parameter_value=$((RANDOM % 20))  # Modify the range as per your requirement
      echo "Parameter Value: $parameter_value"

      # Check if the value has gone back below the limit
      if [ $parameter_value -le $limiter_value ]; then
        echo "Value returned below the limiter_value within $interval seconds."
        # Log this behavior as required
        break
      fi

      # Get the current timestamp and calculate the elapsed time
      current_time=$(date +%s)
      elapsed_time=$((current_time - start_time))

      # Check if the interval has passed
      if [ $elapsed_time -ge $interval ]; then
        echo "Timeout reached!"
        break
      fi

      sleep 1
    done
  fi

  # Wait for the next iteration
  sleep 1
done
