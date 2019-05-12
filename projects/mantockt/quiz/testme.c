#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int randi(int floor, int ceiling)
{
  return rand() % (ceiling - floor + 1) + floor;
}

char inputChar()
{
  // TODO: rewrite this function
  char characters[] = {'(', ')', '{', '}', '[', ']', ' ', 'a', 'b', 'c', 'd', 'x', '\0'};
  int len = (int)(sizeof(characters) / sizeof(char));

  return characters[randi(0, len - 1)]; // Non-inclusive of len
}

char *inputString()
{
  // TODO: rewrite this function
  size_t size = 6;
  char string[size];

  memset(string, '\0', size);

  for (int i = 0; i < size - 1; i++)
  {
    string[i] = (char)randi(97, 122);
  }

  return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0)
      state = 1;
    if (c == '(' && state == 1)
      state = 2;
    if (c == '{' && state == 2)
      state = 3;
    if (c == ' ' && state == 3)
      state = 4;
    if (c == 'a' && state == 4)
      state = 5;
    if (c == 'x' && state == 5)
      state = 6;
    if (c == '}' && state == 6)
      state = 7;
    if (c == ')' && state == 7)
      state = 8;
    if (c == ']' && state == 8)
      state = 9;
    if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  testme();
  return 0;
}
