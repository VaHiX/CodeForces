// Problem: CF 2021 E1 - Digital Village (Easy Version)
// https://codeforces.com/contest/2021/problem/E1

/*
E1. Digital Village (Easy Version)
Purpose: 
This code solves a problem where we need to find the minimum total latency for connecting houses requiring internet by optimally placing servers in at most k houses of a connected graph. It uses Union-Find with path compression and merging logic along with dynamic programming to compute optimal results for k = 1 to n.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression
- Merge operation with DP on trees to track minimum latencies
- Sorting edges by weight for Kruskal's MST-like approach

Time Complexity: O(m * n^2 + n^3)
Space Complexity: O(n^2)

*/
#include <algorithm>
#include <iostream>
using namespace std;
#define ll long long
const ll N = 5050, inf = 1e18;
ll T, n, m, p, S, s, sz[N], fa[N], tmp[N], dp[N][N];
struct P {
  ll x, y, w;
  bool operator<(const P &B) { return w < B.w; } // Sort edges by weight
} e[N];
void init() {
  for (int i = 1; i <= n; i++)
    fa[i] = i, sz[i] = 0; // Initialize Union-Find structure
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      dp[i][j] = 0; // Reset DP table
}
ll getfa(ll x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); } // Find root with path compression
void hb(ll x, ll y, ll w) {
  x = getfa(x), y = getfa(y);
  if (x == y)
    return; // Already in same component
  if (sz[x] > sz[y])
    x ^= y ^= x ^= y; // Swap to ensure sz[x] <= sz[y]
  ll A = sz[x], B = sz[y];
  fa[x] = y, sz[y] += sz[x]; // Merge smaller tree into larger one

  // Temporary array to hold updated DP values
  for (int i = 1; i <= A + B; i++)
    tmp[i] = inf;

  // Combine DP from both trees using edge weight w
  for (int i = 1; i <= A; i++)
    for (int j = 1; j <= B; j++)
      tmp[i + j] = min(tmp[i + j], dp[x][i] + dp[y][j]); // Base case: both components use existing servers

  for (int i = 1; i <= A; i++)
    tmp[i] = min(tmp[i], dp[x][i] + w * B); // Add the new edge weight to all nodes in y when connecting x and y

  for (int i = 1; i <= B; i++)
    tmp[i] = min(tmp[i], dp[y][i] + w * A); // Symmetric case

  for (int i = 1; i <= A + B; i++)
    dp[y][i] = tmp[i]; // Update merged DP table
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m >> p;
    init();
    for (int i = 1; i <= p; i++)
      cin >> s, sz[s] = 1; // Mark nodes that need internet as individual components
    for (int i = 1; i <= m; i++)
      cin >> e[i].x >> e[i].y >> e[i].w;
    sort(e + 1, e + m + 1); // Sort edges by weight for MST processing
    for (int i = 1; i <= m; i++)
      hb(e[i].x, e[i].y, e[i].w); // Process each edge in increasing order of weight
    S = getfa(1); // Get root of the final component
    for (int i = 1; i <= n; i++)
      cout << dp[S][i] << " "; // Output the minimum total latencies for all k from 1 to n
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/