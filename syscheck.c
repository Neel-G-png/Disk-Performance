#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define KILOBYTE (1024)
#define GIGABYTE (1024*1024*1024)
#define MEGABYTE (1024*1024)

void readTest(int fd,int blockSize){
    char * buf = (char * )malloc((blockSize));
    int n;
    lseek(fd, 0, SEEK_SET);
    n = read(fd,buf,blockSize);
    return;
}

void lseekTest(int fd){
    lseek(fd, 1, SEEK_CUR);
}

void randTest(){
    int rnd ;
    rnd = rand() % 26;
}

void writeTest(int fd,int blockSize){
    char * buf = (char * )malloc((blockSize));
    // buf[0] = '\0';
    write(fd,buf,blockSize);
}

off_t getFileSize(char * filename){
    int ptr;
    ptr = open(filename, O_RDONLY);
    off_t fileSize = lseek(ptr,(size_t)0, SEEK_END);
    printf("File Size - %lld\n",fileSize);
    close(ptr);
    return fileSize;
}

void runTests(char * filename){
    off_t blockSize = 1;
    int fd;
    off_t i;
    time_t start, end;
    double readTime, writeTime, lseekTime, randTime;
    long long int fileSize;
    fileSize = getFileSize(filename);

    fd = open(filename, O_RDWR);

    printf("SysCall\tSpeed(Mib/s)\tSpeed(B/s)\n");
    time(&start);
    for(i=0;i<fileSize;i++){
        readTest(fd,blockSize);
    }
    time(&end);
    readTime = difftime(end,start);
    printf("%s\t%.2f\t\t%0.2f\n","Read",fileSize/((double)MEGABYTE*readTime),fileSize/((double)readTime));

    time(&start);
    for(i=0;i<fileSize;i++){
        writeTest(fd,blockSize);
    }
    time(&end);
    writeTime = difftime(end,start);
    printf("%s\t%.2f\t\t%0.2f\n","Write",fileSize/((double)MEGABYTE*writeTime),fileSize/((double)writeTime));

    time(&start);
    for(i=0;i<fileSize;i++){
        lseekTest(fd);
    }
    time(&end);
    lseekTime = difftime(end,start);
    printf("%s\t%.2f\t\t%0.2f\n","Lseek",fileSize/((double)MEGABYTE*lseekTime),fileSize/((double)lseekTime));

    time(&start);
    for(i=0;i<500000000;i++){
        randTest();
    }
    time(&end);
    randTime = difftime(end,start);
    printf("%s\t%.2f\t\t%0.2f\n","Rand",50000000/((double)MEGABYTE*randTime),50000000/((double)randTime));
}

int main(int argc, char *argv[])
{
    char *filename = argv[1];

    if(argc <= 1){
        printf("Incorrect Usage\nPlease enter ./run <filename>");
        exit(0);
    }
    runTests(filename);
    return 0;
}
