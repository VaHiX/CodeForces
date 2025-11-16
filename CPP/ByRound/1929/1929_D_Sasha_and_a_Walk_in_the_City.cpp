// Problem: CF 1929 D - Sasha and a Walk in the City
// https://codeforces.com/contest/1929/problem/D

/*
 * Problem: Sasha and a Walk in the City
 * Algorithm: Tree Dynamic Programming
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 *
 * The solution uses dynamic programming on trees to count the number of "good"
 * sets of intersections. A good set is one where, if only those intersections
 * are dangerous, no simple path contains more than two dangerous intersections.
 * The key insight is that a set is good if and only if it does not contain a
 * path of length 3 (i.e., three nodes connected in a line). This can be
 * reformulated as: for each node u, compute dp[u] := number of good sets in the
 * subtree rooted at u such that u is not in the set. Then, the answer is sum of
 * all dp[u] + 1 (for including the empty set). The recurrence is: dp[u] =
 * product over children v of (dp[v] + 1)
 */

#include <algorithm>
#include <ctype.h>
#include <functional>
#include <stdio.h>
#include <vector>

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
const int SZ = 1 << 11;
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
int main() {
  int t, n, M = 998244353;
  cin >> t;
  while (t--) {
    int tt = 0, ans = 0;
    cin >> n;
    vector<int> dp(n + 1), hd(n + 1), vr(2 * n), nx(2 * n);
    auto add = [&](int u, int v) {
      vr[++tt] = v;
      nx[tt] = hd[u];
      hd[u] = tt;
    };
    int a, b;
    for (int i = 1; i <= n - 1; i++) {
      cin >> a >> b;
      add(a, b);
      add(b, a);
    }
    function<void(int, int)> dfs = [&](int u, int pa) {
      dp[u] = 1;
      for (int i = hd[u]; i; i = nx[i]) {
        int v = vr[i];
        if (v == pa)
          continue;
        dfs(v, u);
        dp[u] = 1ll * dp[u] * (dp[v] + 1) % M;
      }
      ans = (ans + dp[u]) % M;
    };
    dfs(1, 0);
    cout << (ans + 1) % M << '\n';
  }
}

// https://github.com/VaHiX/CodeForces/