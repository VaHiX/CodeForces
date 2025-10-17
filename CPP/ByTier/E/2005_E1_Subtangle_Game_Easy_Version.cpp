// Problem: CF 2005 E1 - Subtangle Game (Easy Version)
// https://codeforces.com/contest/2005/problem/E1

/*
E1. Subtangle Game (Easy Version)
Algorithms/Techniques: Dynamic Programming with State Compression
Time Complexity: O(t * n * m * l) where t is number of test cases, n and m are matrix dimensions, l is length of array a.
Space Complexity: O(n * m + l)

This problem simulates a game between two players (Tsovak and Narek) on a matrix. Each player picks elements from
the array sequentially in order, and after each pick, the next player must pick from a submatrix starting one row
and column further. The goal is to determine whether Tsovak (first player) wins optimally.

We use dynamic programming with reverse iteration over rows of the matrix:
- First, we map element positions in the array to their indices in reverse order (p[elem] = index)
- Then, we iterate backwards through rows of the matrix
- At each position in a row, we check if it holds an element that can be played next in sequence
- We maintain a DP array f[k] which tracks the maximum column index at which a player can pick the k-th element,
  ensuring optimal moves for both players
- If Tsovak (first to play) can make a move that guarantees victory, we output "T"

*/
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;
const int N = 304;
int t, n, m, a[N][N], b[N], f[8], p[8]; // f: dp array, p: position mapping of elements in reverse
void sol() {
  cin >> t >> n >> m; // read length of array, matrix dimensions
  for (int i = 1; i <= t; i++)
    cin >> b[i]; // read the array elements
  for (int i = t; i; i--) // map each element to its position in the reverse array
    p[b[i]] = i;
  for (int i = 1; i <= n; i++) // read matrix
    for (int j = 1; j <= m; j++)
      cin >> a[i][j];
  for (int i = n; i; i--) { // iterate from last row to first (reverse direction)
    for (int j = 1, k = p[a[i][1]]; j <= m; j++, k = p[a[i][j]]) // process each cell in the current row
      if (k && f[k + 1] <= j) // if this element exists and we can place it optimally
        f[k] = max(f[k], j); // update the maximum column position for reaching this element
    if (f[1]) { // if Tsovak can reach the first element with winning strategy
      cout << "T\n";
      return;
    }
  }
  cout << "N\n"; // otherwise Narek wins
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--)
    sol(), memset(f, 0, 64), memset(p, 0, 64); // reset DP arrays and counters for next test case
}


// https://github.com/VaHiX/codeForces/