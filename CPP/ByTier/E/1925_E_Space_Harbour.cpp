// Problem: CF 1925 E - Space Harbour
// https://codeforces.com/contest/1925/problem/E

/*
 * Problem: E. Space Harbour
 * 
 * Purpose: 
 *   This code handles a dynamic scenario involving ships moving between harbours on a line,
 *   where each harbour has a value and cost is calculated based on product of values
 *   of adjacent harbours multiplied by distance. It supports adding new harbours and
 *   querying total cost for ships in a range.
 * 
 * Algorithms:
 *   - Union-Find (Disjoint Set Union) is used to efficiently manage the structure of harbours.
 *   - Binary Indexed Tree (Fenwick Tree) is used to maintain prefix sums for efficient range queries.
 * 
 * Time Complexity:
 *   - Preprocessing: O(n)
 *   - Each query: O(log n)
 *   - Overall: O(n + q * log n)
 * 
 * Space Complexity:
 *   - O(n) for storing harbour data, BIT, and auxiliary arrays.
 * 
 * Techniques:
 *   - Fenwick Tree for range sum queries.
 *   - Union-Find with path compression for maintaining structure of harbours.
 *   - Preprocessing initial harbour positions.
 *   - Reverse processing of queries to handle updates correctly.
 */

#include <stdio.h>
#include <iosfwd>

#define N 300005
using namespace std;
typedef long long ll;
int n, m, Q, id[N], pre[N], nxt[N], X[N];
ll bit[N], cur[N], val[N], ans[N];
struct Qr {
  int op, x, v, l, r;
} q[N];

// Find root of x with path compression
int find(int x) {
  if (id[x] == x) {
    return x;
  }
  return id[x] = find(id[x]); // Path compression
}

// Add value to BIT at position x
void add(int x, ll num) {
  while (x <= n) {
    bit[x] += num;
    x += (x & (-x)); // Move to next node
  }
}

// Query prefix sum in BIT up to position x
ll qry(int x) {
  ll res = 0;
  while (x) {
    res += bit[x];
    x -= (x & (-x)); // Move to parent node
  }
  return res;
}

// Query sum for range ending at x using BIT and precomputed values
ll qq(int x) {
  int pos = find(x);
  if (pos == n) {
    return qry(n);
  }
  ll len = nxt[pos] - x;
  ll res = qry(pos) - val[pos] * (len * (len - 1) / 2);
  return res;
}

int main() {
  scanf("%d %d %d", &n, &m, &Q);
  for (int i = 1; i <= m; i++) {
    scanf("%d", &X[i]);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%lld", &val[X[i]]);
  }
  for (int t = 1; t <= Q; t++) {
    scanf("%d", &q[t].op);
    if (q[t].op == 1) {
      scanf("%d %d", &q[t].x, &q[t].v);
      val[q[t].x] = q[t].v;
    } else {
      scanf("%d %d", &q[t].l, &q[t].r);
    }
  }
  
  // Initialize data structures for harbour positions
  int lst = 0;
  for (int i = 1; i <= n; i++) {
    if (val[i]) {
      pre[i] = lst;
      nxt[lst] = i;
      ll len = i - lst;
      cur[lst] = (len * (len - 1) / 2) * val[lst];
      if (lst)
        add(lst, cur[lst]);
      lst = i;
    }
    id[i] = lst;
  }
  
  // Process queries in reverse order to handle dynamic updates
  for (int t = Q; t >= 1; t--) {
    if (q[t].op == 1) {
      int pos = q[t].x;
      ll len = nxt[pos] - pre[pos];
      add(pos, -cur[pos]); // Remove old contribution
      add(pre[pos], (len * (len - 1) / 2) * val[pre[pos]] - cur[pre[pos]]); // Add new contribution
      cur[pre[pos]] = (len * (len - 1) / 2) * val[pre[pos]];
      id[pos] = pre[pos];
      nxt[pre[pos]] = nxt[pos];
      pre[nxt[pos]] = pre[pos];
    } else {
      ans[t] = qq(q[t].r) - qq(q[t].l - 1); // Compute range sum
    }
  }
  
  // Output answers for queries of type 2
  for (int i = 1; i <= Q; i++)
    if (q[i].op == 2) {
      printf("%lld\n", ans[i]);
    }
  return 0;
}


// https://github.com/VaHiX/CodeForces/