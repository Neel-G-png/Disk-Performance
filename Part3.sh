echo -e "\n################### Raw Performance Test ###################"
read -p "Enter file name: " name
gcc -O3 rawPerformance.c -o rpm
./rpm $name