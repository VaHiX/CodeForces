// Problem: CF 1236 C - Labs
// https://codeforces.com/contest/1236/problem/C

/*
Code Purpose:
This code solves the problem of optimally dividing n^2 labs into n groups of n labs each,
such that the minimum flow (f(A,B)) from any group A to any group B is maximized.
The algorithm uses a specific pattern to assign labs to groups to achieve this optimal division.
It leverages the property that grouping labs in a particular order based on their indices
helps balance the water flow (f) between groups.

Algorithms/Techniques:
- Pattern-based grouping: Uses bit manipulation and arithmetic to assign labs to groups.
- Mathematical construction: Orders labs in a way that balances the outgoing flow from each group.

Time Complexity: O(n^2) - as we iterate through all n^2 labs to assign them to groups.
Space Complexity: O(1) - only using a constant amount of extra space (variables p, q, n).
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  for (long p = 1; p <= n; p++) {
    for (long q = 1; q <= n; q++) {
      // Assign lab numbers using a specific formula based on parity of q
      // If q is odd, assign lab number in ascending order within group
      // If q is even, assign lab number in descending order within group
      printf("%ld ", (q & 1) ? ((q - 1) * n + p) : (q * n - p + 1));
    }
    puts(""); // Move to next line after printing all labs in a group
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/