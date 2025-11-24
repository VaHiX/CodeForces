// Problem: CF 2053 G - Naive String Splits
// https://codeforces.com/contest/2053/problem/G

/*
 * Problem: G. Naive String Splits
 *
 * Algorithm/Techniques:
 * - Z-algorithm for pattern matching
 * - String reversal and symmetry
 * - Period detection
 * - Dynamic programming style matching using Z-function
 *
 * Time Complexity: O(n + m) per test case, where n is the length of string s,
 *                  and m is the length of string t.
 * Space Complexity: O(n + m) for storing the strings and Z arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

void Zfunc(int *z, const std::string &S) {
  z[0] = 0;
  for (int i = 1, r = 0, n = (int)S.size(); i < n; ++i)
    if (r + z[r] - 1 < i) {
      z[i] = 0;
      while (i + z[i] < n && S[z[i]] == S[i + z[i]])
        ++z[i];
      r = i;
    } else {
      z[i] = std::min({z[i - r], n - i, r + z[r] - i});
      while (i + z[i] < n && S[z[i]] == S[i + z[i]])
        ++z[i];
      if (z[i] != z[i - r])
        r = i;
    }
}
#define MAXN 10000005
int z[MAXN], r[MAXN];
char ans[MAXN];
void solve() {
  int n, m, k;
  std::cin >> n >> m, k = n + 1;
  std::string s, t;
  std::cin >> s >> t;
  Zfunc(z, s + "$" + t);
  std::reverse(s.begin(), s.end());
  std::reverse(t.begin(), t.end());
  Zfunc(r, s + "$" + t);
  auto match_pre = [&](int i, int j) -> bool { return z[n + j] >= i; };
  auto match_suf = [&](int i, int j) -> bool {
    return r[n + m - j - i + 2] >= i;
  };
  for (int i = 1; i <= n; ++i)
    if (z[i - 1] == n - i + 1) {
      k = i - 1;
      break;
    }
  bool period = (n % k == 0), ok = (m % k == 0);
  if (k <= n)
    for (int i = 0; i < m; ++i)
      if (t[i] != s[i % k])
        ok = 0;
  for (int i = 1; i < n; ++i) {
    if (period && i % k == 0) {
      if (!ok) {
        putchar('0');
        continue;
      }
      if (i > n / 2) {
        putchar(ans[n - i]);
        continue;
      }
      int x = i / k, y = n / k, z = m / k, flag = 0;
      for (int B = 0; !flag && B * y <= 2 * z; ++B)
        if ((z - (B * y)) % x == 0)
          if ((z - (B * y)) / x + B >= 0) {
            flag = 1;
            break;
          }
      putchar(ans[i] = (flag ^ '0'));
      continue;
    }
    if (i <= n / 2) {
      int d = 0, pos = i + 1, flag = 1, now = 1, mth = 0;
      while (z[pos - 1] >= i)
        ++d, pos += i;
      while (now < m + 1) {
        if (match_pre(i, now))
          ++mth, now += i;
        else {
          if (mth < d || !match_suf(n - i, now - d * i)) {
            flag = 0;
            break;
          }
          now = now - d * i + n - i, mth = 0;
        }
      }
      putchar(flag ^ '0');
    } else {
      int d = 0, pos = i + 1, flag = 1, now = 1, mth = 0;
      while (r[pos - 1] >= n - i && pos > n - i)
        ++d, pos -= n - i;
      while (now < m + 1) {
        if (match_suf(n - i, now))
          ++mth, now += n - i;
        else {
          if (mth < d || !match_pre(i, now - d * (n - i))) {
            flag = 0;
            break;
          }
          now = now - d * (n - i) + i, mth = 0;
        }
      }
      putchar(flag ^ '0');
    }
  }
  puts("");
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/