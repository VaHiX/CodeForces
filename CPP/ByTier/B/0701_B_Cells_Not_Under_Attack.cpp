// Problem: CF 701 B - Cells Not Under Attack
// https://codeforces.com/contest/701/problem/B

/*
B. Cells Not Under Attack
Algorithm: Track rows and columns that are attacked by rooks. For each new rook, calculate how many cells are no longer under attack.
Time Complexity: O(m), where m is the number of rooks.
Space Complexity: O(n), for storing row and column status.

Input:
- n: size of the chessboard (n x n)
- m: number of rooks
- For each of the m rooks, input their row and column coordinates

Output:
- For each rook placed, print the number of cells not under attack
*/

#include <cstdio>
#include <vector>
int main() {
  long long n, m;
  scanf("%lld %lld\n", &n, &m);
  std::vector<bool> rows(n + 1, 0); // Track which rows are occupied
  std::vector<bool> cols(n + 1, 0); // Track which columns are occupied
  long long takenRows(0), takenCols(0); // Count of occupied rows and columns
  long long safe(n * n); // Initially all cells are safe
  while (m--) {
    long long r, c;
    scanf("%lld %lld\n", &r, &c);
    if (!rows[r]) { // If row r is not yet occupied
      rows[r] = 1;
      ++takenRows;
      safe -= (n - takenCols); // Reduce safe cells by number of unoccupied columns
    }
    if (!cols[c]) { // If column c is not yet occupied
      cols[c] = 1;
      ++takenCols;
      safe -= (n - takenRows); // Reduce safe cells by number of unoccupied rows
    }
    printf("%lld ", safe);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/