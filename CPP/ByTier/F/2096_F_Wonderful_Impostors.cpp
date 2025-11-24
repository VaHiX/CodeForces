// Problem: CF 2096 F - Wonderful Impostors
// https://codeforces.com/contest/2096/problem/F

/*
F. Wonderful Impostors

Purpose:
Solve a problem where we have n viewers and m statements about their roles (crewmate or impostor). 
Each statement can be of two types:
- Type 0: No impostors in range [a, b]
- Type 1: At least one impostor in range [a, b]

We want to answer queries about whether a range of statements can all be true under some assignment.

This problem uses segment tree with lazy propagation and sliding window technique.
The key idea is to maintain valid ranges that allow consistent assignments of roles to viewers.
Two types of operations are used:
1. Add interval (update sum in segment tree)
2. Query minimum prefix to ensure no negative imbalance
3. Maintain maximum value in segments for range queries

Time Complexity: O(m log n + q log m) per test case due to segment tree operations and sliding window
Space Complexity: O(n) for the segment trees and auxiliary data structures

Algorithms/Techniques:
- Segment Tree with Range Updates and Queries
- Sliding Window Technique
- Two Heaps / Multiset Approach
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FIO                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int ofs = (1 << 18);
int n, m;
int qu[ofs][3]; // Stores queries: type, left, right
pii t[2 * ofs]; // Segment tree for balance tracking
int g[2 * ofs]; // Segment tree for max value tracking
inline pii merge(pii x, pii y) { return {x.F + y.F, min(x.S, x.F + y.S)}; }
void add(int x, int val) {
  x += ofs;
  t[x].F += val;
  t[x].S += val;
  while (x /= 2)
    t[x] = merge(t[2 * x], t[2 * x + 1]);
}
int get(int x, int l, int r, int o, int sum = 0, int lo = 0, int hi = ofs - 1) {
  if (l > r || r < lo || hi < l || t[x].S + sum > 0)
    return -1;
  if (lo == hi)
    return lo;
  int mid = (lo + hi) / 2, h;
  if (!o) {
    h = get(2 * x, l, r, o, sum, lo, mid);
    if (h == -1)
      return get(2 * x + 1, l, r, o, sum + t[2 * x].F, mid + 1, hi);
  } else {
    h = get(2 * x + 1, l, r, o, sum + t[2 * x].F, mid + 1, hi);
    if (h == -1)
      return get(2 * x, l, r, o, sum, lo, mid);
  }
  return h;
}
void upd(int x, int val) {
  x += ofs;
  g[x] = val;
  while (x /= 2)
    g[x] = max(g[2 * x], g[2 * x + 1]);
}
int qmax(int x, int l, int r, int lo = 0, int hi = ofs - 1) {
  if (r < lo || hi < l)
    return -1;
  if (l <= lo && hi <= r)
    return g[x];
  int mid = (lo + hi) / 2;
  return max(qmax(2 * x, l, r, lo, mid), qmax(2 * x + 1, l, r, mid + 1, hi));
}
multiset<int> s[ofs]; // For maintaining maximum value in segment tree range
bool dod(int o, int l, int r) {
  if (!o) {
    int le = get(1, 0, l - 1, 1) + 1, ri = get(1, r + 1, n, 0) - 1;
    if (qmax(1, le, ri) >= le)
      return 0;
    add(l, 1);
    add(r + 1, -1);
  } else {
    if (get(1, l, r, 0) == -1)
      return 0;
    s[r].insert(l);
    upd(r, *(--s[r].end()));
  }
  return 1;
}
void del(int o, int l, int r) {
  if (!o)
    add(l, -1), add(r + 1, 1);
  else {
    s[r].erase(s[r].find(l));
    if (s[r].empty())
      upd(r, -1);
    else
      upd(r, *(--s[r].end()));
  }
}
void task() {
  cin >> n >> m;
  vector<int> opt(m);
  int j = 0;
  for (int i = 0; i < m; i++) {
    cin >> qu[i][0] >> qu[i][1] >> qu[i][2];
    qu[i][1]--;
    qu[i][2]--;
    while (!dod(qu[i][0], qu[i][1], qu[i][2]))
      del(qu[j][0], qu[j][1], qu[j][2]), j++;
    opt[i] = j;
  }
  while (j < m)
    del(qu[j][0], qu[j][1], qu[j][2]), j++;
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    cout << (opt[r] <= l ? "YES\n" : "NO\n");
  }
}
int main() {
  FIO;
  memset(g, -1, sizeof g);
  int tt;
  cin >> tt;
  while (tt--)
    task();
  return 0;
}


// https://github.com/VaHiX/codeForces/