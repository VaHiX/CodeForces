/*
 * Problem URL : https://codeforces.com/contest/840/problem/A
 * Submit Date : 2025-08-31
 */



#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }

  std::vector<std::pair<long, long>> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p].first);
    b[p].second = p;
  }

  sort(a.rbegin(), a.rend());
  sort(b.begin(), b.end());

  std::vector<long> f(n);
  for (long p = 0; p < n; p++) {
    f[b[p].second] = a[p];
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", f[p]);
  }
  puts("");

  return 0;
}
