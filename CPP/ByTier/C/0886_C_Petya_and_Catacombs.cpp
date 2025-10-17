/*
 * Problem URL : https://codeforces.com/contest/886/problem/C
 * Submit Date : 2025-09-12
 */

#include <cstdio>
#include <set>

int main() {

  long n;
  scanf("%ld", &n);
  std::set<long> s;
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    s.insert(x);
  }
  printf("%ld\n", n + 1 - s.size());

  return 0;
}
