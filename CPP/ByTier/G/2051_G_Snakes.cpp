// Problem: CF 2051 G - Snakes
// https://codeforces.com/contest/2051/problem/G

/* 
G. Snakes
Purpose: Minimize the maximum cell occupied by any snake during a sequence of expanding/shrinking operations on snakes placed on a linear grid.

Algorithms/Techniques:
- Bitmask Dynamic Programming (DP)
- State compression: Each state represents a subset of snakes that have been processed
- The DP tracks the minimum cost (score) to reach each state, considering the placement and evolution of snakes.
- Time Complexity: O(3^n * n), where n is the number of snakes. In practice, due to constraints (n <= 20), it's manageable.
- Space Complexity: O(2^n * n)

Input:
- Two integers n (snakes) and q (events)
- q lines with "s +" or "s -" indicating snake s enlarges or shrinks

Output:
- Minimum possible score (maximum cell occupied by any snake)

*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
const int kMaxN = 21;
int n, q, a[kMaxN][kMaxN], mi[kMaxN][kMaxN], c[kMaxN],
    dp[1 << (kMaxN - 1)][kMaxN], z[1 << (kMaxN - 1)], ans = 2e9;
char y;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 1, x; i <= q; i++) {
    cin >> x >> y;
    if (y == '+') {
      c[x]++;
      for (int j = 1; j <= n; j++) {
        a[x][j]--, mi[x][j] = min(mi[x][j], a[x][j]);
      }
    } else {
      for (int j = 1; j <= n; j++) {
        a[j][x]++;
      }
    }
  }
  fill(dp[0], dp[(1 << n) - 1] + n + 1, 2e9); // Initialize DP with large values
  for (int i = 1; i <= n; i++) {
    dp[1 << (i - 1)][i] = 1, z[1 << (i - 1)] = i; // Base case: one snake placed at position i
  }
  for (int i = 1; i < (1 << n); i++) {
    for (int j = i; j; j ^= (j & (-j))) { // Iterate over subset of snakes that have been placed
      for (int k = (1 << n) - 1 - i; k; k ^= (k & (-k))) { // Iterate over subset of remaining snakes to determine next one to place
        dp[i ^ (k & (-k))][z[k & (-k)]] =
            min(dp[i ^ (k & (-k))][z[k & (-k)]],
                dp[i][z[j & (-j)]] + 1 - mi[z[j & (-j)]][z[k & (-k)]]); // Update DP state
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = min(ans, dp[(1 << n) - 1][i] + c[i]); // Compute final answer from all possible ending positions
  }
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/codeForces/