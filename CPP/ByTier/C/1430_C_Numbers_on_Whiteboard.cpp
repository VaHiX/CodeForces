// Problem: CF 1430 C - Numbers on Whiteboard
// https://codeforces.com/contest/1430/problem/C

/*
Code Purpose:
This code solves the problem of minimizing the final number left on the board after performing
a series of operations on numbers 1 to n. In each operation, two numbers a and b are selected,
and their average (rounded up) is written back. The strategy is to always combine the largest
number with the current result to minimize the growth of the final value.

Algorithm:
- Greedily combine the largest number available with the current running result.
- Use a simple loop to simulate the process, keeping track of the current largest number.
- The process mimics a binary heap-like merging strategy to keep the growth minimal.

Time Complexity: O(n) per test case
Space Complexity: O(1) - only using a few variables for computation
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts("2"); // The minimum possible value is always 2 for n >= 2
    long cur(n); // Start with the largest number
    for (long p = n - 1; p >= 1; p--) {
      printf("%ld %ld\n", p, cur); // Print operation: combine p and cur
      cur = (cur + p + 1) / 2; // Update cur to the ceiling of average of cur and p
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/