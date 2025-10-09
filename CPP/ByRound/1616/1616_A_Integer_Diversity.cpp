/*
 * Problem URL : https://codeforces.com/problemset/problem/1616/A
 * Submit Date : 2025-08-23
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
      if (s.count(x)) {
        s.insert(-x);
      } else {
        s.insert(x);
      }
    }

    printf("%ld\n", s.size());
  }
}
