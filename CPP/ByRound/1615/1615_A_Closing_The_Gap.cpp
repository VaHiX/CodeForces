// Problem: CF 1615 A - Closing The Gap
// https://codeforces.com/contest/1615/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x; // accumulate total sum of all tower heights
    }
    s %= n; // remainder when total sum is divided by number of towers
    puts(s ? "1" : "0"); // if remainder is non-zero, minimum ugliness is 1; otherwise 0
  }
}
/*
A. Closing The Gap

Algorithms/Techniques: Greedy approach, mathematical analysis of distribution

Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to minimize the difference between maximum and minimum tower heights
by redistributing blocks among towers. 

Key insight:
- If total sum of blocks can be evenly distributed among n towers, 
  then we can make all towers have equal height (ugliness = 0).
- Otherwise, there will be a remainder when dividing total by n, 
  which means at least one tower must be taller than others, resulting in ugliness = 1.

The code computes the sum of all elements and takes modulo with n.
If the result is 0, all blocks can be equally distributed => ugliness = 0.
Otherwise, some blocks will remain unbalanced => ugliness = 1.
*/

// https://github.com/VaHiX/codeForces/