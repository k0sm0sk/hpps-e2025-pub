#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));

  int x = rand() % 10;
  printf("%d\n", x);

  printf("OK, I am thinking of a number in the range [0,4] - see if you can guess it!\n");
  printf("Type a number and press enter to make a guess.\n");

  int guess;

  // if (scanf("%d", &guess) != 1) {
  //   printf("Wrong input type, only input integers.\n");
  // }
  while (scanf("%d", &guess) == 1) {
    if (guess < x) {
      printf("Too low!\n");
    } else if (guess > x) {
      printf("Too high!\n");
    } else {
      x = rand() % 10;
      printf("Too high! %d!\n", x);
    }
  }
}
