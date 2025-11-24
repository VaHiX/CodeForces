// Problem: CF 1970 G3 - Min-Fund Prison (Hard)
// https://codeforces.com/contest/1970/problem/G3

/*
Algorithm: 
- This code solves a problem of dividing a prison (represented as a graph) into two connected components (complexes) with exactly one corridor connecting them.
- Uses Bridge Finding (Tarjan's Algorithm) to identify edges that, when removed, split the graph into components.
- Utilizes Subset Sum DP with bitset optimization to find optimal partition sizes for minimal funding.
- Time Complexity: O(n * sqrt(n) + m) where n is number of nodes and m is number of edges. Space Complexity: O(n)

*/

#include <assert.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <set>
#include <vector>

#define int long long
using namespace std;
const int maxn = 50005;
int n, m, c, timer = 0, first[100005], low[100005], sz[100005], normal[100005];
set<int> special[100005];
vector<int> adj[100005];
vector<array<int, 2>> bridges, pairs;

// Reset global arrays and variables before each test case
void reset() {
  for (int i = 1; i <= n; i++) {
    first[i] = low[i] = sz[i] = normal[i] = 0;
    adj[i].clear();
    special[i].clear();
  }
  pairs.clear();
  timer = 0;
}

// DFS to find bridges and component sizes using Tarjan's algorithm
void dfs(int u, int p) {
  first[u] = low[u] = ++timer;
  sz[u] = 1;
  for (int i : adj[u]) {
    if (i == p)
      continue;
    if (!first[i]) {
      dfs(i, u);
      sz[u] += sz[i];
      if (first[u] < low[i]) {
        bridges.push_back({u, i});
      }
      low[u] = min(low[u], low[i]);
    } else {
      low[u] = min(low[u], first[i]);
    }
  }
}

// Template function to perform subset sum DP using bitset for optimization
template <int len = 1> int subset_sum(int n) {
  if (n / 2 + 1 >= len) {
    return subset_sum<std::min(len * 2, maxn)>(n);
  }
  bitset<len> dp, dp2;
  dp[0] = 1;
  for (auto i : pairs) {
    i[1]--;
    int cur = 1;
    while (cur < i[1]) {
      dp |= dp << (i[0] * cur);
      dp2 |= dp2 << (i[0] * cur);
      i[1] -= cur;
      cur *= 2;
    }
    if (i[1]) {
      dp |= dp << (i[0] * i[1]);
      dp2 |= dp2 << (i[0] * i[1]);
    }
    dp2 |= dp2 << i[0];
    for (int j : special[i[0]]) {
      dp2 |= dp << j;
    }
    dp |= dp << i[0];
  }
  int ans;
  for (int i = n / 2; i >= 0; i--) {
    if (dp[i] || dp2[i]) {
      assert(i != 0);
      ans = i * i + (n - i) * (n - i);
      break;
    }
  }
  return ans;
}

// Main solving function for each test case
void solve() {
  cin >> n >> m >> c;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int cc = 0, br = 0;
  for (int i = 1; i <= n; i++) {
    if (!first[i]) {
      cc++;
      dfs(i, i);
      br += bridges.size();
      normal[sz[i]]++;
      for (auto j : bridges) {
        special[sz[i]].insert(sz[j[1]]);
        special[sz[i]].insert(sz[i] - sz[j[1]]);
      }
      bridges.clear();
    }
  }
  // If graph is connected and has no bridges, impossible to split
  if (cc == 1 && br == 0) {
    cout << "-1\n";
    reset();
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (normal[i]) {
      pairs.push_back({i, normal[i]});
    }
  }
  // Calculate total funding and output result
  cout << subset_sum(n) + (cc - 1) * c << '\n';
  reset();
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/