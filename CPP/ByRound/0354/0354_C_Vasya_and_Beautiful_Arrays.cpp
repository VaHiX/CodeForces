/*
 * Problem URL : https://codeforces.com/problemset/problem/354/C
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  long m = a[0];
  bool done(false);
  while (!done) {
    done = true;
    for (long p = 0; p < n; p++) {
      while (a[p] % m > k) {
        --m;
        done = false;
      }
    }
  }

  printf("%ld\n", m);

  return 0;
}
