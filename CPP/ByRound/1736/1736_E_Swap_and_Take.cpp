// Problem: CF 1736 E - Swap and Take
// https://codeforces.com/contest/1736/problem/E

/*
Code Purpose:
This code solves the "Swap and Take" problem using dynamic programming with memoization.
The algorithm explores all possible sequences of operations (swap and zero out, or do nothing)
to maximize the score obtained over n turns.

Algorithms/Techniques:
- Dynamic Programming with Memoization
- Recursive state exploration with two states:
  - `nw`: current turn index
  - `x`: number of elements that can be swapped in future
  - `y`: flag indicating if we can perform a zero operation

Time Complexity: O(n^4)
Space Complexity: O(n^3)
*/

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1013;
int n, a[N], dp[N][N][2];
int sdfs(int nw, int x, int y) {
  if (nw > n)
    return 0;
  if (~dp[nw][x][y])
    return dp[nw][x][y];
  int &p = dp[nw][x][y];
  // Try all possible swap operations for current turn
  for (int i = nw; i <= n; i++)
    p = max(p, sdfs(i + 1, x + 1, 1) + (i + 1 - nw) * a[nw] * y);
  // Try all possible zero operations for current turn
  for (int i = 1; i <= x; i++)
    p = max(p, i * a[i + nw] +
                   max(sdfs(nw + i, x - i + 1, 0), sdfs(nw + i, x - i, 1)));
  return p;
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  memset(dp, -1, sizeof dp);
  cout << sdfs(1, 1, 1);
}


// https://github.com/VaHiX/CodeForces/