_This project has been created as part of the 42 curriculum by gumagni_

## Description

**get_next_line** is a C project that implements a function to read a file descriptor line by line. The function reads from a file descriptor and returns one line at a time, including the newline character when present.

### Goal

The objective of this project is to:
- Learn and apply file descriptor operations in C
- Understand buffer management and dynamic memory allocation
- Implement efficient string manipulation and parsing
- Handle edge cases such as files without newlines, empty files, and multiple consecutive calls

### Key Features

- **Line-by-line reading**: Read from any file descriptor one line at a time
- **Configurable buffer size**: The `BUFFER_SIZE` macro allows customization of the internal buffer
- **Memory efficiency**: Uses static variables to maintain state across function calls
- **Robust error handling**: Proper handling of read errors and memory allocation failures
- **Bonus version**: Includes support for multiple file descriptors simultaneously

## Instructions

### Compilation

To compile the project, use the provided Makefile:

```bash
make              # Compile the mandatory part
make bonus        # Compile the bonus part
make clean        # Remove object files
make fclean       # Remove object files and executable
make re           # Recompile everything
```

### Basic Usage

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Configuration

The `BUFFER_SIZE` can be defined at compile time:

```bash
gcc -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c
```

### Testing

The project includes a test suite in the `gnlTester/` directory. To run tests:

```bash
cd gnlTester
make test_mandatory    # Test mandatory functions
make test_bonus        # Test bonus functions
```

## Algorithm Explanation and Justification

### Overview

The `get_next_line` function uses a **static buffer approach** to maintain state across multiple function calls while efficiently managing memory.

### How It Works

1. **Static Buffer**: A static variable `rest` persists across function calls, storing leftover content from previous reads that doesn't contain a newline.

2. **Read Loop**: The `read_until_newline` function repeatedly reads chunks from the file descriptor (using `BUFFER_SIZE` bytes per read) until a newline is found or EOF is reached.

3. **String Concatenation**: Each chunk is concatenated to the current line using `ft_strjoin`, building the complete line incrementally.

4. **Line Extraction**: Once a newline is found, the `extract_line` function:
   - Splits the content at the newline character
   - Returns the line (including the newline)
   - Stores the remainder in the `rest` buffer for the next call

5. **State Management**: The next call to `get_next_line` begins by using the previously stored `rest` content, ensuring continuity across calls.

### Why This Algorithm?

- **Efficiency**: By using a configurable `BUFFER_SIZE`, we balance between memory usage and the number of system calls
- **Simplicity**: The static buffer approach is straightforward and doesn't require external state management
- **Robustness**: Handles various edge cases including:
  - Files without newlines
  - Empty files
  - Multiple consecutive newlines
  - Very large lines (larger than buffer size)

### Time Complexity

- **Per call**: O(n) where n is the length of the returned line (due to string concatenations)
- **Overall for file reading**: O(m) where m is the total file size

### Space Complexity

- O(BUFFER_SIZE) for the internal read buffer
- O(line_length) for the returned line

## Resources

### Documentation
- [man read(2)](https://linux.die.net/man/2/read) - File descriptor read operations
- [man open(2)](https://linux.die.net/man/2/open) - File descriptor creation and manipulation
- [C Dynamic Memory Allocation](https://en.cppreference.com/w/c/memory) - malloc, free, and memory management

### References
- [Buffer I/O in C](https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm) - Understanding buffered input
- [File Descriptors in Unix](https://www.computerhope.com/unix/ushell.htm) - File descriptor concepts
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/) - Understanding static storage duration

### AI Usage

AI assistance was used in the following areas:

- **Memory Management**: Verification of proper memory allocation patterns and leak detection strategies
- **Error Handling**: Suggestions for comprehensive edge case handling (empty files, missing newlines, read errors)
- **Testing**: Assistance with understanding test cases and debugging failed test scenarios
- **Documentation**: Help creating clear, comprehensive README documentation

## Technical Choices

### Static Variables vs. Context Structures

We chose **static variables** over passing a context structure because:
- Simpler API (only requires fd parameter)
- Matches the project specification
- Easier to use from client code

### String Concatenation Approach

We use repeated `ft_strjoin` calls instead of dynamic array resizing because:
- Clearer, more maintainable code
- Reasonable performance for typical line sizes
- Simpler memory management logic

### Single File Descriptor Limitation (Mandatory)

The mandatory version supports only one file descriptor at a time due to the static `rest` variable. The bonus version addresses this by:
- Using an array of static buffers
- Enabling simultaneous reading from multiple file descriptors