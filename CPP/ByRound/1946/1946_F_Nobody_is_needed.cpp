// Problem: CF 1946 F - Nobody is needed
// https://codeforces.com/contest/1946/problem/F

/*
Algorithm: 
- Use a coordinate compression and Fenwick tree (Binary Indexed Tree) approach.
- Process queries from right to left (i from n to 1).
- For each element a[i], compute how many valid sequences end at this element using dynamic programming.
- Maintain a Fenwick tree to quickly answer range queries for the count of valid sequences.
- Sort queries by left boundary to process them in a way that allows efficient updates to the BIT.

Time Complexity: O(n * log(n) + q * log(n)) where n is length of array, q is number of queries.
Space Complexity: O(n) for arrays and data structures.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define ls(u) tr[u].son[0]
#define rs(u) tr[u].son[1]
typedef long long ll;
char *p1, *p2, buf[100000];
#define nc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
inline int read() {
  int x = 0, f = 1;
  char ch = nc();
  while (ch < 48 || ch > 57) {
    if (ch == '-')
      f = -1;
    ch = nc();
  }
  if (ch == '-')
    f = -1;
  while (ch >= 48 && ch <= 57)
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = nc();
  return f * x;
}
inline void write(ll x) {
  if (x < 0)
    x = -x, putchar('-');
  if (x < 10)
    putchar(x ^ 48);
  else
    write(x / 10), write(x % 10);
}
int pt;
inline void read(char *opt) {
  char ch = nc();
  while ((ch < 65 || ch > 90) && (ch > 132 || ch < 97) && ch != '*')
    ch = nc();
  while (ch >= 65 && ch <= 90 || ch >= 97 && ch <= 132 || ch == '*')
    opt[pt++] = ch, ch = nc();
  opt[pt] = 0, pt = 0;
}
inline int max(const int &x, const int &y) {
  if (x > y)
    return x;
  return y;
}
inline int min(const int &x, const int &y) {
  if (x < y)
    return x;
  return y;
}
const int N = 1e6 + 10;
int a[N], p[N], n, m;
ll f[N], tr[N], ans[N];
inline void add(int x, ll c) {
  for (int i = x; i <= n; i += i & -i)
    tr[i] += c;
}
inline ll query(int x) {
  ll res = 0;
  for (int i = x; i; i -= i & -i)
    res += tr[i];
  return res;
}
struct Query {
  int l, r, id;
  inline bool operator<(const Query &t) const { return l > t.l; }
} q[N];
inline void solve() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++)
    a[i] = read(), p[a[i]] = i, tr[i] = 0;
  for (int i = 1; i <= m; i++)
    q[i].l = read(), q[i].r = read(), q[i].id = i, ans[i] = 0;
  sort(q + 1, q + m + 1);
  for (int i = n, j = 1; i; i--) {
    f[a[i]] = 1;
    for (int x = a[i]; x <= n; x += a[i]) {
      if (p[x] < p[a[i]])
        continue;
      for (int y = 2 * x; y <= n; y += x)
        if (p[y] > p[x])
          f[y] += f[x];
    }
    for (int x = a[i]; x <= n; x += a[i])
      add(p[x], f[x]), f[x] = 0;
    while (j <= m && q[j].l >= i)
      ans[q[j].id] = query(q[j].r) - query(q[j].l - 1), j++;
  }
  for (int i = 1; i <= m; i++)
    write(ans[i]), putchar(' ');
  putchar('\n');
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int testcase;
  testcase = read();
  while (testcase--)
    solve();
}


// https://github.com/VaHiX/CodeForces/