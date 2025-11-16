// Problem: CF 2025 G - Variable Damage
// https://codeforces.com/contest/2025/problem/G

/*
G. Variable Damage
Algorithm: Square Root Decomposition with Offline Processing
Time Complexity: O((n * sqrt(n) + n * log(n)) * log(max_val)) where n is number of queries
Space Complexity: O(n * sqrt(n))

This solution uses a square root decomposition technique to efficiently handle online queries.
For each block, we maintain:
- the maximum value in the block (mx)
- a tag for lazy propagation updates (tag)
- prefix sums and difference arrays to compute cost efficiently

Each query adds either a hero or artifact. After each addition, we calculate how many rounds
the army can survive by optimally assigning artifacts to heroes, using dynamic programming
on blocks.
*/

#include <algorithm>
#include <iostream>
#include <numeric>

#pragma GCC optimize("Ofast")
using namespace std;
#define MAXN 300005
const int B = 550; // Block size for sqrt decomposition
#define ll long long
const int NB = (MAXN / B) + 5;
int n, X[MAXN];
struct Query {
  int op, pos;
} Q[MAXN];
int ord[MAXN], rev[MAXN]; // ord: original order of indices, rev: reversal of ord
int bel[MAXN], bl[NB], br[NB], nb; // bel: block number, bl/br: block boundaries, nb: total number of blocks
int mx[NB], tag[NB], val[MAXN]; // mx: max value in block, tag: lazy propagation, val: current values
ll len[NB], d[MAXN], f[NB][B + 5]; // len: length of block, d: differences, f: prefix sums for dp

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> Q[i].op >> Q[i].pos, X[i] = Q[i].pos; // Read operations and values
  iota(ord + 1, ord + 1 + n, 1); // Fill ord with [1..n]
  sort(ord + 1, ord + 1 + n, [&](int x, int y) { return Q[x].pos < Q[y].pos; }); // Sort indices by value
  sort(X + 1, X + 1 + n); // Sort original values for differences
  for (int i = 1; i <= n; i++)
    d[i] = X[i] - X[i - 1]; // Compute difference array

  for (int i = 1; i <= n; i++)
    rev[ord[i]] = i; // Map original index to sorted position

  for (int i = 1; i <= n; i += B) { // Initialize blocks
    ++nb;
    bl[nb] = i, br[nb] = min(i + B - 1, n);
    for (int j = bl[nb]; j <= br[nb]; j++)
      bel[j] = nb, len[nb] += d[j]; // Assign block numbers and compute lengths
    for (int j = 1; j <= B; j++)
      f[nb][j] = j * len[nb]; // Initialize dp-like prefix
  }

  ll sum = 0, res = 0; // sum: total damage sum, res: accumulated result
  auto calc = [&](int bid) -> ll { // Compute the current cost of block
    if (mx[bid] < 0)
      return 0;
    if (mx[bid] > B)
      return f[bid][B] + len[bid] * (mx[bid] - B);
    return f[bid][mx[bid]];
  };
  auto update = [&](int bid, int k) { // Apply lazy propagation
    mx[bid] += k;
    tag[bid] += k;
  };
  auto build = [&](int bid) { // Rebuild block after update
    int l = bl[bid], r = br[bid];
    mx[bid] = -1e9;
    for (int i = l; i <= r; i++) {
      val[i] += tag[bid]; // Apply pending updates to values
      mx[bid] = max(mx[bid], val[i]); // Track maximum value in block
    }
    tag[bid] = 0;
    fill(f[bid] + 0, f[bid] + B + 1, 0); // Reset f
    for (int i = l; i <= r; i++) {
      int diff = mx[bid] - val[i]; // Calculate difference from max
      f[bid][diff + 1] += d[i]; // Add to difference frequency array
    }
    for (int i = 1; i <= B; i++)
      f[bid][i] += f[bid][i - 1]; // Compute prefix sum of frequencies
    for (int i = 1; i <= B; i++)
      f[bid][i] += f[bid][i - 1];
  };

  for (int i = 1; i <= n; i++) {
    if (Q[i].op == 1) // Hero added
      sum += Q[i].pos;
    int bid = bel[rev[i]]; // Get block number of the current index in sorted array
    int k = Q[i].op == 1 ? 1 : -1; // Update direction: 1 for hero, -1 for artifact
    for (int i = 1; i < bid; i++) { // Process all blocks before current one
      res -= calc(i);
      update(i, k); // Apply update to block
      res += calc(i); // Recalculate and accumulate cost
    }
    res -= calc(bid); // Remove old block's contribution
    for (int j = bl[bid]; j <= rev[i]; j++)
      val[j] += k; // Update values in block up to position rev[i]
    build(bid);
    res += calc(bid); // Add new block's contribution
    cout << 2 * sum - res << '\n'; // Output final answer
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/