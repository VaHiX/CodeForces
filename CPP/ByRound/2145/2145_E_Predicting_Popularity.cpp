// Problem: CF 2145 E - Predicting Popularity
// https://codeforces.com/contest/2145/problem/E

/*
E. Predicting Popularity
Algorithms/Techniques: Segment Tree with Lazy Propagation, Binary Search, Sorting
Time Complexity: O(n log n + m log^2 n)
Space Complexity: O(n)

The problem models a dynamic process where users watch a movie based on how well it matches their preferences.
We use a segment tree to efficiently manage the number of users who are suitable for the current popularity level,
and perform updates and queries using lazy propagation.

Key Concepts:
- For each user i, we define v[i] = max(a[i] - ac, 0) + max(d[i] - dr, 0)
- This value represents how much "shortfall" a user has relative to the movie's action and drama.
- As popularity p increases, more users become suitable (v[i] <= p).
- A segment tree tracks counts of users for each potential shortfall value.
- Each update modifies a user's shortfall and adjusts tree accordingly.
- The query returns the minimum index where count becomes non-zero, indicating current total popularity.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
char buf1[2097152], *ip1 = buf1, *ip2 = buf1;
inline int getc() {
  return ip1 == ip2 && (ip2 = (ip1 = buf1) + fread(buf1, 1, 2097152, stdin),
                        ip1 == ip2)
             ? EOF
             : *ip1++;
}
template <typename T> void in(T &a) {
  T ans = 0;
  char c = getc();
  for (; c < '0' || c > '9'; c = getc())
    ;
  for (; c >= '0' && c <= '9'; c = getc())
    ans = ans * 10 + c - '0';
  a = ans;
}
template <typename T, typename... Args> void in(T &a, Args &...args) {
  in(a), in(args...);
}
const int lim = 2000001;
int ac, dr, n, m, a[500005], d[500005], v[500005], cnt[2000005];
struct node {
  int v, tag;
} tr[8000005];
void pushdown(int pos) {
  tr[pos << 1].tag += tr[pos].tag, tr[pos << 1 | 1].tag += tr[pos].tag;
  tr[pos << 1].v += tr[pos].tag, tr[pos << 1 | 1].v += tr[pos].tag;
  tr[pos].tag = 0;
}
void pushup(int pos) { tr[pos].v = min(tr[pos << 1].v, tr[pos << 1 | 1].v); }
void build(int pos, int nl, int nr, int cnt[]) {
  tr[pos].tag = 0;
  if (nl == nr)
    tr[pos].v = cnt[nl];
  else {
    int mid = (nl + nr) >> 1;
    build(pos << 1, nl, mid, cnt), build(pos << 1 | 1, mid + 1, nr, cnt),
        pushup(pos);
  }
}
void add(int pos, int nl, int nr, int gl, int gr, int k) {
  if (gl <= nl && nr <= gr) {
    tr[pos].tag += k, tr[pos].v += k;
    return;
  }
  pushdown(pos);
  int mid = (nl + nr) >> 1;
  if (gl <= mid)
    add(pos << 1, nl, mid, gl, gr, k);
  if (gr > mid)
    add(pos << 1 | 1, mid + 1, nr, gl, gr, k);
  pushup(pos);
}
int query(int pos, int nl, int nr) {
  if (nl == nr)
    return tr[pos].v + nl;
  pushdown(pos);
  int mid = (nl + nr) >> 1;
  if (tr[pos << 1].v < 0)
    return query(pos << 1, nl, mid);
  else
    return query(pos << 1 | 1, mid + 1, nr);
}
int main() {
  in(ac, dr, n);
  for (int i = 1; i <= n; i++)
    in(a[i]);
  for (int i = 1; i <= n; i++)
    in(d[i]), v[i] = max(a[i] - ac, 0) + max(d[i] - dr, 0), cnt[v[i] + 1]++;
  for (int i = 1; i <= lim; i++)
    cnt[i] += cnt[i - 1];
  for (int i = 1; i <= lim; i++)
    cnt[i] -= i;
  build(1, 1, lim, cnt), in(m);
  for (int i = 1, x, y, z; i <= m; i++) {
    in(x, y, z), add(1, 1, lim, v[x] + 1, lim, -1); // remove old count
    a[x] = y, d[x] = z, v[x] = max(a[x] - ac, 0) + max(d[x] - dr, 0);
    add(1, 1, lim, v[x] + 1, lim, 1), cout << query(1, 1, lim) << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/