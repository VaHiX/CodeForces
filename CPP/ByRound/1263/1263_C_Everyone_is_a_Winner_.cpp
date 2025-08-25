/*
 * Problem URL : https://codeforces.com/problemset/problem/1263/C
 * Submit Date : 2025-08-19
 */

#include <cstdio>
#include <set>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s;
    s.insert(0);
    for (long p = 1; p * p <= n; p++) {
      s.insert(p);
      s.insert(n / p);
    }
    printf("%ld\n", s.size());
    for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
      printf("%ld ", *it);
    }
    puts("");
  }

  return 0;
}
