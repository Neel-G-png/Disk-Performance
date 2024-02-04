#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
// #include <sys/random.h>

unsigned int xor(char * buf, int bs){
    unsigned int result = 0;
    unsigned int *newbuf;
    newbuf = (unsigned int *)buf;
    for (int i = 0; i < bs; i++) {
        result ^= newbuf[i];
    }
    return result;
}

unsigned int readBlocks(int fd,int blockSize,int blockCount){
    char * buf = (char * )malloc((blockSize));
    unsigned int xorcumulate = 0; 
    int count = 0;
    int n;

    while((n = read(fd,buf,blockSize))>0){
        xorcumulate ^= xor(buf,n/4);
        if (count++ == blockCount){
            break;
        }
        // printf("count - %d\n",count);
    }
    // return count;
    free(buf);
    return xorcumulate;
}

void writeBlocks(int fd,int blockSize,int blockCount){
    char * buf = (char * )malloc((blockSize+1));
    int count = 0;
    int i;

    // getrandom(buf, blockSize, 0);
    for (i=0 ; i < blockSize+1 ; i++){
        int rnd = rand() % 26;
        buf[i] = 'A' + rnd;
    }
    buf[blockSize + 1] = '\0';
    while(count++ != blockCount){
        write(fd,buf,blockSize);
    }
    free(buf);
}

int main(int argc, char *argv[])
{
    int ptr;
    unsigned int xor_final;
    char *action = argv[2];
    char *filename = argv[1];
    char *blocksize = argv[3];
    char *blockcount = argv[4];
    // char *cache = argv[5];
    double cpu_time_used;
    time_t start, end;

    if(argc <= 4){
        printf("Incorrect Usage\nPlease enter ./run <filename> [-r|-w] <block_size> <block_count>");
        exit(0);
    }
    ptr = open(filename, O_RDWR | O_APPEND );
    off_t fileSize = lseek(ptr,(size_t)0, SEEK_END);
    printf("File Size - %lld Bytes\n",fileSize);
    close(ptr);
    if (strcmp(action,"-r")==0){
        ptr = open(filename, O_RDONLY);
        // if (strcmp(cache,"-cf")==0){
        //     if (fcntl(ptr, F_NOCACHE, 1) == -1) {
        //         perror("Error advising kernel");
        //         close(ptr);
        //         exit(EXIT_FAILURE);
        //     }
        // }
        time(&start); 
        xor_final = readBlocks(ptr, atoi(blocksize), atoi(blockcount));
        time(&end); 
        cpu_time_used = difftime(end,start);
        printf("Calculated XOR for the input file is ==> %u\n", xor_final);
        printf("Calculated XOR in time               ==> %.2f\n", cpu_time_used);
        close(ptr);
    }
    else if (strcmp(action,"-w")==0){
        ptr = open(filename, O_CREAT | O_WRONLY | O_SYNC,  0644);
        time(&start);
        writeBlocks(ptr, atoi(blocksize), atoi(blockcount));
        time(&end);
        cpu_time_used = difftime(end,start);
        printf("Time taken to create this file ==> %.2f\n", cpu_time_used);
        close(ptr);
    }
    return 0;
}

