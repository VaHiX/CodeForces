// Problem: CF 1990 D - Grid Puzzle
// https://codeforces.com/contest/1990/problem/D

/*
Purpose: 
  Solve a grid coloring problem where we need to make all cells white using two types of operations:
  1. Dye a 2x2 subgrid white
  2. Dye an entire row white
  Strategy uses dynamic programming to find minimum operations needed.
  
Algorithms/Techniques:
  - Dynamic Programming
  - State optimization based on the number of black cells in a row (0, 1-2, 3+)
  
Time Complexity: O(n) per test case
Space Complexity: O(n) for DP array
*/

#include <ctype.h>
#include <stdio.h>
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
int f[MAXN][3], a[MAXN];
void solve() {
  n = read();
  read(a, n);
  for (int i = 1; i <= n; ++i)
    f[i][0] = f[i][1] = f[i][2] = inf;
  f[0][0] = 0;
  f[0][1] = f[0][2] = inf;
  for (int i = 1; i <= n; ++i) {
    if (!a[i]) { // if row has no black cells
      f[i][0] = f[i - 1][0];
      f[i][1] = f[i][2] = inf;
      continue;
    }
    if (a[i] > 4) { // if row has more than 4 black cells
      f[i][0] = min({f[i - 1][0], f[i - 1][1], f[i - 1][2]}) + 1;
      f[i][1] = f[0][2] = inf;
      continue;
    }
    if (a[i] <= 2) { // if row has 0, 1 or 2 black cells
      f[i][0] = min({f[i - 1][0] + 1, f[i - 1][1], f[i - 1][2] + 1});
      f[i][1] = min({f[i - 1][1] + 1, f[i - 1][0] + 1, f[i - 1][0] + 1});
      f[i][2] = inf;
    } else { // if row has 3 or 4 black cells
      f[i][0] = min({f[i - 1][0], f[i - 1][1], f[i - 1][2]}) + 1;
      f[i][1] = f[i - 1][2] + 1;
      f[i][2] = f[i - 1][1] + 1;
    }
  }
  printf("%d\n", min({f[n][0], f[n][1], f[n][2]}));
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