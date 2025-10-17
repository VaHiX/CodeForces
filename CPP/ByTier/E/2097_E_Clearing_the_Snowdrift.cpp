// Problem: CF 2097 E - Clearing the Snowdrift
// https://codeforces.com/contest/2097/problem/E

/*
E. Clearing the Snowdrift
Problem: Find minimum time for snowplow to clear all sections of runway with given constraints.
Algorithm: Persistent Segment Tree + Sliding Window + Coordinate Compression
Time Complexity: O(n * log^2(max(a)))
Space Complexity: O(n * log(max(a)))

The solution uses a persistent segment tree to track the "active" snow sections in a sliding window.
Coordinates are compressed to reduce memory usage.

Key Techniques:
- Coordinate compression on input values
- Persistent Segment Tree for efficient range queries and updates
- Sliding window approach to process elements with delay up to d steps
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using ld = long double;
using pii = pair<int, int>;
using pil = pair<int, long long>;
using pli = pair<long long, int>;
using pll = pair<long long, long long>;
template <typename T> using uset = unordered_set<T>;
template <typename T1, typename T2> using umap = unordered_map<T1, T2>;
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#ifdef _DEBUG
const int N = 1000;
const int NODES = 1000;
#else
const int N = 5e5 + 10;
const int NODES = 5e7;
#endif

struct node {
  int sum = 0;        // sum of active sections in this node's range
  int ls = 0, rs = 0; // left and right children indices
};
node tree[NODES];
int nv = 1;             // next available node index

// Extend tree and initialize a new node
inline int ext(int x = 0) {
  tree[nv].sum = x;
  tree[nv].ls = tree[nv].rs = 0;
  return nv++;
}

// Update a node's sum based on children
inline void upd(int v) {
  tree[v].sum = tree[tree[v].ls].sum + tree[tree[v].rs].sum;
}

// Split segment at index i, return pair of nodes (before i, after i)
pii split(int i, int v, int tl, int tr) {
  if (!v)
    return {0, 0};
  if (tr - tl == 1) {
    if (i <= tl)
      return {0, v};
    else
      return {v, 0};
  }
  int m = (tl + tr) / 2;
  if (i < m) {
    auto p = split(i, tree[v].ls, tl, m);
    int v1 = p.first, v2 = p.second;
    int r1 = ext();                  // Create new node
    tree[v].ls = v2;
    upd(v);
    tree[r1].ls = v1;
    upd(r1);
    return {r1, v};
  } else {
    auto p = split(i, tree[v].rs, m, tr);
    int v1 = p.first, v2 = p.second;
    int r2 = ext();                  // Create new node
    tree[v].rs = v1;
    upd(v);
    tree[r2].rs = v2;
    upd(r2);
    return {v, r2};
  }
}

// Merge two persistent segment trees
int merge(int v1, int v2) {
  if (!v1 || !v2)
    return v1 + v2;
  tree[v1].ls = merge(tree[v1].ls, tree[v2].ls);
  tree[v1].rs = merge(tree[v1].rs, tree[v2].rs);
  upd(v1);
  return v1;
}

// Print elements in set (for debug only)
void printSet(int v, int tl, int tr) {
  if (!v)
    return;
  if (tr - tl == 1) {
    cout << tl << ' ';
    return;
  }
  int m = (tl + tr) / 2;
  printSet(tree[v].ls, tl, m);
  printSet(tree[v].rs, m, tr);
}

// Solve function for single test case
inline void solve() {
  nv = 1;                    // Reset node counter
  int n, d;
  cin >> n >> d;
  vector<int> a(n), c;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    c.push_back(a[i]);
  }
  c.push_back(0);
  sort(all(c));
  // Remove duplicates
  c.resize(unique(all(c)) - c.begin());
  // Compress coordinates
  for (int &i : a)
    i = lower_bound(all(c), i) - c.begin();
  ll ans = 0;
  int st = 0;  // root index of segment tree

  // Build persistent segment tree for initial state
  auto build = [&](auto self, int tl, int tr) -> int {
    if (tr - tl == 1) {
      int v = ext(c[tl] - c[tl - 1]); // Store difference in compressed coordinates
      return v;
    }
    int v = ext();
    int m = (tl + tr) / 2;
    tree[v].ls = self(self, tl, m);
    tree[v].rs = self(self, m, tr);
    upd(v);
    return v;
  };
  st = build(build, 1, c.size());

  vector<int> push(n);  // Delayed operations
  for (int i = 0; i < n; i++) {
    // Combine current node with delayed nodes in the window
    st = merge(st, push[i]);
    auto p = split(a[i] + 1, st, 1, c.size());
    ans += tree[p.first].sum;
    if (i + d < n)
      push[i + d] = merge(push[i + d], p.first);  // Delayed addition
    st = p.second;   // Move to next state
  }
  cout << ans << '\n';
}

signed main() {
#ifdef _DEBUG
  freopen("01.dat", "r", stdin);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int tt = 1;
  cin >> tt;
  for (int test_id = 1; test_id <= tt; test_id++) {
#ifdef _DEBUG
    cout << "TESTCASE #" << test_id << ":\n";
#endif
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/