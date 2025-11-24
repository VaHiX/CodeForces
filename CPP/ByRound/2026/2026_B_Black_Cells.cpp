// Problem: CF 2026 B - Black Cells
// https://codeforces.com/contest/2026/problem/B

/*
B. Black Cells
Algorithm: Binary search on answer + greedy verification
Time Complexity: O(n * log(max_value)) per test case
Space Complexity: O(n)

The problem is to find the minimum k such that all given cells can be painted black using operations 
that allow choosing two white cells at distance at most k and painting them black. We can also paint 
at most one extra cell not in the list.

Approach:
1. Binary search on the value of k (from 0 to 1e18)
2. For each k, verify whether it's possible to paint all required cells.
3. Verification is done greedily by scanning through the sorted array and trying to cover 
   consecutive elements with operations. If a gap larger than k is found, we have to place 
   an extra cell.

Key Variables:
- lb: lower bound of binary search
- ub: upper bound of binary search
- md: mid-point in binary search
- zz: number of extra cells needed (if > 1, then not possible with current k)
- x: flag indicating whether the current position is part of previous operation
*/

#include <stdio.h>
int t, n;
long long a[2222];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
      scanf("%lld", a + i);
    long long lb = 0, ub = 1e18;
    while (ub - lb > 1) {
      long long md = lb + (ub - lb) / 2;
      int zz = 0, x, i;
      for (x = 0, i = 0; i < n; ++i) {
        if (i && a[i] - a[i - 1] > md)
          zz += x, x = 0; // If gap exceeds k, we must place an extra cell
        x ^= 1; // Toggle the flag to indicate that next position will be covered
      }
      zz += x; // Add final group of cells
      if (zz > 1)
        lb = md;
      else
        ub = md;
    }
    printf("%lld\n", ub);
  }
}


// https://github.com/VaHiX/codeForces/