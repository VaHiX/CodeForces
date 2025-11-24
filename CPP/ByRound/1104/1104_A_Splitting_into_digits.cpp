// Problem: CF 1104 A - Splitting into digits
// https://codeforces.com/contest/1104/problem/A

#include <cstdio>
// Flowerbox:
// Purpose: This code solves the problem of splitting a given number 'n' into digits such that 
//          the number of different digits in the partition is minimized.
// Algorithm/Techniques: Greedy approach - use as many 9s as possible, then use the remainder as the last digit.
// Time Complexity: O(1) - The algorithm performs constant time operations regardless of input size (since n <= 1000).
// Space Complexity: O(1) - Only a fixed amount of space is used for storing variables.

int main() {
  long n;
  scanf("%ld", &n); // Read the input number
  printf("%ld\n", n); // Print the number of digits in the result (which is n if we use all 1s)
  for (long p = 0; p < n; p++) { // Loop to print 'n' ones
    printf("1 ");
  };
  puts(""); // Print a newline at the end
  return 0;
}

// https://github.com/VaHiX/codeForces/