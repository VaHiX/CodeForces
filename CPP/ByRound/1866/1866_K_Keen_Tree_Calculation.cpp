// Problem: CF 1866 K - Keen Tree Calculation
// https://codeforces.com/contest/1866/problem/K

/*
K. Keen Tree Calculation

Algorithms/Techniques:
- Tree diameter calculation with edge weight modifications using centroid decomposition and convex hull trick.
- DFS traversal to compute subtree maximum distances.
- Convex Hull Trick (CHT) for efficient query processing.
- Multiset for maintaining values during traversal.

Time Complexity: O(N log N + Q log N)
Space Complexity: O(N)

Problem:
Given a tree with N vertices, each edge has a weight. For Q queries,
each query modifies one edge's weight and asks for the new diameter of the tree.
*/

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 1e5 + 5, INF = 0x3f3f3f3f, MOD = 998244353;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;

vector<pii> s[MAXN];           // Adjacency list for tree
pii p[MAXN];                   // Parent and edge weight to parent
ll l[MAXN];                    // Distance from root to node
pair<ll, int> ma[MAXN], sma[MAXN]; // Maximum and second max dist from each node
ll ans[MAXN];                  // Answer array for queries
vector<pii> Q[MAXN];           // Queries grouped by node
ll tempans = 0;                // Global maximum diameter during DFS

// First DFS: calculates max distances in subtrees
void dfs(int nd, int par, int w) {
  p[nd] = {par, w};
  l[nd] = l[par] + w;
  for (auto [i, j] : s[nd]) {
    if (i == par)
      continue;
    dfs(i, nd, j);
    // Update max and second max distances
    if (ma[i].first + j > ma[nd].first) {
      sma[nd] = ma[nd];
      ma[nd] = {ma[i].first + j, i};
    } else if (ma[i].first + j > sma[nd].first)
      sma[nd] = {ma[i].first + j, i};
  }
  tempans = max(tempans, ma[nd].first + sma[nd].first);
}

// Convex Hull Trick: Insert line into deque maintaining convexity
void insert(deque<pll> &d, ll k, ll b) {
  while (!d.empty() && d.back().second <= b)
    d.pop_back();
  while (d.size() > 1) {
    auto [k1, b1] = d.back();
    double x = 1.0 * (b1 - b) / (k - k1);
    auto [k2, b2] = d[d.size() - 2];
    double x2 = 1.0 * (b2 - b1) / (k1 - k2);
    if (x <= x2)
      d.pop_back();
    else
      break;
  }
  d.push_back({k, b});
}

deque<pll> d, d2;              // Deques for convex hulls
vector<pll> tmp, tmp2;         // Temporary vectors for sorting and insertion
multiset<ll> st;               // Multiset for storing values during traversal

// Second DFS: processes each subtree and answers queries using CHT
void dfs2(int nd) {
  d.clear();                  // Deque for current node's conv hull
  tmp.clear();                // Temporary vector
  d2.clear();                 // Deque for queries' convex hull
  tmp2.clear();               // Temporary vector for merging

  // Collect all edges from children to process
  for (auto [i, j] : s[nd]) {
    if (i == p[nd].first)
      continue;
    tmp.push_back({j, ma[i].first});
  }
  sort(tmp.begin(), tmp.end());  // Sort by weight (k)

  // Build convex hull for current node
  for (auto [k, b] : tmp) {
    while (!d.empty() && d.back().second <= b) {
      tmp2.push_back(d.back());
      d.pop_back();
    }
    while (d.size() > 1) {
      auto [k1, b1] = d.back();
      double x = 1.0 * (b1 - b) / (k - k1);
      auto [k2, b2] = d[d.size() - 2];
      double x2 = 1.0 * (b2 - b1) / (k1 - k2);
      if (x <= x2) {
        tmp2.push_back(d.back());
        d.pop_back();
      } else
        break;
    }
    d.push_back({k, b});
  }

  // Merge tmp2 into second deque d2
  sort(tmp2.begin(), tmp2.end());
  for (auto [k, b] : tmp2) {
    insert(d2, k, b);
  }

  // Process queries at current node
  sort(Q[nd].begin(), Q[nd].end());
  pll last = {0, 0};  // Previous line of the CHT
  for (auto [x, ind] : Q[nd]) {
    ans[ind] = tempans;
    while (d.size() > 1) {
      auto [k1, b1] = d[0];
      auto [k2, b2] = d[1];
      double x2 = 1.0 * (b2 - b1) / (k1 - k2);
      if (x >= x2) {
        last = d[0];
        d.pop_front();
      } else
        break;
    }

    while (d2.size() > 1) {
      auto [k1, b1] = d2[0];
      auto [k2, b2] = d2[1];
      double x2 = 1.0 * (b2 - b1) / (k1 - k2);
      if (x >= x2)
        d2.pop_front();
      else
        break;
    }

    ll k = 0, b = 0;
    if (!d.empty()) {
      k = d.front().first;
      b = d.front().second;
    }

    ll Ma = k * x + b, sMa = last.first * x + last.second;

    if (d.size() > 1) {
      auto [k2, b2] = d[1];
      sMa = max(sMa, k2 * x + b2);
    }
    if (!d2.empty()) {
      auto [k2, b2] = d2[0];
      sMa = max(sMa, k2 * x + b2);
    }

    ans[ind] = max(ans[ind], Ma + sMa);  // Answer for this query
    if (nd != 1 && !st.empty())
      ans[ind] = max(ans[ind], *st.rbegin() + l[p[nd].first] + Ma +
                                   1ll * x * p[nd].second);
  }

  // Recursive DFS on children (centroid decomposition)
  for (auto [i, j] : s[nd]) {
    if (i == p[nd].first)
      continue;
    if (i == ma[nd].second)
      st.insert(sma[nd].first - l[nd]);
    else
      st.insert(ma[nd].first - l[nd]);
    dfs2(i);
    if (i == ma[nd].second)
      st.erase(st.find(sma[nd].first - l[nd]));
    else
      st.erase(st.find(ma[nd].first - l[nd]));
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  // Read all edges
  for (int i = 1; i < n; ++i) {
    int a, b, w;
    cin >> a >> b >> w;
    s[a].push_back({b, w});
    s[b].push_back({a, w});
  }

  // Initialize and run first DFS
  dfs(1, 0, 0);

  int q;
  cin >> q;

  // Collect queries grouped by affected node
  for (int i = 0; i < q; ++i) {
    int x, y;
    cin >> x >> y;
    Q[x].push_back({y, i});
  }

  // Run second DFS to answer all queries
  dfs2(1);

  // Output answers
  for (int i = 0; i < q; ++i)
    cout << ans[i] << "\n";

  return 0;
}


// https://github.com/VaHiX/codeForces/