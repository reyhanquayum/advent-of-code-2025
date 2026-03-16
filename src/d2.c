#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 256

long ipow(int base, int exp){
  long result = 1;
  for (int i = 0; i < exp; i++) result *= base;
  return result;
}

typedef struct {
  long current;
  long end;
} RangeIter;

RangeIter range_iter(long start, long end) {
  return (RangeIter){start, end};
}

int range_next(RangeIter* it, long* val){
  if (it->current >= it->end) return 0; // done

  *val = it->current;
  it->current += 1; //step is always 1 dw ab it
  return 1; // returns 1 if has more
}

int isInvalid_v2(long val){
  char s[32];
  int len = snprintf(s, sizeof(s), "%ld", val);
  if (len % 2 != 0) return 1;

  // memcmp returns 0 if equal, so if 0 this is invalid and resolves to 1
  return memcmp(s, s + len / 2, len/2) == 0;
}

int isvalid(int val){
  // 1. convert val to string
  // 2. if len(string) % 2 != 0 -> return 1
  // 3. divide string in half
  // 4. if halves equal eachother, return 0

  char val_as_str[32]; // largest possible int is at most 10 digits plus a possible minus sign plus null terminator

  snprintf(val_as_str, sizeof(val_as_str), "%d", val);

  int len = strlen(val_as_str);

  if (len % 2 != 0){
    return 1; // automatically valid if odd number of chars
  }

  char first_half[16];
  char sec_half[16];

  strncpy(first_half, val_as_str, len / 2);
  first_half[len / 2] = '\0'; // STRNCPY DOESNT NULL TERMINATE REMEMBER TO DO THAT BRUH
  strncpy(sec_half, &val_as_str[len/2], len / 2);
  sec_half[len / 2] = '\0';

  if (strcmp(first_half, sec_half) == 0){ // strcmp returns 0 if strings are equal
    return 0; // invalid
  }

  return 1;
}

int main(){
  // honestly, if an ID has an odd num of characters it's automatically valid -> only need to look at IDs with an even number of digits or of even length. hmm
  // but we are going for a range. we're given ranges. if both the. we can completely skip computing values for a range if len(start) == len(end) && len(start) % 2 != 0 -> which means all of the values in this range have an odd number of digits which make them valid IDs. ah how to get a range in C though? python it's easy... i suppose we'll have to implement it ourselves

  FILE *fptr;
  fptr = fopen("input.txt", "r");

  if (!fptr){
    perror("file opening failed");
    return EXIT_FAILURE;
  }

  // what we're gonna get is just one long string with commas in it. is there any preprocessing we can do while processing file? ehh i dont really care lets just take it.
  // question is, what size array to allocate for this one big line? just do 1024 and call it a day.
  char ranges[2048];
  int cnt = 0;

  fgets(ranges, sizeof(ranges), fptr);
  // this could fail but i dont really care about error handling...

  // now we need to separate ranges by comma

  long strt;
  long ed;
  long starts[64], ends[64];

  char *range = strtok(ranges, ",");
  while (range){
  // we now have a string like '24-56' -> split this by dash and convert both tokens to int
    char *dash = strchr(range, '-'); // find dash
    *dash = '\0'; // split string there
    starts[cnt] = strtol(range, NULL, 10);
    ends[cnt] = strtol(dash + 1, NULL, 10);
    cnt++;
    range = strtok(NULL, ","); // when we pass NULL as first arg it means continue from where you left off in last string
  //
  //   RangeIter rit = range_iter(strt, ed);
  //   int val;
  //
  //   while (range_next(&rit, &val)){
  //     // check if current val is invalid id
  //     // reminder: invalid id is something like 1010 which repeats 10. or 99. or 22.
  //     // or 1188511885
  //     if (isInvalid_v2(val) == 1)
  //       invalids[cnt++] = val;
  //   }
  // }
  // int sum = 0;
  // for (int i = 0; i < SIZE; i++){
  //   sum += invalids[i];
  }


  long sum = 0;
  int evens[] = {2, 4, 6, 8, 10};
  int size = sizeof(evens) / sizeof(evens[0]);
  // ok so for each even length 2, 4, 6, 8, 10
  // iterate over all (d = length / 2) digit numbers
  // compute n * (10^d + 1)
  // check if that falls within any of the input ranges
  // if yes, add to sum
  for (int i = 0; i < size; i++){
    int d = evens[i] / 2;

    for (long n = ipow(10, d-1); n < ipow(10, d); n++){
      long candidate = n * (ipow(10, d) + 1);

      for (int i = 0; i < cnt; i++){
        if (candidate >= starts[i] && candidate <= ends[i]){
          sum += candidate;
        }
      }
    }
  }
  printf("%ld", sum);

}
