/*
 * Problem URL : https://codeforces.com/contest/992/problem/A
 * Submit Date : 2025-08-30
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
    if (x != 0) {
      s.insert(x);
    }
  }
  printf("%ld\n", s.size());

  return 0;
}
