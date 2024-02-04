#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define MEGABYTE (1024*1024)
#define GIGABYTE (1024*1024*1024)

unsigned int xor(char * buf, int bs){
    unsigned int result = 0;
    unsigned int *newbuf;
    newbuf = (unsigned int *)buf;
    for (int i = 0; i < bs; i++) {
        result ^= newbuf[i];
    }
    return result;
}

unsigned int readBlocks(int fd,int blockSize){
    char * buf = (char * )malloc((blockSize));
    unsigned int xorcumulate = 0; 
    int n;

    while((n = read(fd,buf,blockSize))>0){
        xorcumulate ^= xor(buf,n/4);
    }
    return xorcumulate;
    free(buf);
}

int main(int argc, char *argv[])
{
    int ptr;
    unsigned int FinalXOR;
    char *filename = argv[1];
    double timeTaken;
    time_t start, end;
    off_t blockSize = MEGABYTE;

    if(argc <= 1){
        printf("Incorrect Usage\nPlease enter ./fast <filename>\n");
        exit(0);
    }
    ptr = open(filename, O_RDWR | O_APPEND );
    off_t fileSize = lseek(ptr,(size_t)0, SEEK_END);
    // printf("File Size - %lld Bytes\n",fileSize);
    close(ptr);

    ptr = open(filename, O_RDONLY);
    time(&start); 
    FinalXOR = readBlocks(ptr, blockSize);
    time(&end); 
    timeTaken = difftime(end,start);
    printf(FinalXOR);
    close(ptr);

    return 0;
}