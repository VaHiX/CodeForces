// Problem: CF 1353 C - Board Moves
// https://codeforces.com/contest/1353/problem/C

/*
C. Board Moves
Purpose: Calculate the minimum number of moves to gather all figures on a single cell of an n×n board (n is odd).
Algorithm: Mathematical formula derivation for minimizing Manhattan distances from all cells to the center.
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem reduces to finding the sum of Manhattan distances from all cells to the center cell (n/2, n/2).
Each cell (i,j) has distance |i - n/2| + |j - n/2|.
We simplify this by observing symmetry and using the formula for sum of squares.
The derived formula is: 8 * n * (n+1) * (2*n+1) / 6 where n is halved before computation.
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    n /= 2; // halve n to work with half the board size
    ll res = 8 * n * (n + 1) * (2 * n + 1) / 6; // compute result using derived formula
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/