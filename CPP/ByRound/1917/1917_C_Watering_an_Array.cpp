// Problem: CF 1917 C - Watering an Array
// https://codeforces.com/contest/1917/problem/C

/*
Code Purpose:
This solution simulates a process over d days where we either increment the first b_i elements of an array or count how many elements equal their position, adding that count to the score and resetting the array. The sequence b is cyclically repeated from a given vector v.

The key idea is to optimize the selection of operations to maximize score. It uses a linked list to maintain valid indices (those that haven't exceeded their position). For the first few iterations (up to 2*n), we simulate all operations and calculate maximum potential score based on current count and remaining operations.

Algorithms/Techniques:
- Simulation with a linked list optimization to track valid positions efficiently
- Cyclic sequence handling by using modulo operation
- Greedy-like approach to estimate upper bound of score from a few operations

Time Complexity: O(min(d, 2*n) * n)
Space Complexity: O(n + k)
*/
#include <ctype.h>
#include <stdio.h>
#include <algorithm>

#pragma GCC optimize("O3")
using namespace std;
namespace Fread {
const int SIZE = 1 << 18;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 8;
char buf[SIZE], *S = buf, *T = buf + SIZE;
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
namespace Fastio {
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
} // namespace Fastio
#define cin Fastio ::cin
#define cout Fastio ::cout
#define fore(i, a, b) for (int i = a; i <= b; ++i)
const int N = 2e3 + 2, M = 1e5 + 1;
int T, n, k, d, lim, t, ans, c, a[N], lst[N], nxt[N], b[M];
int main() {
  cin >> T;
  while (T--) {
    cin >> n >> k >> d;
    nxt[0] = 1;
    lst[n + 1] = n;
    fore(i, 1, n) nxt[i] = i + 1, lst[i] = i - 1;
    auto era = [&](int x) {
      int l = lst[x], r = nxt[x];
      nxt[l] = r, lst[r] = l;
    };
    fore(i, 1, n) {
      cin >> a[i];
      if (a[i] > i)
        era(i);
    }
    fore(i, 1, k) cin >> b[i];
    lim = min(d - 1, 2 * n);
    ans = 0;
    fore(i, 0, lim) {
      c = 0;
      for (int j = nxt[0]; j <= n; j = nxt[j])
        c += a[j] == j;
      ans = max(ans, c + (d - 1 - i) / 2);
      t = b[i % k + 1];
      for (int j = nxt[0]; j <= t; j = nxt[j]) {
        a[j]++;
        if (a[j] > j)
          era(j);
      }
      if (nxt[0] > n)
        break;
    }
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/