/*
 * Problem URL : https://codeforces.com/contest/1405/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1405/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    for (long p = n - 1; p >= 0; p--) {
      printf("%ld ", a[p]);
    }
    puts("");
  }

  return 0;
}
