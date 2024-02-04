# Operating Systems Final Project

This project includes a series of scripts and programs for various file operations and performance measurements. Below are the instructions for running each file.

## Files and Usage

### 1. `run.c`
This program allows for read or write operations on a specified file with defined block size and count.

**Usage:** 
 ⁠
./run <filename> [-r|-w] <block_size> <block_count>

- `<filename>`: Name of the file to read or write.
- `[-r|-w]`: Operation mode (read or write).
- `<block_size>`: Size of each block in bytes.
- `<block_count>`: Number of blocks to read/write.

### 2. `run2.c`
This program handles file creation or reading of existing files, aiming to determine a total size that can be read in a reasonable time.

**Usage:** 

./run2 <filename> <block_size>

- `<filename>`: Name of the existing file (must be >10GB) or new file to create.
- `<block_size>`: Block size for reading/writing.

### 3. `fast.c`
Calculates XOR on the contents of a file as quickly as possible.

**Usage:** 

./fast <file_to_read>

- `<file_to_read>`: File on which to perform the XOR operation.

### 4. `Part2.sh`
Runs `run2.c` with multiple block sizes to compare performance.

**Usage:**

bash Part2.sh : and then enter filepath when prompted

- `<filename>`: Large file for performance comparison.

### 5. `Part3.sh`
Compares read speeds in MiB/s for different block sizes.

**Usage:**

bash Part3.sh : and then enter filepath when prompted

- `<filename>`: Reasonably large file for accurate speed comparison.

### 6. `Part4.sh`
Compares read rates of cached and non-cached files.

**Usage:**

bash Part4.sh : and then enter filepath when prompted

- `<filename>`: Reasonably large file to ensure full read.

### 7. `Part5.sh`
Compares the performance of various system calls with a block size of 1.

**Usage:**

bash Part5.sh : and then enter filepath when prompted

- `<filename>`: File for system call performance comparison.

## Additional Notes
- Ensure you have the necessary permissions to execute these scripts.
- For best results, especially in performance comparisons, use files of appropriate sizes as mentioned in each script's description.
