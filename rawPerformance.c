#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define KILOBYTE (1024)
#define GIGABYTE (1024*1024*1024)
#define MEGABYTE (1024*1024)

unsigned int xor(char * buf, int bs){
    unsigned int result = 0;
    unsigned int *newbuf;
    newbuf = (unsigned int *)buf;
    for (int i = 0; i < bs; i++) {
        result ^= newbuf[i];
    }
    return result;
}

int readBlocks(int fd,int blockSize,long int blockCount){
    char * buf = (char * )malloc((blockSize));
    int count = 0;
    int n;
    lseek(fd, 0, SEEK_SET);
    while((n = read(fd,buf,blockSize))>0){
        if (count++ == blockCount){
            break;
        }
    }
    return count;
}

void writeBlocks(int fd,int blockSize,long int blockCount){
    char * buf = (char * )malloc((blockSize + 1));
    int count = 0;
    int i;
    for (i=0 ; i < blockSize+1 ; i++){
        // int rnd = rand() % 26;
        buf[i] = 'A';// + rnd;
    }
    buf[blockSize + 1] = '\0';
    while(count++ != blockCount){
        write(fd,buf,blockSize);
    }
}

off_t getFileSize(char * filename){
    int ptr;
    ptr = open(filename, O_RDONLY);
    off_t fileSize = lseek(ptr,(size_t)0, SEEK_END);
    close(ptr);
    return fileSize;
}

void dataForGraph(char * file){
    // double time_used = 0.0;
    off_t blockSizes[15] = {0,64, 128, 256, 512, 1024, 4*1024, 16*1024, 32*1024, 128*1024, 256*1024,512*1024, 1024*1024, 4*1024*1024, 16*1024*1024};
    // off_t blockSizes[15] = {0,512, 1024, 4*1024, 16*1024, 32*1024, 128*1024, 256*1024,512*1024, 1024*1024, 4*1024*1024, 16*1024*1024, 32*1024*1024, 128*1024*1024, 256*1024*1024};
    int fd;
    int i;
    long blockSize, blockCount;
    double readTime;
    time_t start, end;
    long long int fileSize;// = 3LL*1024*1024*1024;
    fileSize = getFileSize(file);
    printf("BlockSize\tReadSpeed\tReadTime\n");
    fd = open(file, O_RDONLY);
    // for(i=100 ; i<2000 ;){
    //     blockSize = i;
    //     blockCount = fileSize/blockSize;  
    //     // fd = open(file, O_CREAT | O_WRONLY | O_SYNC,  0644);
    //     // time(&start);
    //     // writeBlocks(fd,blockSize,blockCount);
    //     // time(&end);
    //     // close(fd);
    //     // writeTime = difftime(end,start);
    //     // printf("Write Time - %0.2f\n",writeTime);
    //     time(&start);
    //     readBlocks(fd,blockSize,blockCount);
    //     time(&end);
    //     readTime = difftime(end,start);
    //     // printf("\t\t\t\t\tRead Time - %0.2f\n",readTime);
    //     int block = (double)blockSize/KILOBYTE;
    //     // double writeSpeed = writeTime == 0 ? 0 : (double)blockSize/(MEGABYTE*writeTime);
    //     double readSpeed = readTime == 0 ? 0 : fileSize/(MEGABYTE*readTime);
    //     printf("%d KB\t\t%0.2f MiB/s\t%0.2f s\n",block,readSpeed,readTime);
    //     i += 100;
    // }

    for(i=1 ; i<15 ;i++){
        blockSize = blockSizes[i];
        blockCount = fileSize/blockSize;
        
        // fd = open(file, O_CREAT | O_WRONLY | O_SYNC,  0644);
        // time(&start);
        // writeBlocks(fd,blockSize,blockCount);
        // time(&end);
        // close(fd);
        // writeTime = difftime(end,start);
        // printf("Write Time - %0.2f\n",writeTime);
        time(&start);
        readBlocks(fd,blockSize,blockCount);
        time(&end);
        readTime = difftime(end,start);
        // printf("\t\t\t\t\tRead Time - %0.2f\n",readTime);
        double block = blockSize/(double)KILOBYTE;
        // double writeSpeed = writeTime == 0 ? 0 : (double)blockSize/(MEGABYTE*writeTime);
        double readSpeed = readTime == 0 ? 0 : fileSize/(MEGABYTE*readTime);
        printf("%.1f KB\t\t%0.1f MiB/s\t%0.1f s\n",block,readSpeed,readTime);
        // i += 100;
    }
    // close(fd);
}

int main(int argc, char *argv[])
{
    // long int blockCount;
    char *filename = argv[1];
    // char *blocksize = argv[2];
    // double cpu_time_used;
    // time_t start, end;

    if(argc <= 1){
        printf("Incorrect Usage\nPlease enter ./run <filename>");
        exit(0);
    }
    dataForGraph(filename);
    return 0;
}
