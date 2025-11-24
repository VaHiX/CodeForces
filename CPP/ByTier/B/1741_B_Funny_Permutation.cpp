// Problem: CF 1741 B - Funny Permutation
// https://codeforces.com/contest/1741/problem/B

/*
Code Purpose:
This program generates a "funny" permutation for a given integer n. A funny permutation satisfies two conditions:
1. Every element has at least one neighbor that differs by 1.
2. No element is in its original position (no fixed points).

Algorithm:
- For n = 3, it's impossible to create a funny permutation, so we output -1.
- For n != 3, we construct the permutation by placing numbers from 3 to n in order, followed by 2 and 1.
  This ensures:
  - No fixed points (since 1 and 2 are moved from their original positions)
  - Every element has a neighbor differing by 1 (the sequence is structured to maintain this condition)

Time Complexity: O(n) - A single loop runs from 3 to n, and printing is linear.
Space Complexity: O(1) - Only a constant amount of extra space is used, not counting the output.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 3) {
      puts("-1");  // Special case: impossible to create a funny permutation
    } else {
      for (long p = 3; p <= n; p++) {
        printf("%ld ", p);  // Print numbers from 3 to n in order
      }
      puts("2 1");  // Append 2 and 1 at the end to satisfy conditions
    }
  }
}


// https://github.com/VaHiX/CodeForces/