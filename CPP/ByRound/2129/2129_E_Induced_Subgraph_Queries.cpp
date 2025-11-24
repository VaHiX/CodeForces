// Problem: CF 2129 E - Induced Subgraph Queries
// https://codeforces.com/contest/2129/problem/E

/*
E. Induced Subgraph Queries

Algorithms/Techniques: Mo's algorithm with bit manipulation, square root decomposition, and fast query processing.

Time Complexity:
  - For each test case: O((n + m + q) * sqrt(n + m) * log(max_value))
    where max_value is bounded by 1e5 (node labels), due to the use of bucketing technique with bit manipulation.
Space Complexity:
  - O(n + m + q) for storing graph structure, queries, and auxiliary arrays.

This code implements an optimized algorithm to answer queries on induced subgraphs. Each query defines a range of nodes [l, r], and we are to find the k-th smallest XOR value of neighbors across all nodes in that range.

The solution uses:
1. Mo's algorithm for efficient range query processing.
2. Bit manipulation for fast computation of XOR values (f(u)).
3. Bucketing to maintain counts and efficiently query k-th smallest value.
*/
#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
int t, n, m, k, bn, pre[150005], l, r, w[150005], cnt[262144], sum[512],
    ans[150005];
vector<int> e[150005];
struct query {
  int l, r, k, id;
} q[150005];

// Comparator for Mo's algorithm - sorts queries by block and direction
bool cmp(query a, query b) {
  return pre[a.l] / bn == pre[b.l] / bn
             ? pre[a.l] / bn & 1 ? a.r < b.r : a.r > b.r
             : pre[a.l] / bn < pre[b.l] / bn;
}

// Add node x to the current window [l, r]
void add(int x) {
  w[x] = 0; // Initialize XOR value for node x
  for (int i = 0; i < e[x].size(); i++) {
    int v = e[x][i];
    if (v >= l && v <= r) { // Only consider edges within current window
      cnt[w[v]]--, sum[w[v] >> 9]--; // Decrease counts for old XOR of neighbor
      w[v] ^= x;                     // XOR with node x
      cnt[w[v]]++, sum[w[v] >> 9]++; // Update counts for new XOR of neighbor
      w[x] ^= v;                     // XOR the current node as well
    }
  }
  cnt[w[x]]++, sum[w[x] >> 9]++; // Add updated value of x to bucketing
}

// Remove node x from current window [l, r]
void del(int x) {
  cnt[w[x]]--, sum[w[x] >> 9]--; // Decrease counter for XOR value of x
  w[x] = 0;                      // Reset XOR value

  for (int i = 0; i < e[x].size(); i++) {
    int v = e[x][i];
    if (v >= l && v <= r) {
      cnt[w[v]]--, sum[w[v] >> 9]--; // Decrease current XOR of neighbor
      w[v] ^= x;                     // Reverse operation on neighbor's XOR
      cnt[w[v]]++, sum[w[v] >> 9]++; // Re-update count for new XOR value
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cin >> t;
  while (t--) {
    cin >> n >> m, bn = sqrt(n + m); // Initialize block size for Mo's algorithm
    
    // Build adjacency list representation of the graph
    for (int i = 1, u, v; i <= m; i++)
      cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
    
    // Precompute prefix sums for grouping in Mo's algorithm
    for (int i = 1; i <= n; i++)
      pre[i] = pre[i - 1] + e[i].size() + 1;
    
    cin >> k; // Number of queries
    
    // Read queries and assign IDs
    for (int i = 1; i <= k; i++)
      cin >> q[i].l >> q[i].r >> q[i].k, q[i].id = i;
    
    sort(q + 1, q + k + 1, cmp); // Sort queries using Mo's algorithm ordering
    l = 1, r = 0;                // Initialize window

    for (int i = 1; i <= k; i++) {
      while (l > q[i].l)
        add(--l);     // Extend window left
      while (r < q[i].r)
        add(++r);     // Extend window right
      while (l < q[i].l)
        del(l++);     // Shrink window from left
      while (r > q[i].r)
        del(r--);     // Shrink window from right

      // Find k-th smallest XOR value using bucketing technique
      for (int j = 0;; q[i].k -= sum[j >> 9], j += 512) {
        if (q[i].k <= sum[j >> 9]) {     // If required value is in current bucket
          while (q[i].k > cnt[j])
            q[i].k -= cnt[j++];
          ans[q[i].id] = j;  // Store result
          break;
        }
      }
    }

    for (int i = 1; i <= k; i++)
      cout << ans[i] << '\n'; // Output answers
    
    // Clear data structures for next test case
    for (int i = 1; i <= n; i++)
      e[i].clear(), w[i] = 0;
    
    for (int i = 0; i < 2 << __lg(n); i++)
      cnt[i] = 0;
    memset(sum, 0, sizeof(sum));
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/