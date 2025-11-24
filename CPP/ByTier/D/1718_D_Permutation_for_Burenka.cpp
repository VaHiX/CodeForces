// Problem: CF 1718 D - Permutation for Burenka
// https://codeforces.com/contest/1718/problem/D

/*
Purpose: 
This code determines whether a given number d can be used to fill in zeros in an array a such that the resulting array is "similar" to a given permutation p.
The algorithm uses a segment tree-like structure to find the valid ranges for each zero in the array and then checks if the number d falls within the intersection of these ranges.

Algorithms/Techniques:
1. Monotonic stack to build a binary tree structure representing the permutation
2. DFS traversal to determine valid ranges for zeros
3. Set operations to check if a valid range exists for d

Time Complexity: O(n log n + q)
Space Complexity: O(n)

*/
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
const int o = 3e5 + 10, inf = 1e9;
int T, n, q, p[o], a[o], ls[o], rs[o], st[o], tp, rt, k, s[o], L, R;
bool flg;
set<int> S;
set<int>::iterator iter;
struct cons {
  int l, r;
} c[o];

// DFS to traverse the tree and find valid ranges for each 0 in array a
int dfs(int nw, int r) {
  int l = 1;
  if (a[nw] > r)
    flg = 1;
  if (a[nw])
    r = min(r, a[nw] - 1);
  if (ls[nw])
    l = max(l, dfs(ls[nw], r));
  if (rs[nw])
    l = max(l, dfs(rs[nw], r));
  if (a[nw] && a[nw] < l)
    flg = 1;
  if (a[nw])
    l = max(l, a[nw] + 1);
  else
    c[++k].l = l, c[k].r = r;
  return l;
}

// Compare function for sorting from left to right
inline bool Cmp(cons A, cons B) { return A.l > B.l; }

// Compare function for sorting from right to left
inline bool cmp(cons A, cons B) { return A.r < B.r; }

int main() {
  for (scanf("%d", &T); T--; tp = k = flg = 0, S.clear()) {
    scanf("%d%d", &n, &q);
    L = 0;
    R = inf;
    for (int i = 1; i <= n; ++i)
      scanf("%d", &p[i]);
    // Build the binary tree using monotonic stack
    for (int i = 1; i <= n; rs[st[++tp] = i++] = 0) {
      for (st[tp + 1] = 0; tp && p[st[tp]] < p[i]; --tp)
        ;
      ls[rs[st[tp]] = i] = st[tp + 1];
      if (!tp)
        rt = i;
    }
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    dfs(rt, inf);
    for (int i = 1; i < k; ++i)
      scanf("%d", &s[i]), S.insert(s[i]);
    sort(c + 1, c + k + 1, Cmp);
    for (int i = 1; i <= k; ++i)
      if ((iter = S.upper_bound(c[i].r)) == S.begin() || (*--iter) < c[i].l)
        flg |= !!L, L = c[i].l;
      else
        S.erase(iter);
    for (int i = 1; i < k; ++i)
      S.insert(s[i]);
    sort(c + 1, c + k + 1, cmp);
    for (int i = 1; i <= k; ++i)
      if ((iter = S.lower_bound(c[i].l)) == S.end() || (*iter) > c[i].r)
        flg |= (R < inf), R = c[i].r;
      else
        S.erase(iter);
    for (int d; q--; printf((L <= d && d <= R && !flg) ? "YES\n" : "NO\n"))
      scanf("%d", &d);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/