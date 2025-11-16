// Problem: CF 1906 F - Maximize The Value
// https://codeforces.com/contest/1906/problem/F

/*
Problem: Maximize The Value
Algorithms/Techniques: Difference Array + Segment Tree with Range Maximum Subarray
Time Complexity: O((N + M + Q) * log M)
Space Complexity: O(N + M + Q)

This solution uses a segment tree to efficiently handle range updates and queries.
For each element in the array, we maintain a segment tree that tracks the effect of
operations on that element. We use a difference array technique to efficiently
apply range updates, and then query the maximum subarray sum in the segment tree.

The segment tree stores for each node a structure with:
- lsum: maximum sum starting from the left end of the range
- rsum: maximum sum ending at the right end of the range
- msum: maximum sum of any subarray within the range
- sum: total sum of all elements in the range
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
#define task "sol"
#define lb lower_bound
#define ub upper_bound
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define zs(v) ((int)(v).size())
#define BIT(x, i) (((x) >> (i)) & 1)
#define CNTBIT __builtin_popcountll
#define ALL(v) (v).begin(), (v).end()
#define endl '\n'
typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
const int dxx[8] = {-1, -1, 0, 1, 1, 1, 0, -1},
          dyy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const ll mod = 998244353;
const ll base = 331;
const int N = 1e5 + 5;
struct no {
  long long lsum, rsum, msum, sum;
};
vector<pii> range[N * 4]; // Stores operations affecting position i
no tree[4 * N + 1];       // Segment tree for range queries
vector<tuple<int, int, int>> qry[N]; // Stores queries for element K
long long ans[N];         // Stores final answers for each query
int n, m;

// Update the segment tree at position pos with value val
void update(int node, int pos, int val, int a, int b) {
  if (a == b && a == pos) {
    tree[node] = ((no){val, val, val, val});
    return;
  } else if (pos <= (a + b) / 2) {
    update(node * 2, pos, val, a, (a + b) / 2);
  } else if (pos > (a + b) / 2) {
    update(node * 2 + 1, pos, val, (a + b) / 2 + 1, b);
  }
  no left = tree[node * 2], right = tree[node * 2 + 1];
  tree[node] = ((no){max(left.lsum, left.sum + right.lsum),
                     max(right.rsum, right.sum + left.rsum),
                     max(left.msum, max(right.msum, right.lsum + left.rsum)),
                     left.sum + right.sum});
}

// Query the maximum subarray sum in range [i, j]
no query(int node, int a, int b, int i, int j) {
  if (i == a && j == b) {
    return tree[node];
  }
  if (j <= (a + b) / 2) {
    return query(node * 2, a, (a + b) / 2, i, j);
  }
  if (i > (a + b) / 2) {
    return query(node * 2 + 1, (a + b) / 2 + 1, b, i, j);
  }
  no left = query(node * 2, a, (a + b) / 2, i, (a + b) / 2);
  no right = query(node * 2 + 1, (a + b) / 2 + 1, b, (a + b) / 2 + 1, j);
  return ((no){max(left.lsum, left.sum + right.lsum),
               max(right.rsum, right.sum + left.rsum),
               max(left.msum, max(right.msum, right.lsum + left.rsum)),
               left.sum + right.sum});
}

void gogo() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int l, r, x;
    cin >> l >> r >> x;
    range[l].push_back(mp(x, i));      // Start of operation
    range[r + 1].push_back(mp(x, -i)); // End of operation
  }
  int q;
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    int k, s, t;
    cin >> k >> s >> t;
    qry[k].push_back({i, s, t}); // Store queries for element k
  }
  for (int i = 1; i <= n; ++i) {
    for (auto [x, id] : range[i]) {
      if (id < 0) {
        update(1, -id, 0, 1, m); // Remove operation
      } else {
        update(1, id, x, 1, m);  // Add operation
      }
    }
    for (auto [id, s, t] : qry[i]) {
      ans[id] = query(1, 1, m, s, t).msum; // Query the maximum subarray sum
    }
  }
  for (int i = 1; i <= q; ++i) {
    cout << ans[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  if (fopen(task ".inp", "r")) {
    freopen(task ".inp", "r", stdin);
    freopen(task ".out", "w", stdout);
  }
  gogo();
}


// https://github.com/VaHiX/CodeForces/