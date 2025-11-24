// Problem: CF 2117 H - Incessant Rain
// https://codeforces.com/contest/2117/problem/H

/*
 * Problem: H. Incessant Rain
 * Algorithm: Persistent Segment Tree with Lazy Updates and Dynamic Programming on Trees
 * 
 * Time Complexity:
 *   - Preprocessing: O(n log n) per test case
 *   - Each query: O(log^2 n)
 *   - Total for all queries: O((n + q) * log^2 n)
 * Space Complexity: O(n * log n) per test case due to persistent segment trees.
 *
 * Techniques:
 *   - Persistent Segment Tree
 *   - Dynamic Programming on tree structures (for tracking max k-majority)
 *   - Priority Queue for max element tracking
 *   - Custom memory pool for node reuse (to manage memory efficiently under constraints)
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#pragma GCC optimize("Ofast")
using namespace std;
#define endl '\n'
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
typedef long long ll;
const int N = 3e5, M = N * 20;
int t, n, q, a[N + 1];
struct Node {
  int c, ls, rs, ms;
  int l, r;
};
int trees[N + 1]; // Persistent root pointers for each element value in array
Node nodes[M + 1]; // Pool of nodes for segment tree (persistent)
vector<int> av;    // Memory pool for node reuse

// Frees a node back to memory pool to reduce allocations
void freenode(int &ci) {
  av.push_back(ci);
  ci = 0;
}

// Updates value at position i to x, in the persistent segment tree rooted at ci
void update(int i, int x, int l, int r, int &ci) {
  if (!ci) {
    ci = av.back();
    av.pop_back();
  }
  auto &cur = nodes[ci];
  if (l == r) {
    cur.c = cur.ls = cur.rs = cur.ms = x;
    // If count becomes 0, free node to reclaim memory
    if (!x)
      freenode(ci);
    return;
  }
  int m = (l + r) / 2;
  if (i <= m)
    update(i, x, l, m, cur.l);
  else
    update(i, x, m + 1, r, cur.r);

  int lt = m - l + 1, rt = r - m;
  auto &ln = nodes[cur.l], &rn = nodes[cur.r];
  
  // Update segment tree fields based on subtrees' properties
  cur.c = ln.c + rn.c;
  cur.ls = max(ln.ls, 2 * ln.c - lt + rn.ls);
  cur.rs = max(rn.rs, 2 * rn.c - rt + ln.rs);
  cur.ms = max({ln.ms, rn.ms, ln.rs + rn.ls});

  // Free node if total count is zero
  if (!cur.c)
    freenode(ci);
}

// Frees entire subtree rooted at ci (recursively)
void destroy(int &ci) {
  if (!ci)
    return;
  auto &cur = nodes[ci];
  freenode(ci);
  destroy(cur.l);
  destroy(cur.r);
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // Initialize memory pool to store up to M nodes upfront
  av.reserve(M);
  for (int i = 1; i <= M; i++)
    av.push_back(i);

  cin >> t;
  while (t--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      update(i, 1, 1, n, trees[a[i]]); // Build segment tree for existing elements
    }

    priority_queue<int> ans;
    vector<int> m(n + 1); // Tracks how many times each max_k_majority value appeared

    // Initial maximum k-majorities from current configuration
    for (int i = 1; i <= n; i++)
      ans.push(nodes[trees[i]].ms);

    while (q--) {
      int i, x;
      cin >> i >> x;

      auto f = [&](int x) {
        int &ci = trees[a[i]];
        auto &node = nodes[ci];
        m[node.ms]++; // Count old max_k_majority
        update(i, x, 1, n, ci);
        ans.push(node.ms); // Push the old value before replacement
      };

      f(0), a[i] = x, f(1); // Simulate removing and adding back

      // Remove outdated top values from priority queue if they are no longer valid
      while (m[ans.top()]) {
        m[ans.top()]--;
        ans.pop();
      }

      cout << ans.top() / 2 << " "; // Output half of max_k_majority value, as specified in task description
    }

    cout << endl;

    // Clean up persistent trees after test case
    for (int i = 1; i <= n; i++)
      destroy(trees[i]);
  }
}


// https://github.com/VaHiX/codeForces/