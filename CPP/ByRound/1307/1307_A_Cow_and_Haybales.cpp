/*
 * Problem URL : https://codeforces.com/contest/1307/problem/A
 * Submit Date : 2025-08-27
 */



#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, d;
    scanf("%ld %ld", &n, &d);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long s(a[0]);
    for (long p = 1; p < n; p++) {
      long x = (d / p);
      x = (x < a[p]) ? x : a[p];
      d -= x * p;
      s += x;
    }

    printf("%ld\n", s);
  }

  return 0;
}
