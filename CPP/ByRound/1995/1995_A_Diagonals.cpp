// Problem: CF 1995 A - Diagonals
// https://codeforces.com/contest/1995/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (!k) {
      puts("0");
      continue;
    }
    k -= n; // Adjust k to account for the first row's chips
    long cnt(1); // Start with one diagonal already occupied
    for (long p = n - 1; k > 0 && p > 0; p--) {
      k -= p; // Decrease k by number of cells in current diagonal
      ++cnt; // Increment diagonal count
      if (k > 0) {
        k -= p; // Again decrease k by number of cells in current diagonal
        ++cnt; // Increment diagonal count
      }
    }
    printf("%ld\n", cnt);
  }
}
/*
Flowerbox:
Problem: Minimum number of occupied diagonals when placing k chips on an n x n board.
Diagonal is defined as cells where i + j = constant.

Algorithm:
- Place chips greedily to minimize the number of diagonals used.
- The idea is to fill diagonals with increasing capacity.
- First, we place one chip per row (or column) to maximize occupancy.
- Then, we assign remaining chips to diagonals starting from those with fewer cells.
- If a diagonal can hold more chips than needed, we still count it as occupied.

Time Complexity: O(n)
Space Complexity: O(1)

Techniques:
- Greedy placement on diagonals
- Simulation of diagonal occupancy
*/

// https://github.com/VaHiX/codeForces/