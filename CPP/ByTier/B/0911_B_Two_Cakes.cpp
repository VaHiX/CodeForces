// Problem: CF 911 B - Two Cakes
// https://codeforces.com/contest/911/problem/B

/*
Algorithm: Brute Force
Approach:
- We try all possible ways to split the n plates between the two cakes.
- For each split (p plates for cake a, q = n - p plates for cake b), we calculate:
  - How many pieces of cake a can be distributed per plate: a / p
  - How many pieces of cake b can be distributed per plate: b / q
  - The minimum of these two values gives the minimum number of pieces per plate for this split.
- We keep track of the maximum such minimum value over all splits.
Time Complexity: O(n)
Space Complexity: O(1)

The key insight is that given a fixed allocation of plates to cakes, the optimal distribution is to fill each plate as evenly as possible (hence a/p and b/q).
*/
#include <cstdio>
int main() {
  long n, a, b;
  scanf("%ld %ld %ld", &n, &a, &b);
  long numPieces(0);
  for (long p = 1; p < n; p++) {
    long q = n - p;
    long x = a / p;
    long y = b / q;
    long z = (x < y) ? x : y;
    numPieces = (numPieces > z) ? numPieces : z;
  }
  printf("%ld\n", numPieces);
  return 0;
}


// https://github.com/VaHiX/CodeForces/