/*
 * Problem URL : https://codeforces.com/contest/1057/problem/A
 * Submit Date : 2025-08-30
 */



#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> v(n + 1, 0);
  for (long p = 2; p <= n; p++) {
    scanf("%ld", &v[p]);
  }

  std::vector<long> w;
  w.push_back(n);
  while (w.back() != 1) {
    w.push_back(v[w.back()]);
  }
  for (long p = w.size() - 1; p >= 0; p--) {
    printf("%ld ", w[p]);
  }
  puts("");
}
