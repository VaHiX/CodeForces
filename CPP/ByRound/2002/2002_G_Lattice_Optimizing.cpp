// Problem: CF 2002 G - Lattice Optimizing
// https://codeforces.com/contest/2002/problem/G

/*
 * Problem: G. Lattice Optimizing
 * Algorithm: Meet-in-the-Middle with Bitmasking
 * Time Complexity: O(3^(m/3) * m) where m = 2*(n-1), space complexity: O(3^(m/3))
 *
 * Description:
 * Given an n x n grid, each cell has two directed edges: one down (d[x][y]) and one right (r[x][y]).
 * You start at (1,1) and travel to (n,n). The set S contains values of edges passed.
 * Goal is to maximize MEX(S), which is the smallest non-negative integer not in S.
 *
 * Approach:
 * Since n <= 20, m = 2*(n-1) can be up to 38. But we use meet-in-the-middle:
 * - First half (top-left to middle) builds all possible sets of edge values
 * - Second half (middle to bottom-right) uses reverse traversal to check valid combinations
 * - We use a hash table for efficient lookup of intermediate results.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define il inline
#define ll long long
const int N = 21;
int T, n, m, k, ans;
int d[N][N], r[N][N];
ll h;
struct HashTable {
  static const int M = 1 << 26, P = 3e7 + 1;
  int tot;
  int head[P], nxt[M];
  ll val[M];
  vector<int> had;
  il void Clear() {
    for (auto v : had)
      head[v] = 0;
    tot = 0, had.clear();
    return;
  }
  il void Insert(ll x) {
    int p = x % P;
    for (int i = head[p]; i; i = nxt[i]) {
      if (val[i] == x)
        return;
    }
    if (!head[p])
      had.push_back(p);
    nxt[++tot] = head[p], head[p] = tot, val[tot] = x;
    return;
  }
  il bool Find(ll x) {
    int p = x % P;
    for (int i = head[p]; i; i = nxt[i]) {
      if (val[i] == x)
        return true;
    }
    return false;
  }
} mp;

// DFS1: builds all possible sets of edge values from (1,1) to middle point
il void Dfs1(int x, int y, int t, ll S) {
  if (t == k) {
    // For each subset of current set S, insert into hash table
    for (ll T = S; T; T = (T - 1) & S)
      mp.Insert(((ll)x << 40) | T);
    return;
  }
  // Moving right or down
  if (x < n)
    Dfs1(x + 1, y, t + 1, S | (1ll << d[x][y]));
  if (y < n)
    Dfs1(x, y + 1, t + 1, S | (1ll << r[x][y]));
  return;
}

// DFS2: traverse from (n,n) backwards
il void Dfs2(int x, int y, int t, ll S) {
  if (t == k) {
    // Check if complement set exists in hash table
    while (mp.Find(((ll)x << 40) | (~S & h)))
      ans++, h |= 1ll << ans;
    return;
  }
  // Moving up or left
  if (x > 1)
    Dfs2(x - 1, y, t - 1, S | (1ll << d[x - 1][y]));
  if (y > 1)
    Dfs2(x, y - 1, t - 1, S | (1ll << r[x][y - 1]));
  return;
}

il void Build() {
  cin >> n, m = (n - 1) << 1, k = m / 3;
  // Read input values for down edges
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= n; j++)
      cin >> d[i][j];
  }
  // Read input values for right edges
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < n; j++)
      cin >> r[i][j];
  }
  ans = 0, h = 1, mp.Clear();
  // Insert initial nodes into hash table
  for (int i = 1; i <= n; i++)
    mp.Insert((ll)i << 40);
  Dfs1(1, 1, 0, 0), Dfs2(n, n, m, 0);
  cout << ans << "\n";
  return;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    Build();
  return 0;
}


// https://github.com/VaHiX/codeForces/