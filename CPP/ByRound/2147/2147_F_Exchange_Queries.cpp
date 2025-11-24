// Problem: CF 2147 F - Exchange Queries
// https://codeforces.com/contest/2147/problem/F

/*
F. Exchange Queries
Algorithms/Techniques: Segment Tree with Lazy Propagation, Discrete Mathematics

Time Complexity: O((n + q) * log n)
Space Complexity: O(n)

The problem deals with two permutations representing traders' views on item values. 
We are to compute how many pairs (i,j) exist such that item i is at least as valuable as item j.
This means there's a path from i to j in the transitive closure of trading relations.
Using segment tree with lazy propagation allows efficient updates and queries.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>

#define ll long long
using namespace std;
const int N = 500010;
inline ll read() {
  ll x = 0, y = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-')
      y = -y;
    c = getchar();
  }
  while ('0' <= c && c <= '9') {
    x = (x << 1) + (x << 3) + (c ^ 48);
    c = getchar();
  }
  return x * y;
}
void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x >= 10)
    write(x / 10);
  putchar('0' + x % 10);
}
struct Tree {
  ll l, r;
  ll siz, L, R;
  ll Min, sum, add;
} t[N << 2];
ll n, q;
void pushup(Tree &x, Tree y, Tree z) {
  x.Min = min(y.Min, z.Min);
  x.siz = y.siz + z.siz;
  if (y.Min == x.Min && z.Min == x.Min) {
    x.sum = y.sum + z.sum + y.R * z.L; // Combine sums when minimums match
    x.L = y.L, x.R = z.R;
  } else if (y.Min == x.Min) {
    x.sum = y.sum + y.R * z.siz + z.siz * (z.siz - 1) / 2; // Adjust for prefix matching minimum
    x.L = y.L, x.R = y.R + z.siz;
  } else {
    x.sum = z.sum + z.L * y.siz + y.siz * (y.siz - 1) / 2; // Adjust for suffix matching minimum
    x.L = z.L + y.siz, x.R = z.R;
  }
}
void spread(ll p) {
  if (t[p].add) { // Apply pending updates to children
    t[p << 1].Min += t[p].add, t[p << 1 | 1].Min += t[p].add;
    t[p << 1].add += t[p].add;
    t[p << 1 | 1].add += t[p].add;
    t[p].add = 0;
  }
}
void build(ll p, ll l, ll r) {
  t[p].l = l;
  t[p].r = r;
  t[p].add = 0;
  if (l == r) {
    t[p].L = 1, t[p].R = 0, t[p].Min = l, t[p].siz = 1, t[p].sum = 0;
    if (l == n)
      t[p].Min = 0; // Special case for last element
    return;
  }
  ll mid = (l + r) >> 1;
  build(p << 1, l, mid);
  build(p << 1 | 1, mid + 1, r);
  pushup(t[p], t[p << 1], t[p << 1 | 1]);
}
void change(ll p, ll l, ll r, ll d) {
  if (l <= t[p].l && t[p].r <= r) {
    t[p].Min += d;
    t[p].add += d;
    return;
  }
  spread(p); // Propagate pending updates before proceeding
  ll mid = (t[p].l + t[p].r) >> 1;
  if (l <= mid)
    change(p << 1, l, r, d);
  if (r > mid)
    change(p << 1 | 1, l, r, d);
  pushup(t[p], t[p << 1], t[p << 1 | 1]);
}
ll ask(ll p, ll l) {
  if (t[p].l == t[p].r)
    return t[p].Min; // Query specific value
  spread(p);
  ll mid = (t[p].l + t[p].r) >> 1;
  if (l <= mid)
    return ask(p << 1, l);
  return ask(p << 1 | 1, l);
}
ll a[N], b[N];
void add(ll x) { change(1, max(a[x], b[x]), n - 1, -1); } // Apply update to interval
void del(ll x) { change(1, max(a[x], b[x]), n - 1, 1); } // Remove update from interval
void print() { write(t[1].sum + n * (n - 1) / 2 + n), putchar('\n'); } // Output final count
void solve() {
  n = read(), q = read();
  build(1, 1, n);
  for (int i = 1; i <= n; i++)
    a[i] = read();
  for (int i = 1; i <= n; i++)
    b[i] = read();
  for (int i = 1; i <= n; i++)
    add(i); // Initialize all elements
  while (q--) {
    ll op = read(), x = read(), y = read();
    del(x), del(y); // Remove old elements before swaps
    if (op == 1)
      swap(a[x], a[y]); // Update permutation p
    else
      swap(b[x], b[y]); // Update permutation s
    add(x), add(y); // Add updated elements
    print(); // Print current count
  }
}
int main() {
  ll T = read();
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/