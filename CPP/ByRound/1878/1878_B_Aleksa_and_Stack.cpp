// Problem: CF 1878 B - Aleksa and Stack
// https://codeforces.com/contest/1878/problem/B

/*
Purpose: This code generates a strictly increasing array of positive integers of size n such that for every triple of consecutive elements a_i, a_{i+1}, a_{i+2}, the value 3 * a_{i+2} is not divisible by a_i + a_{i+1}. The approach uses an arithmetic sequence with a common difference of 2, starting from 1, which satisfies the condition due to properties of modular arithmetic.

Algorithms/Techniques: Arithmetic progression generation, modular arithmetic properties

Time Complexity: O(n) - Linear time per test case, as we simply iterate from 0 to n-1 and print values.
Space Complexity: O(1) - Only constant space is used, excluding the input/output buffers.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      // Generate numbers in arithmetic sequence: 1, 3, 5, 7, ...
      // This ensures all elements are odd and strictly increasing.
      printf("%ld ", 2 * p + 1);
    }
    puts(""); // Print newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/