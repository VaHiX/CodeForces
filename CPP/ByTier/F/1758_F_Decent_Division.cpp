// Problem: CF 1758 F - Decent Division
// https://codeforces.com/contest/1758/problem/F

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#define F first
#define S second
using namespace std;
typedef pair<int, int> pr;
inline int rd() {
  int x = 0, y = 1;
  char c = getchar();
  for (; c < '0' || c > '9'; c = getchar())
    if (c == '-')
      y = -1;
  for (; c >= '0' && c <= '9'; c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return x * y;
}
const int N = 2000009, M = 400001;
int n, m, tg[N], mn[N];
void add(int x, int y) {
  tg[x] += y;
  mn[x] += y;
}
void pd(int x) {
  if (tg[x])
    add(x << 1, tg[x]), add(x << 1 | 1, tg[x]), tg[x] = 0;
}
void bd(int rt, int l, int r) {
  mn[rt] = -r;
  if (l == r)
    return;
  int md = l + r >> 1;
  bd(rt << 1, l, md);
  bd(rt << 1 | 1, md + 1, r);
}
void upd(int rt, int l, int r, int x, int y, int z) {
  if (x <= l && r <= y) {
    add(rt, z);
    return;
  }
  int md = l + r >> 1;
  pd(rt);
  if (x <= md)
    upd(rt << 1, l, md, x, y, z);
  if (y > md)
    upd(rt << 1 | 1, md + 1, r, x, y, z);
  mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
int qr(int rt, int l, int r, int x) {
  if (l == r)
    return mn[rt];
  int md = l + r >> 1;
  pd(rt);
  if (x <= md)
    return qr(rt << 1, l, md, x);
  return qr(rt << 1 | 1, md + 1, r, x);
}
int ask(int rt, int l, int r, int x, int y) {
  if (mn[rt] >= y)
    return -1;
  if (l == r)
    return l;
  int md = l + r >> 1;
  pd(rt);
  if (x <= md) {
    int o = ask(rt << 1, l, md, x, y);
    if (o != -1)
      return o;
  }
  return ask(rt << 1 | 1, md + 1, r, x, y);
}
int calc(int x) {
  int o = qr(1, 0, M, x - 1);
  return ask(1, 0, M, x, o) - 1;
}
set<int> s;          // Store positions of '1's in the binary string
set<pr> b;           // Store disjoint ranges [l,r] where substring is decent
vector<pr> u, v;     // u: ranges to be removed, v: ranges to be added
set<int>::iterator it;

// Algorithm: Segment tree with lazy propagation to efficiently track and update
// the count of 1s in each position. Maintain a set of disjoint decent ranges.
// Time Complexity: O(n log N) where N is the maximum possible index
// Space Complexity: O(N) for the segment tree and auxiliary structures
int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  bd(1, 0, M);        // Initialize segment tree
  for (int x; n--;) {
    cin >> x;
    u.clear();
    v.clear();
    if (s.count(x)) {
      // Flip from 1 to 0
      s.erase(x);
      upd(1, 0, M, x, M, -2);  // Update segment tree for decrement
      auto o = --b.upper_bound({x + 1, 0});  // Find range that contains x
      u.push_back(*o);   // Mark range for removal
      // Find all ranges that may need to be merged or adjusted
      for (int y = o->F; (it = s.lower_bound(y)) != s.end() && (*it) <= o->S;
           ++y)
        v.push_back({*it, y = calc(*it)});
    } else {
      // Flip from 0 to 1
      s.insert(x);
      upd(1, 0, M, x, M, 2);  // Update segment tree for increment
      auto o = b.upper_bound({x + 1, 0});
      int y = (o == b.begin() || (--o)->S + 1 < x) ? x : o->F, z;
      v.push_back({y, z = calc(y)});  // Find new range to be added
      // Find overlapping ranges that need to be removed
      for (; (o = b.lower_bound({y, 0})) != b.end() && o->F <= z; y = o->S + 1)
        u.push_back(*o);
    }
    // Output ranges to be removed
    cout << u.size() << endl;
    for (auto i : u)
      cout << i.F << " " << i.S << endl, b.erase(i);
    
    // Output ranges to be added
    cout << v.size() << endl;
    for (auto i : v)
      cout << i.F << " " << i.S << endl, b.insert(i);
    
    fflush(stdout);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/