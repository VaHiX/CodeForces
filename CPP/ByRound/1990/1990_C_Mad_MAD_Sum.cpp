// Problem: CF 1990 C - Mad MAD Sum
// https://codeforces.com/contest/1990/problem/C

/*
 * Problem: C. Mad MAD Sum
 * 
 * Algorithm:
 * - For each test case, we simulate a process on an array `a` of size `n`.
 * - In each step:
 *   1. Add the sum of all elements of `a` to the result `sum`.
 *   2. Compute array `b` where each `b[i]` is the MAD (Maximum Appearing Duplicate)
 *      of the prefix `a[1..i]`.
 *   3. Replace `a` with `b`.
 * - The process continues until all elements in `a` become 0.
 * 
 * Key Observations:
 * - We can optimize by precomputing the MAD for each prefix.
 * - The MAD value is computed efficiently by tracking seen numbers.
 * - The final sum involves summing up values from intermediate arrays multiplied by
 *   appropriate weights due to multiple iterations.
 * 
 * Time Complexity: O(n) per test case (linear in the size of array due to efficient MAD tracking).
 * Space Complexity: O(n) for storing arrays and auxiliary tracking variables.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <utility>

#define ll long long
#define enl putchar('\n')
#define all(x) (x).begin(), (x).end()
#define debug(x) printf(" " #x ":%d\n", x);
using namespace std;
const int MAXN = 1e6 + 5;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
typedef pair<int, int> pii;
char buf[1 << 21], *p1 = buf, *p2 = buf, obuf[1 << 21], *o = obuf, of[35];
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
inline ll qpow(ll a, ll n) {
  ll res = 1;
  while (n) {
    if (n & 1)
      res = res * a % mod;
    n >>= 1;
    a = a * a % mod;
  }
  return res;
}
template <class T = int> inline T read() {
  T s = 0, f = 1;
  char c = gc();
  for (; !isdigit(c); c = gc())
    if (c == '-')
      f = -1;
  for (; isdigit(c); c = gc())
    s = s * 10 + c - '0';
  return s * f;
}
inline void read(int *a, int n) {
  for (int i = 1; i <= n; ++i)
    a[i] = read();
}
inline int inal(char *s) {
  int n = 0;
  for (s[0] = gc(); !isalpha(s[0]); s[0] = gc())
    ;
  for (; isalpha(s[n]); s[++n] = gc())
    ;
  return s[n] = 0, n;
}
inline void outd(int *a, int n) {
  for (int i = 1; i <= n; ++i)
    printf("%d ", a[i]);
  enl;
}
int n, m, q;
int a[MAXN], b[MAXN];
bool vis[MAXN];
void solve() {
  ll sum = 0;
  n = read();
  read(a, n);
  int cur = 0;
  for (int i = 1; i <= n; ++i) {
    if (vis[a[i]])
      cur = max(cur, a[i]); // update current MAD if we've seen this value before
    vis[a[i]] = 1;
    sum += a[i]; // accumulate the sum of the current state of array
    b[i] = cur;  // store MAD for prefix [1..i]
  }
  cur = 0;
  memset(vis + 1, 0, sizeof(bool) * n); // reset the visibility tracking for second pass
  for (int i = 1; i <= n; ++i) {
    if (vis[b[i]])
      cur = max(cur, b[i]); // similarly compute MAD of prefix using b array
    vis[b[i]] = 1;
    sum += b[i]; // accumulate sum for second pass
    b[i] = cur;
  }
  for (int i = n; i >= 1; --i) {
    sum += 1ll * (n - i + 1) * b[i]; // multiply by number of iterations this element contributes
  }
  printf("%lld\n", sum);
  memset(vis + 1, 0, sizeof(bool) * n); // reset for next test case
}
signed main(signed argc, char const *argv[]) {
  clock_t c1 = clock();
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif
  int TxT = 1;
  TxT = read();
  while (TxT--)
    solve();
#ifdef LOCAL
end:
  cerr << "Time Used:" << clock() - c1 << "ms" << endl;
#endif
  return 0;
}


// https://github.com/VaHiX/CodeForces/