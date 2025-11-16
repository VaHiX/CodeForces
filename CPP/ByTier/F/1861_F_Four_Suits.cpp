// Problem: CF 1861 F - Four Suits
// https://codeforces.com/contest/1861/problem/F

/*
Algorithm: 
This code solves a complex combinatorial optimization problem in a poker game. 
The goal is to determine the maximum points a player can achieve by optimally 
distributing remaining cards after initial deals, such that:
1. All players end up with equal number of cards.
2. Each player picks one suit to keep and discards others.
3. Winner gets x - y points where x is their card count and y is max among others.
4. We want to find max possible points for each player assuming optimal play.

Time Complexity: O(n * S * 2^4) where S = total cards per player
Space Complexity: O(S * 2^4) for storing prefix sums and z arrays

The approach involves:
1. Compute prefix max arrays for forward and backward pass
2. Precompute how many cards of each suit go to each player
3. Binary search over possible distributions
4. For each player, simulate best decision for each suit

Key components:
- slv() function computes maximum points for a given player with a given suit choice
- Uses binary search and prefix sums for efficient range queries
- Bitmasking technique for suit combination generation (2^4 combinations)

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
#define N 50005
#define M 4000005
#define ll long long
#define pct __builtin_popcount
int n, b[4], b1[16], mx1[N], mx2[N], ans[N], a[N][4], a1[N][16], z1[M][16];
ll s, z[M][16];

// Function to compute maximum points for player x choosing suit y
int slv(int x, int y) {
  int l = max(mx1[x - 1], mx2[x + 1]), r = s, d = min<int>(s - a1[x][15], b[y]);
  // Binary search on the number of cards to add
  while (l <= r) {
    int mid = (l + r) / 2, t1;
    ll t;
    bool fl = 0;
    // Try all 2^4 suit combinations for the decision-making
    for (int i = 0; i < 16; ++i) {
      t1 = mid * pct(i);
      t = b1[15] - b1[i] + z[mid][i] + 1ll * t1 * z1[mid][i];
      t -= (!(i >> y & 1)) * d + min<int>(t1 - a1[x][i], s - a1[x][15]);
      t += s - a1[x][15] - d;
      if (t < b1[15] - d) {
        fl = 1;
        break;
      }
    }
    if (fl)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return a[x][y] + d - l;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < 4; ++j) {
      scanf("%d", &a[i][j]);
      mx1[i] = max(mx1[i], a[i][j]);
      for (int k = 0; k < 16; ++k)
        if (k >> j & 1)
          a1[i][k] += a[i][j];
    }
  // Compute prefix max arrays for optimization
  copy(mx1 + 1, mx1 + n + 1, mx2 + 1);
  for (int i = 1; i <= n; ++i)
    mx1[i] = max(mx1[i], mx1[i - 1]);
  for (int i = n; i; --i)
    mx2[i] = max(mx2[i], mx2[i + 1]);
  for (int i = 0; i < 4; ++i) {
    scanf("%d", &b[i]);
    for (int j = 0; j < 16; ++j)
      if (j >> i & 1)
        b1[j] += b[i];
  }
  // Calculate total cards each player should have
  for (int i = 1; i <= n; ++i)
    s += a1[i][15];
  s += b1[15];
  s /= n;
  // Precompute difference arrays for prefix sum queries
  for (int i = 1, t; i <= n; ++i)
    for (int j = 1; j < 16; ++j) {
      t = (s - a1[i][15] + a1[i][j]) / pct(j) + 1;
      ++z1[0][j];
      --z1[t][j];
      z[0][j] -= a1[i][j];
      z[t][j] += a1[i][j];
      z[t][j] += s - a1[i][15];
    }
  // Convert difference arrays to prefix sums
  for (int i = 1; i <= s; ++i)
    for (int j = 1; j < 16; ++j)
      z[i][j] += z[i - 1][j], z1[i][j] += z1[i - 1][j];
  // Compute answer for each player
  for (int i = 1, t; i <= n; ++i) {
    t = 0;
    for (int j = 0; j < 4; ++j)
      t = max(t, slv(i, j));
    printf("%d ", t);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/