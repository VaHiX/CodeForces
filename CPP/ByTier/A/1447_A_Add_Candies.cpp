// Problem: CF 1447 A - Add Candies
// https://codeforces.com/contest/1447/problem/A

/*
Code Purpose:
This program solves the problem of making all bags of candies contain an equal number of candies
by performing a series of operations. Each operation adds a specific number of candies to all bags
except one chosen bag. The strategy is to sequentially choose each bag and perform operations
that balance the total candies across all bags.

Algorithm:
1. For each test case, we perform 'n' operations.
2. In each operation j (from 1 to n), we choose bag j and add j candies to all other bags.
3. This ensures that by the end, all bags will have equal amounts of candies.

Time Complexity: O(n) per test case, where n is the number of bags.
Space Complexity: O(1) additional space (excluding input/output).

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", n); // Print the number of operations needed (equal to n)
    for (long p = 1; p <= n; p++) {
      printf("%ld\n", p); // For each operation, choose bag p (1-indexed)
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/