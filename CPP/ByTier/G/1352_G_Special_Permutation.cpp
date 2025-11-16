// Problem: CF 1352 G - Special Permutation
// https://codeforces.com/contest/1352/problem/G

/*
Code Purpose:
This code solves the problem of finding a special permutation of length n where the absolute difference between any two adjacent elements is between 2 and 4, inclusive. 
It constructs such a permutation by separating odd and even numbers in a specific order to ensure the difference constraint is satisfied.

Algorithms/Techniques:
- Greedy construction of permutation
- Separation of odd and even numbers to maintain valid differences
- Special handling for small values of n (n < 4)

Time Complexity: O(n) - We iterate through the numbers a constant number of times.
Space Complexity: O(1) - Only using a constant amount of extra space (excluding output).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n < 4) {
      // For n < 4, it's impossible to satisfy the difference constraint
      puts("-1");
      continue;
    }
    // Print all odd numbers in descending order
    for (long p = n; p > 0; p--) {
      if (p & 1) {
        printf("%ld ", p);
      }
    }
    // Print 4 and 2 (these are chosen to maintain the constraint with previous odd numbers)
    printf("%d %d ", 4, 2);
    // Print all even numbers starting from 6 in ascending order
    for (long p = 6; p <= n; p += 2) {
      printf("%ld ", p);
    }
    puts(""); // New line after each permutation
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/