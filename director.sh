#!/bin/bash

# Check command line arguments
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 W sPID"
  exit 1
fi

W=$1
sPID=$2

# Trap SIGINT signal and perform clean-up before terminating
function cleanup() {
  # Kill all worker processes
  kill -9 $(jobs -p)

  # Delete worker files
  rm -f worker*.txt

  exit 0
}
trap cleanup SIGINT

# Start worker processes
for ((i=1; i<=W; i++)); do
  ./worker worker$i.txt $2 &
done

# Function to display contents of worker files
function display() {
  clear
  for ((i=1; i<=W; i++)); do
    echo "Contents of worker$i.txt"
    cat worker$i.txt
    echo ""
  done
}

# Loop to call display function once per second
while true; do
  sleep 1
  display
done
