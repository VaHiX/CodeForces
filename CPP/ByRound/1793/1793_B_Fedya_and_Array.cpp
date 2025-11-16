// Problem: CF 1793 B - Fedya and Array
// https://codeforces.com/contest/1793/problem/B

/*
Purpose: This code solves the problem of reconstructing a circular array given the sum of local maxima (x) and the sum of local minima (y).
         The array must satisfy the constraint that adjacent elements differ by exactly 1.
         The algorithm constructs the minimal length array by:
         - First creating an increasing sequence from y to x,
         - Then decreasing back from x-1 to y+1,
         - The total length is 2*(x-y), which is minimal for the given sums.

Algorithms/Techniques:
- Greedy construction of array with specific sum constraints
- Mathematical derivation of minimal array length based on x and y
- Linear traversal to build the array

Time Complexity: O(x - y) per test case, which is the time to generate the array.
Space Complexity: O(1) additional space (excluding the output array)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    printf("%ld\n", 2 * (x - y)); // Output the minimal length of the array (2*(x-y))
    for (long p = y; p <= x; p++) { // First part: increasing from y to x
      printf("%ld ", p);
    }
    for (long p = x - 1; p > y; p--) { // Second part: decreasing from x-1 to y+1
      printf("%ld ", p);
    }
    puts(""); // Print newline after each array
  }
}


// https://github.com/VaHiX/CodeForces/