#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define GIGABYTE (1024*1024*1024)

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
    free(buf);
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
    free(buf);
}

off_t getFileSize(char * filename){
    int ptr;
    ptr = open(filename, O_RDONLY);
    off_t fileSize = lseek(ptr,(size_t)0, SEEK_END);
    close(ptr);
    return fileSize;
}

long int findReasonableBlocks(char * file, int blockSize){
    double time_used = 0.0;
    int fd;
    int doWrite = 0;
    time_t start, end;
    int blocksRead = 0;
    long int blockCount = 2;

    fd = open(file,O_RDONLY);
    if (fd == -1){
        doWrite =1;
    }

    // long long int gb = 1;
    // long int blockCount = gb*GIGABYTE/blockSize;
    int iter = 0;
    while (time_used <= 5.0){
        // printf("\n\t############ Iter %d ############\n",iter++);
        if(doWrite){
            // printf("Writing\n");
            fd = open(file,O_CREAT|O_WRONLY|O_TRUNC|O_SYNC, 0644);
            writeBlocks(fd,blockSize,blockCount);
            close(fd);
        }
        time(&start); 
        fd = open(file, O_RDWR,0644);
        blocksRead = readBlocks(fd,blockSize,blockCount);
        time(&end); 
        close(fd);
        time_used = difftime(end, start);
        // printf("BlocksRead in this iter - %d in time %f\n",blocksRead-1,time_used);
        blockCount = time_used == (double)0 ? blockCount*2 : 6*blockCount/time_used;
        // blockCount *= 2;
    }
    // printf("Time take to read %d Blocks of size %d Bytes => %.2f\n",blocksRead-1,blockSize,time_used);
    return blocksRead-1;
}

int main(int argc, char *argv[])
{

    long int blockCount;
    char *filename = argv[1];
    char *blocksize = argv[2];
    double cpu_time_used;
    time_t start, end;
    int fd;

    if(argc <= 2){
        printf("Incorrect Usage\nPlease enter ./run2 <filename> <block_size>");
        exit(0);
    }

    off_t fileSize;
    fileSize = getFileSize(filename);
    if (fileSize!=-1){
        if (fileSize/GIGABYTE < 5){
            printf("\nFile Size entered might be too low. Enter a bigger file!!\n");
            exit(0);
        }
    }

    time(&start); 
    blockCount = findReasonableBlocks(filename, atoi(blocksize));
    time(&end); 
    cpu_time_used = difftime(end,start);
    // printf("Time taken find Reasonable blocks ==> %.2f Seconds\n", cpu_time_used);
    printf("Number of Reasonable blocks ==> %li\n", blockCount);
    printf("File Size : \n");
    printf("%lld in time %.2f\n", (off_t)blockCount*atoi(blocksize),cpu_time_used);

    return 0;
}
