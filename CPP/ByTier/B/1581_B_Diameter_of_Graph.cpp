/*
 * Problem URL : https://codeforces.com/contest/1581/problem/B
 * Submit Date : 2025-08-26
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    bool ans;
    if (n == 1) {
      ans = (m == 0 && k > 1);
    } else if (m < n - 1 || m > n * (n - 1) / 2) {
      ans = false;
    } else if (m == (n * (n - 1) / 2)) {
      ans = (k > 2);
    } else {
      ans = (k > 3);
    }
    puts(ans ? "YES" : "NO");
  }
}
