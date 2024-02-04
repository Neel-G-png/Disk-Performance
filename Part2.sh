#!/bin/bash
echo -e "\nEnter file name for a file" 
echo -e "\t1. That exists (best resuls)"
echo -e "\t2. That should be created (will take a long time to execute)"
echo -e "to find what file size can be read in reasonable time."
read -p "Enter file name: " name

echo -e "################### Trying to find Reasonable file size ###################"
echo -e "## For blockSize = 64 ##"
gcc -O3 run2.c -o run2
output=$(./run2 $name 64)

file_size=$(echo "$output" | tail -n 1) # awk '/File Size/ {print $NF}')
echo "File Size: $file_size"

echo -e "\n## For blockSize = 128 ##"
output=$(./run2 $name 128)
file_size=$(echo "$output" | tail -n 1) # awk '/File Size/ {print $NF}')
echo "File Size: $file_size"

echo -e "\n## For blockSize = 256 ##"
output=$(./run2 $name 256)
file_size=$(echo "$output" | tail -n 1) # awk '/File Size/ {print $NF}')
echo "File Size: $file_size"

echo -e "\n## For blockSize = 512 ##"
output=$(./run2 $name 512)
file_size=$(echo "$output" | tail -n 1) # awk '/File Size/ {print $NF}')
echo "File Size: $file_size"

echo -e "\n## For blockSize = 1024 ##"
output=$(./run2 $name 1024)
file_size=$(echo "$output" | tail -n 1) # awk '/File Size/ {print $NF}')
echo "File Size: $file_size"

echo -e "\n## For blockSize = 2048 ##"
output=$(./run2 $name 2048)
file_size=$(echo "$output" | tail -n 1) # awk '/File Size/ {print $NF}')
echo "File Size: $file_size"