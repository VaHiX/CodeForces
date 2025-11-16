// Problem: CF 1173 B - Nauuo and Chess
// https://codeforces.com/contest/1173/problem/B

/*
Code Purpose:
This program finds the smallest square chessboard (of size m x m) on which n chess pieces can be placed such that the constraint |r_i - r_j| + |c_i - c_j| >= |i - j| is satisfied for all pairs of pieces i and j. The solution uses a constructive approach where pieces are placed in a specific pattern to satisfy the distance condition.

Algorithms/Techniques:
- Constructive algorithm
- Greedy placement strategy

Time Complexity: O(n)
Space Complexity: O(1)

The first n/2 + 1 pieces are placed along the first column (1, 1), (2, 1), ..., (n/2 + 1, 1).
The remaining pieces are placed along the last row (n/2 + 1, 2), ..., (n/2 + 1, n - n/2).
This ensures all pairwise constraints are satisfied due to the geometric properties of the layout.
*/
#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long m = n / 2 + 1;  // Calculate minimum board size
  printf("%ld\n", m);
  for (long p = 1; p <= m; p++)
    printf("%ld 1\n", p);  // Place first m pieces in first column
  for (long p = 2; p <= n - m + 1; ++p)
    printf("%ld %ld\n", m, p);  // Place remaining pieces in last row
  return 0;
}


// https://github.com/VaHiX/CodeForces/