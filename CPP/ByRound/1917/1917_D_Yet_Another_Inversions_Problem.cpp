// Problem: CF 1917 D - Yet Another Inversions Problem
// https://codeforces.com/contest/1917/problem/D

/*
算法/技术: 前缀和, 树状数组, 分类讨论
时间复杂度: O(nk log n + mk log k + t(n + k))
空间复杂度: O(n + k)

该程序解决的是计算数组a中逆序对数量的问题。
给定一个奇数排列p和一个[0, k-1]的排列q，构造数组a[i*k+j] = p[i] * 2^q[j]。
使用树状数组加速查询操作，并对不同的情况分类计算逆序对总数。
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
namespace Fread {
const int SZ = 1 << 18;
char buf[SZ], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SZ = 1 << 16;
char buf[SZ], *S = buf, *T = buf + SZ;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#define getchar Fread ::getchar
#define putchar Fwrite ::putchar
namespace Fast {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    char c = getchar();
    while (!isdigit(c))
      c = getchar();
    x = 0;
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = getchar();
    return *this;
  }
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    if (x == 0) {
      putchar('0');
      return *this;
    }
    static int sta[45];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      putchar(sta[top] + '0');
      --top;
    }
    return *this;
  }
  Writer &operator<<(char c) {
    putchar(c);
    return *this;
  }
} cout;
} // namespace Fast
#define cin Fast ::cin
#define cout Fast ::cout
#define ll long long
#define il inline
const int P = 998244353, N = 2e5 + 1;
int n, m, p[N], q[N], tr[2 * N];
il void upd(int x, int r = 2 * n) {
  x++;
  for (int i = x; i <= r; i += i & (-i))
    tr[i]++;
}
il int ask(int x) {
  int ret = 0;
  x++;
  for (int i = x; i; i -= i & (-i))
    ret += tr[i];
  return ret;
}
il int ask(int x, int y) { return ask(y) - ask(x - 1); }
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> p[i];
  for (int i = 1; i <= m; ++i)
    cin >> q[i];
  ll ans = 0;
  auto add = [&](ll &x, ll y) {
    x += y;
    if (x >= P)
      x -= P;
  };
  auto mul = [&](ll x, ll y) { return x * y % P; };
  for (int i = 1; i <= n; ++i) {
    for (int k = 0; k < m; ++k) {
      int y = p[i] * (1 << k);
      if (y >= 2 * n)
        break;
      add(ans, mul(ask(y + 1, 2 * n - 1), m - k));
    }
    upd(p[i]);
  }
  auto clean = [&]() { fill(tr, tr + 2 * n + 1, 0); };
  clean();
  auto sum = [&](ll r) { return (1 + r) * r / 2 % P; };
  for (int i = n; i; --i) {
    for (int k = 1; k < m; ++k) {
      int y = p[i] * (1 << k);
      if (y >= 2 * n) {
        add(ans, mul(sum(m - k), n - i));
        break;
      }
      add(ans, mul(ask(1, y - 1), m - k));
    }
    upd(p[i]);
  }
  clean();
  for (int i = 1; i <= m; ++i)
    add(ans, mul(ask(q[i] + 1, m - 1), n)), upd(q[i], m);
  cout << ans << '\n';
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
    if (t)
      fill(tr, tr + m + 1, 0);
  }
}


// https://github.com/VaHiX/CodeForces/