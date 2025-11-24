// Problem: CF 535 A - Tavas and Nafas
// https://codeforces.com/contest/535/problem/A

/*
 * Problem: Tavas and Nafas
 * Purpose: Convert an integer score (0-99) into its English word representation.
 *          The output consists only of lowercase letters and hyphens.
 *
 * Algorithm:
 *   - Handle special cases for numbers 0, 10-19 directly.
 *   - For numbers 20-99:
 *     - Extract tens digit (t) and units digit (d).
 *     - Print the tens word (twenty, thirty, ..., ninety).
 *     - If units digit > 0, append a hyphen and then the units word.
 *
 * Time Complexity: O(1) - The algorithm uses a fixed number of operations,
 *                     regardless of input size (bounded by 0-99).
 *
 * Space Complexity: O(1) - Only a fixed amount of space is used for variables
 *                          and output strings.
 */

#include <cstdio>
int main() {
  int n;
  scanf("%d\n", &n);
  if (n == 0) {
    puts("zero");
  } else if (n == 10) {
    puts("ten");
  } else if (n == 11) {
    puts("eleven");
  } else if (n == 12) {
    puts("twelve");
  } else if (n == 13) {
    puts("thirteen");
  } else if (n == 14) {
    puts("fourteen");
  } else if (n == 15) {
    puts("fifteen");
  } else if (n == 16) {
    puts("sixteen");
  } else if (n == 17) {
    puts("seventeen");
  } else if (n == 18) {
    puts("eighteen");
  } else if (n == 19) {
    puts("nineteen");
  } else {
    int t = n / 10;   // Extract tens digit
    int d = n % 10;   // Extract units digit
    if (t > 1) {
      if (t == 2) {
        printf("twenty");
      }
      if (t == 3) {
        printf("thirty");
      }
      if (t == 4) {
        printf("forty");
      }
      if (t == 5) {
        printf("fifty");
      }
      if (t == 6) {
        printf("sixty");
      }
      if (t == 7) {
        printf("seventy");
      }
      if (t == 8) {
        printf("eighty");
      }
      if (t == 9) {
        printf("ninety");
      }
    }
    if (t > 1 && d > 0) {
      printf("-");  // Add hyphen between tens and units if both exist
    }
    if (d > 0) {
      if (d == 1) {
        printf("one");
      }
      if (d == 2) {
        printf("two");
      }
      if (d == 3) {
        printf("three");
      }
      if (d == 4) {
        printf("four");
      }
      if (d == 5) {
        printf("five");
      }
      if (d == 6) {
        printf("six");
      }
      if (d == 7) {
        printf("seven");
      }
      if (d == 8) {
        printf("eight");
      }
      if (d == 9) {
        printf("nine");
      }
    }
    puts("");  // Print newline at the end
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/