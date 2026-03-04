*This project has been created as part of the 42 curriculum by traomeli.*
<style>
@import url('https://fonts.googleapis.com/css2?family=Bitcount+Prop+Double:wght@100..900&display=swap');
</style>

# <span style="font-family: Bitcount Prop Double; color: #87df23">Get Next Line </span>

## Description

<span style="color: #d10dd8;">***Get Next Line***</span> is a C function developed as part of the 42 curriculum.
The goal of this project is to implement a function that reads a file line by line,
handling dynamic memory allocation and various edge cases.
This project strengthens skills in file descriptor manipulation, buffer management,
and memory handling, serving as a foundation for future projects requiring file I/O operations.

## Instructions

### Compilation

Compile with the following command:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

### Usage

Include in header:

```c
#include "get_next_line.h"
```

Main exemple 01 :

```c
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
    int		fd;
    char	*line;

    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (EXIT_SUCCESS);
}
```
Main exemple 02 :

```c
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
    int		fd;
    char	*line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (EXIT_FAILURE);
    }
    line = get_next_line(fd);
    if (line == NULL)
    {
        close(fd);
        return (EXIT_FAILURE);
    }
    printf("%s\n", line);
    free(line);
      close(fd);
    return (EXIT_SUCCESS);
}
```
Note: <span style="font-family: Arial Black; background-color: #7e7d7e; color: #ffda07">printf("%s", line);</span> correctly displays the line even if it ends with '\n'.

### header guard explaination:
```c
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
# endif
# if BUFFER_SIZE <= 0
# undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif
# if BUFFER_SIZE == 2147483647
# undef BUFFER_SIZE
#  define BUFFER_SIZE 2147483646
# endif
``` 
- define 42 BUFFER_SIZE in default
- look if the BUFFER_SIZE less or equals <span style= "color: #98c2a6">0</span> then define BUFFER_SIZE to <span style= "color: #98c2a6">0</span>
- look if the BUFFER_SIZE equals <span style= "color : #1d78df">INT_MAX</span> then define BUFFER_SIZE to <span style= "color: #98c2a6">2147483646 ```int max - 1```</span>

### Expected Behavior (Summary)
- Handle memory correctly without leaks.
- Return exactly the next line on each call.
- Support interleaved reading from multiple `fd`.
- <span style= "color : #8abaf1">get_next_line()</span> exhibits undefined behavior if the file associated with the file descriptor is modified after the last call, while <span style= "color : #e5f394">read()</span> has not yet reached the end of the file.So if you make <span style= "color : #e5f394">close()</span> before <span style= "color : #e5f394">read()</span> it's an undefined behavior  


### Resources
- Man pages (`read`, `open`, `close`, `malloc`, `free`)
- Subject and guidelines 42
- [tutorial youtube](https://youtu.be/-Mt2FdJjVno?si=w4p8hlxgEDBkAHlJ)

### AI Usage

AI tools were used for clarification of certain concepts,
proofreading and assistance with README writing. Final decisions and
code belong to the project author.

