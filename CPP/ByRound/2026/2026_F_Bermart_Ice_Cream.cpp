// Problem: CF 2026 F - Bermart Ice Cream
// https://codeforces.com/contest/2026/problem/F

/*
F. Bermart Ice Cream

Problem Description:
This problem implements a dynamic data structure to manage multiple stores where each store maintains a collection of ice cream types.
Each ice cream has a price and tastiness value. The system supports operations to:
1. Open a new store (copying content from an existing one),
2. Add a new ice cream type to a store,
3. Remove the oldest ice cream type from a store,
4. Query the maximum total tastiness for a given budget.

Algorithms Used:
- Segment Tree with lazy propagation for range updates and queries.
- Dynamic Programming on subset selection (0/1 knapsack variant).
- DFS traversal using stack-based simulation to process operations in correct order.
- Deque for maintaining temporal order of entries per store.

Time Complexity: O(q * log q * W) where W = 2000, due to segment tree updates and DP on subset sum.
Space Complexity: O(q * W) for storing segment tree nodes, DP tables, and data structures.

*/

#include <string.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
#define N 30000
int i, j, k, n, m, t, it, q;
int w1[N + 50], w2[N + 50], res[N + 50], fk[N + 50];
int cl[N + 50], cur, idx[N + 50];
vector<pair<int, int>> v[N + 50];
deque<int> q1;
struct SB {
#define md ((l + r) / 2)
#define ls (id * 2)
#define rs (ls + 1)
  basic_string<int> v[N * 4 + 50];  // Segment tree holding indices of items
  int f[21][2005];                 // DP table for knapsack - precomputed for each level
  void add(int id, int l, int r, int x, int y, int z) {
    if (x > y)
      return;
    if (x <= l && r <= y) {
      v[id] += z; // Range update with item index
      return;
    }
    if (x <= md)
      add(ls, l, md, x, y, z);
    if (y > md)
      add(rs, md + 1, r, x, y, z);
  }

  void dfs(int id, int l, int r, int dep) {
    memcpy(f[dep], f[dep - 1], sizeof(f[dep])); // Copy parent DP values
    for (auto x : v[id]) {                       // Apply all items in current node's range
      for (int i = 2000; i >= w1[x]; i--)        // Knapsack update from right to left
        f[dep][i] = max(f[dep][i], f[dep][i - w1[x]] + w2[x]);
    }
    if (l == r) {
      res[idx[l]] = f[dep][fk[idx[l]]];  // Store result after processing query
      return;
    }
    dfs(ls, l, md, dep + 1);   // Traverse left child
    dfs(rs, md + 1, r, dep + 1); // Traverse right child
  }
} sb;

void dfs(int x) {
  basic_string<int> v1, v2;  // v1 for adding items, v2 for removals in reverse order
  for (auto [op, y] : v[x]) {
    if (op == 1)
      dfs(y);  // Recurse on new store
    else if (op == 2) {
      cl[y] = cur;
      q1.push_back(y);
      v1 += y; // Add item to current sequence
    } else if (op == 3) {
      y = q1.front();
      q1.pop_front();
      sb.add(1, 1, q, cl[y] + 1, cur, y); // Update segment tree with removal info
      v2 += y;
    } else if (op == 4)
      idx[++cur] = y; // Mark index for query result
  }
  reverse(v2.begin(), v2.end()); // Reverse since we're removing items from front in backtracking
  for (auto i : v2) {
    cl[i] = cur;
    q1.push_front(i); // Re-add removed item at front
  }
  for (auto i : v1) {
    sb.add(1, 1, q, cl[i] + 1, cur, i); // Add back new item to segment tree
    q1.pop_back();                      // Remove from deque after processing
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  it = 1;
  while (t--) {
    int op, x;
    cin >> op >> x;
    if (op == 1)
      v[x].push_back({1, ++it}); // Open new store
    else if (op == 2) {
      m++;
      cin >> w1[m] >> w2[m];     // Read price and tastiness for new item
      v[x].push_back({2, m});   // Add to store
    } else if (op == 3)
      v[x].push_back({3, 0});   // Remove oldest item
    else {
      cin >> fk[++q];          // Query max tastiness for budget p
      v[x].push_back({4, q});
    }
  }
  dfs(1);
  sb.dfs(1, 1, q, 1); // Start DFS from root with initial dep=1 to build DP arrays
  for (i = 1; i <= q; i++)
    cout << res[i] << '\n';
}


// https://github.com/VaHiX/codeForces/