// Problem: CF 2091 C - Combination Lock
// https://codeforces.com/contest/2091/problem/C

/*
C. Combination Lock
Purpose: Generate a permutation of numbers from 1 to n such that every cyclic shift has exactly one fixed point.
Algorithm/Techniques:
- For odd n: Construct a specific pattern where odd numbers are placed first followed by even numbers.
- For even n: It's impossible to satisfy the condition, so output -1.
Time Complexity: O(n) per test case, as we iterate through the numbers once to construct the permutation.
Space Complexity: O(1) extra space (not counting input/output), since we only use a few variables and print results directly.

Input:
- t: number of test cases
- n: size of permutation for each test case

Output:
- A valid permutation if possible, otherwise -1
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2 == 0) { // If n is even, no valid permutation exists
      puts("-1");
      continue;
    }
    for (long p = 1; p <= n; p += 2) { // Print odd numbers first
      printf("%ld ", p);
    }
    for (long p = 2; p <= n; p += 2) { // Then print even numbers
      printf("%ld ", p);
    }
    puts(""); // Newline after each permutation
  }
}


// https://github.com/VaHiX/codeForces/