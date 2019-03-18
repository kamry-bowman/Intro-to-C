#include <stdio.h>
#include <stdlib.h>

/*
    Given a character pointer x (that points to an array of chars), and a
    character pointer y, copies the character contents of y over to x. Pointer
    arithmetic is necessary here. Also, make sure x points to a null terminator
    at its end to terminate it properly. 

    Example call:

    char buffer[1024];

    string_copy(buffer, "Hello!");
    printf("%s", buffer); // Prints "Hello!"
*/
void string_copy(char *x, char *y)
{
  int counter = 0;
  char *p = y;
  while (*p != '\0')
  {
    counter++;
    p++;
  }
  for (int i = 0; i <= counter; i++)
  {
    *(x + i) = *(y + i);
  }
  *(x + counter + 1) = '\0';
  printf("x: %s\ny: %s\n", x, y);
}

/*
    Searches the input string `str` for the first instance of the 
    character `c` (an unsigned char). This function returns a pointer
    that points to the first instance of the character `c` in the
    input string `str`.

    Do not use the `strchr` function from the standard library.
*/
char *find_char(char *str, int c)
{
  while (*str != c && *str != '\0')
  {
    str++;
  }
  if (*str == c)
  {
    return str;
  }
  else
  {
    return NULL;
  }
}

/*
    Searches the input string `haystack` for the first instance of
    the string `needle`. This function returns a pointer that points
    to the first instance of the string `needle` in the input
    string `haystack`. 

    Do not use the `strstr` function from the standard library.
*/
char *find_string(char *haystack, char *needle)
{
  char *candidate = find_char(haystack, *needle);

  while (candidate && *candidate != '\0')
  {
    // check if candidate is acceptable
    int i = 1;
    int violation = 0;

    while (needle[i] != '\0' && !violation)
    {
      if (needle[i] != candidate[i])
      {
        violation = 1;
      }
      else
      {
        i++;
      }
    }
    // if candidate is acceptable, return pointer to candidate, else
    // continue search at candidate + 1
    if (!violation)
    {
      return candidate;
    }
    candidate = find_char(candidate + 1, *needle);
  }
  return NULL;
}

#ifndef TESTING
int main(void)
{
  char buffer[1024];
  char *hello = "hello";
  string_copy(buffer, hello);
  char *found_char = find_char(hello, 'e');
  char *world = "woorld";
  char *found_string = find_string(world, "or");

  // printf("Found char: %s\n", found_char);
  // printf("Found string: %s\n", found_string);
  char *not_found = find_string(world, "Or");
  // printf("Found string: %s\n", not_found);

  return 0;
}
#endif
