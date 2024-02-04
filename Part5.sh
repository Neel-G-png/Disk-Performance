echo -e "\n################### Running the System Calls performance test ###################"
read -p "Enter file name: " name
gcc -O3 syscheck.c -o sc
./sc $name