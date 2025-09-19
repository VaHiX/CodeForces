/*
 * Problem URL : https://codeforces.com/problemset/problem/2072/C
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> v(n);
    long cx(0);
    for (size_t p = 0; p < n; p++) {
      cx |= p;
      if ((cx | x) > x) {
        break;
      }
      v[p] = p;
    }

    if (cx != x) {
      v.back() = x;
    }
    for (size_t p = 0; p < n; p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}
