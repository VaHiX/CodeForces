/*
 * Problem URL : https://codeforces.com/problemset/problem/1761/B
 * Submit Date : 2025-08-20
 */

#include <cstdio>
#include <set>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s.insert(x);
    }

    printf("%ld\n", (s.size() == 2) ? (1 + n / 2) : n);
  }
}
