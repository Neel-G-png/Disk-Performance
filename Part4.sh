#!/bin/bash
echo -e "\nEnter file name for a file that is within 3 - 5Gb, this code will read"
echo -e "the whole file with varying block sizes which might take time to run."
echo -e "You will also be prompted to input the command to clear cache"
read -p "Enter file name: " name

echo -e "\n################### Running for Cached Reads ###################"
echo -e "\n## For blockSize = 5120##"
output=$(./run $name -r 5120 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"

echo -e "\n## For blockSize = 10240##"
output=$(./run $name -r 10240 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"

echo -e "\n## For blockSize = 20480##"
output=$(./run $name -r 20480 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"

echo -e "\n## For blockSize = 40960##"
output=$(./run $name -r 40960 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"

read -p "Enter command to clear cache: " flushCache
echo -e "################### Running for non-Cached Reads ###################"

eval "$flushCache"
gcc -O3 run.c -o run
echo -e "\n## For blockSize = 5120##"
output=$(./run $name -r 5120 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"

eval "$flushCache"
echo -e "\n## For blockSize = 10240##"
output=$(./run $name -r 10240 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"

eval "$flushCache"
echo -e "\n## For blockSize = 20480##"
output=$(./run $name -r 20480 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"

eval "$flushCache"
echo -e "\n## For blockSize = 40960##"
output=$(./run $name -r 40960 1000000000)
file_size=$(echo "$output" |  awk '/Calculated XOR in time/ {print $NF}')
echo "Calculated XOR in time: $file_size Seconds"