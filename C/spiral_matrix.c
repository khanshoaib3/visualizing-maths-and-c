#include <stdio.h>

int main(int argc, char *argv[])
{
  int n = 5;
  int arr[n][n];

  int temp = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      arr[i][j] = temp;
      ++temp;
      printf("%d\t", arr[i][j]);
    }
    printf("\n");
  }

  printf("\nIn Spiral Format:\n");

  int i = 0, j = 0;
  int max = n;
  int min = -1;
  for (int pass = n; pass > 1; pass--) {// Note: This will probably run one time extra (except if n is 3). Make it work with "pass > 2"
    // Top Left -> Top Right
    while (j < max) {
      printf("%d\t", arr[i][j]);
      ++j;
    }
    --j; // Move LEFT by one as it is out of bounds

    // Top Right -> Bottom Right
    ++i;
    while (i < max) {
      printf("%d\t", arr[i][j]);
      ++i;
    }
    --i; // Move UP by one as it is out of bounds

    // Bottom Right -> Bottom Left
    --j;
    while (j > min) {
      printf("%d\t", arr[i][j]);
      --j;
    }
    ++j;

    // Bottom Left -> Top Left - 1
    --i;
    while (i > min + 1) {
      printf("%d\t", arr[i][j]);
      --i;
    }
    ++i;

    // Move right by one and update min & max
    ++j;
    --max;
    ++min;
  }

  printf("\n");
  return 0;
}
