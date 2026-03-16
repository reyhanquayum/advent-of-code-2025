#include <stdio.h>
#include <stdlib.h>

// need some sort of mod operator
// we can simulate where we are in the dial if we know
// 1. where we start
// 2. what move we took
//
// so for example we will always start at 50
//
// new_position = (current_position + direction * distance) mod 100


int main(){
  int is_ok = EXIT_FAILURE;

  FILE *fptr;
  fptr = fopen("input.txt", "r");

  if (!fptr){
    perror("file opening failed");
    return is_ok;
  }

  char op[8];
  int dir;
  long dist;
  int pos = 50;
  int cnt = 0;

  while (fgets(op, 8, fptr)){

    // we have a string like R38
    // want to extract direction, distance from this
    if (op[0] == 'L'){
      dir = -1;
    }
    else{
      dir = 1;
    }
    // rest of the array is our number

    dist = strtol(&op[1], NULL, 10);

    pos = (pos + dir * dist) % 100;
    if (pos == 0){
      ++cnt;
    }

  }
  fclose(fptr);
  printf("count: %d", cnt);
}
