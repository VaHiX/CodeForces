/*
 * Problem URL : https://codeforces.com/contest/2045/problem/B
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  long long n, d, s, m = 0, shit = -1;
  cin >> n >> d >> s;
  d /= s, n = min(n / s, 2 * d);
  if (n % 2) {
    for (long long i = 3; i * i <= n && m == 0; i++)
      if (!(n % i))
        m = i;
    if ((m != 0 && (m - 1) * (n / m) <= d) || d == n - 1)
      shit = 0;
  }
  cout << s * max(n + max(shit, -n % 2), 1LL);
  return 0;
}