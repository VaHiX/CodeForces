// Problem: CF 500 D - New Year Santa Network
// https://codeforces.com/contest/500/problem/D

/*
Algorithm/Technique: 
- Tree DFS to compute subtree sizes for each edge
- For each edge, calculate how many triplets (c1, c2, c3) have this edge 
  contributing to the total distance in the triangle (c1, c2, c3)
- Use inclusion-exclusion principle: for any edge (u,v), 
  if we know subtree sizes u and v, then 
  number of paths from nodes in u's subtree to nodes in v's subtree = size_u * (n - size_u)
- Update the total expected cost when an edge weight changes

Time Complexity: O(n + q)
Space Complexity: O(n)
*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

typedef long long ll;

// DFS to compute subtree sizes for each edge
ll dfs(ll node, ll from, const std::vector<std::vector<ll>> &g,
       std::map<std::pair<ll, ll>, ll> &bt) {
  ll cnt(1);  // count nodes in subtree rooted at node
  for (ll p = 0; p < g[node].size(); p++) {
    ll u = g[node][p];
    if (u == from) {
      continue;  // avoid going back to parent
    }
    ll cv = dfs(u, node, g, bt);  // get subtree size of child u
    cnt += cv;
    // Store subtree size for edge (min(u,node), max(u,node))
    if (u < node) {
      bt[std::make_pair(u, node)] = cv;
    } else {
      bt[std::make_pair(node, u)] = cv;
    }
  }
  return cnt;
}

int main() {
  const ll S = 3;  // number of Santas
  ll n;
  scanf("%lld", &n);
  std::vector<std::vector<ll>> g(n + 1);  // adjacency list for tree
  std::map<std::pair<ll, ll>, ll> w;     // edge weights
  std::vector<std::pair<ll, ll>> edgeList(n);  // list of edges
  for (ll p = 1; p < n; p++) {
    ll x, y, z;
    scanf("%lld %lld %lld", &x, &y, &z);
    // Make sure smaller node comes first to normalize edge representation
    if (x > y) {
      ll tmp = x;
      x = y;
      y = tmp;
    }
    g[x].push_back(y);
    g[y].push_back(x);
    edgeList[p] = std::make_pair(x, y);
    w[std::make_pair(x, y)] = z;
  }
  std::map<std::pair<ll, ll>, ll> bt;  // bt stores subtree sizes
  dfs(1, 0, g, bt);  // start DFS from root 1

  // For each edge, calculate its contribution to triangle counts
  for (std::map<std::pair<ll, ll>, ll>::iterator it = bt.begin();
       it != bt.end(); it++) {
    std::pair<ll, ll> edge = it->first;
    ll pr = it->second;
    // Number of nodes in subtree = pr, others = n - pr
    // Number of triangles using this edge = pr * (n - pr)
    it->second = pr * (n - pr);
  }

  // Compute initial expected cost
  ll sum(0);
  for (std::map<std::pair<ll, ll>, ll>::iterator it = bt.begin();
       it != bt.end(); it++) {
    std::pair<ll, ll> edge = it->first;
    ll mult = it->second;
    ll weight = w[edge];
    sum += mult * weight;
  }

  ll q;
  scanf("%lld", &q);
  const ll den = n * (n - 1) / 2;  // Total number of possible triplets divided by 2 (because we count twice)
  while (q--) {
    ll num, len;
    scanf("%lld %lld", &num, &len);
    std::pair<ll, ll> edge = edgeList[num];
    // Update sum by removing old contribution and adding new
    sum -= w[edge] * bt[edge];
    w[edge] = len;
    sum += len * bt[edge];
    // Print result: S * sum / den
    printf("%.8lf\n", 1.0 * S * sum / den);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/