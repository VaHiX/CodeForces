// Problem: CF 1240 C - Paint the Tree
// https://codeforces.com/contest/1240/problem/C

/*
C. Paint the Tree
Algorithm: Dynamic Programming on Trees
Time Complexity: O(n log n) per query due to sorting
Space Complexity: O(n) for storage of tree and DP states

This problem involves finding the maximum value of a k-coloring of a tree,
where the value is the sum of weights of saturated edges (edges whose endpoints
share at least one color). We use dynamic programming on trees with the following
approach:
- For each node, we compute two values in dp[u][0] and dp[u][1]:
  - dp[u][0]: maximum value considering up to k colors can be assigned to u's subtree.
  - dp[u][1]: similar but adjusted for handling exactly k colors.
- The key insight is that for an edge (u,v) with weight w, if we assign a color to u and v,
  then w contributes to the total value if both have at least one common color.

We perform DFS traversal:
1. Compute contributions from children
2. Sort the "gain" of adding colors to each child to prioritize large weights.
3. Use top k gains to maximize the total value.

*/
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define rint register int
#define deb(x) cerr << #x << " = " << (x) << '\n';
using namespace std;
typedef long long ll;
using pii = pair<int, int>;
const int maxn = 5e5 + 5;
int q, n, k;
vector<pii> g[maxn];
ll dp[maxn][2];
void dfs(int u, int f) {
  ll tot = 0;
  vector<ll> v;
  for (auto it : g[u]) {
    int to = it.first;
    int w = it.second;
    if (to == f)
      continue;
    dfs(to, u); // Recursively calculate for child
    tot += dp[to][0]; // Accumulate base contribution
    v.push_back(dp[to][1] + w - dp[to][0]); // Calculate gain of adding color to this subtree edge
  }
  sort(v.rbegin(), v.rend()); // Sort gains from largest to smallest
  for (int i = 0; i < min(int(v.size()), k); i++)
    if (v[i] > 0)
      tot += v[i]; // Add top k positive gains
  dp[u][0] = dp[u][1] = tot;
  if (int(v.size()) >= k)
    if (v[k - 1] > 0)
      dp[u][1] -= v[k - 1]; // Adjust to allow exactly k colors in root
}
int main() {
  scanf("%d", &q);
  while (q--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
      g[i].clear();
    for (int i = 1; i < n; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      g[u].push_back(pii(v, w));
      g[v].push_back(pii(u, w));
    }
    dfs(1, 0);
    printf("%lld\n", dp[1][0]);
  }
}


// https://github.com/VaHiX/codeForces/