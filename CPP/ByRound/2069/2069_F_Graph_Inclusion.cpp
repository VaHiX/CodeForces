// Problem: CF 2069 F - Graph Inclusion
// https://codeforces.com/contest/2069/problem/F

/*
F. Graph Inclusion
Algorithm: Dynamic connectivity with segment tree and merge-find union (DSU) structures.
Time Complexity: O((n + q) * α(n)) where α is the inverse Ackermann function.
Space Complexity: O(n + q)

This problem involves maintaining two graphs A and B, and for each query:
- If an edge is added or removed from graph A or B, we compute how many
  additional edges are needed in graph A so that every connected component
  of graph B is contained within a connected component of graph A.

Approach:
1. Use dynamic DSU (Disjoint Set Union) for both graphs to track components fast.
2. Maintain segment tree to process updates over time intervals efficiently.
3. For each query:
   - If adding an edge, process it by either merging components or splitting them back.
   - When the edge is removed in future, rollback changes made during that interval.

Key ideas:
- Two DSUs are used: one for graph A and one for graph B.
- Segment tree stores all changes over time.
- Reverse operations help to undo updates when they become inactive.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
const int N = 4e5 + 10;
int n, q, xz[N], yz[N], fa1[N], fa2[N], sz1[N], sz2[N], vis[N], hx[N], hy[N],
    ha[N], num;
char az[N];
map<pair<char, pair<int, int>>, int> v;
vector<pair<char, pair<int, int>>> g[N << 2];
int find1(int x) {
  if (fa1[x] == x)
    return x;
  return find1(fa1[x]);
}
int find2(int x) {
  if (fa2[x] == x)
    return x;
  return find2(fa2[x]);
}
void merge1(int x, int y) {
  if (sz1[x] > sz1[y])
    swap(x, y);
  fa1[x] = y, sz1[y] += sz1[x];
}
void merge2(int x, int y) {
  if (sz2[x] > sz2[y])
    swap(x, y);
  fa2[x] = y, sz2[y] += sz2[x];
}
struct node {
  int l, r;
} t[N << 2];
void build(int p, int l, int r) {
  t[p] = {l, r};
  if (l == r)
    return;
  int mid = l + r >> 1;
  build(p << 1, l, mid);
  build(p << 1 | 1, mid + 1, r);
}
void add(int p, int l, int r, char a, int x, int y) {
  if (l <= t[p].l && t[p].r <= r) {
    g[p].push_back({a, {x, y}});
    return;
  }
  int mid = t[p].l + t[p].r >> 1;
  if (l <= mid)
    add(p << 1, l, r, a, x, y);
  if (r > mid)
    add(p << 1 | 1, l, r, a, x, y);
}
int ans;
void split1(int x, int y) {
  if (sz1[x] > sz1[y])
    swap(x, y);
  sz1[y] -= sz1[x], fa1[x] = x;
}
void split2(int x, int y) {
  if (sz2[x] > sz2[y])
    swap(x, y);
  sz2[y] -= sz2[x], fa2[x] = x;
}
void query(int p) {
  int laans = ans, lanum = num;
  for (int i = 0; i < g[p].size(); i++) {
    char a = g[p][i].first;
    int x = g[p][i].second.first, y = g[p][i].second.second;
    if (a == 'B') {
      int xx = find2(x), yy = find2(y);
      if (xx != yy) {
        ans++;
        merge2(xx, yy);
        num++, ha[num] = 2, hx[num] = xx, hy[num] = yy;
      }
    } else {
      int x1 = find1(x), y1 = find1(y), x2 = find2(x), y2 = find2(y);
      if (x1 != y1 && x2 == y2)
        ans--;
      if (x1 != y1) {
        merge1(x1, y1);
        num++, ha[num] = 1, hx[num] = x1, hy[num] = y1;
      }
      if (x2 != y2) {
        merge2(x2, y2);
        num++, ha[num] = 2, hx[num] = x2, hy[num] = y2;
      }
    }
  }
  if (t[p].l != t[p].r)
    query(p << 1), query(p << 1 | 1);
  else
    cout << ans << "\n";
  ans = laans;
  while (num > lanum) {
    if (ha[num] == 1)
      split1(hx[num], hy[num]);
    else
      split2(hx[num], hy[num]);
    num--;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> q;
  build(1, 1, q);
  for (int i = 1; i <= n; i++)
    fa1[i] = fa2[i] = i, sz1[i] = sz2[i] = 1;
  for (int i = 1; i <= q; i++) {
    cin >> az[i] >> xz[i] >> yz[i];
    if (xz[i] > yz[i])
      swap(xz[i], yz[i]);
    int z = v[{az[i], {xz[i], yz[i]}}];
    if (z) {
      add(1, z, i - 1, az[i], xz[i], yz[i]);
      vis[z] = 0;
      v[{az[i], {xz[i], yz[i]}}] = 0;
    } else {
      v[{az[i], {xz[i], yz[i]}}] = i;
      vis[i] = 1;
    }
  }
  for (int i = 1; i <= q; i++)
    if (vis[i])
      add(1, i, q, az[i], xz[i], yz[i]);
  query(1);
  return 0;
}


// https://github.com/VaHiX/codeForces/