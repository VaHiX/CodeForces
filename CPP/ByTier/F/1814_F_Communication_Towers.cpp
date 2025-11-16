// Problem: CF 1814 F - Communication Towers
// https://codeforces.com/contest/1814/problem/F

/*
 * Problem: Communication Towers
 * Algorithm: Segment Tree with Union-Find (Disjoint Set Union)
 * 
 * Approach:
 * 1. For each edge connecting two towers, compute the intersection of their frequency ranges.
 *    If intersection exists, insert this interval into a segment tree.
 * 2. For each frequency in the segment tree, perform a union operation on the towers 
 *    that accept this frequency.
 * 3. Use a global tag array to track which connected components include the root (tower 1).
 * 
 * Time Complexity: O((n + m) * log(max_frequency)) 
 * Space Complexity: O(n + m * log(max_frequency))
 * 
 * Techniques:
 * - Segment Tree with lazy propagation simulation via interval updates
 * - Union-Find (Disjoint Set Union) with path compression and union by size
 * - Coordinate compression using segment tree for range queries
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
const int N = 5e5 + 10, maxn = 200000, M = 2e5 + 10;
int n, m, top, l[N], r[N], tag[N], f[N], siz[N];
pair<pair<int, int>, int> st[M * 20]; // Union-find stack for rollback
vector<pair<int, int>> v[M << 2];     // Segment tree nodes store (tower1, tower2) pairs

// Update segment tree with interval [L, R] to connect towers x and y
void change(int p, int l, int r, int L, int R, pair<int, int> pi) {
  if (L <= l && r <= R) {
    v[p].push_back(pi);
    return;
  }
  int mid = (l + r) >> 1;
  if (L <= mid)
    change(p << 1, l, mid, L, R, pi);
  if (R > mid)
    change(p << 1 | 1, mid + 1, r, L, R, pi);
}

// Find root of element x with path compression
int get(int x) { return f[x] == x ? x : get(f[x]); }

// Merge two sets: union x and y
void add(int x, int y) {
  x = get(x), y = get(y);
  if (x == y)
    return;
  if (siz[x] > siz[y])
    swap(x, y);
  st[++top] = {{x, y}, siz[y]};
  f[x] = y;
  siz[y] += siz[x];
  tag[x] -= tag[y]; // To properly mark connected components
}

// Rollback union-find to previous state
void del(int tmp) {
  while (top > tmp) {
    int x = st[top].first.first, y = st[top].first.second;
    int sz = st[top].second;
    top--;
    f[x] = x, siz[y] = sz, tag[x] += tag[y];
  }
}

// Traverse segment tree and process intervals
void solve(int p, int l, int r) {
  int tmp = top;
  for (int i = 0; i < v[p].size(); i++)
    add(v[p][i].first, v[p][i].second);
  if (l == r) {
    tag[get(1)]++; // Mark root component
    del(tmp);
    return;
  }
  int mid = (l + r) >> 1;
  solve(p << 1, l, mid), solve(p << 1 | 1, mid + 1, r);
  del(tmp);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &l[i], &r[i]);
    f[i] = i, siz[i] = 1;
  }
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    int L = max(l[x], l[y]), R = min(r[x], r[y]);
    if (R >= L)
      change(1, 1, maxn, L, R, {x, y});
  }
  solve(1, 1, maxn);
  for (int i = 1; i <= n; i++) {
    if (tag[i])
      printf("%d ", i);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/