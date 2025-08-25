/*
 * Problem URL : https://codeforces.com/problemset/problem/1509/A
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
    std::vector<long> evens;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) {
        printf("%ld ", x);
      } else {
        evens.push_back(x);
      }
    }
    for (long p = 0; p < evens.size(); p++) {
      printf("%ld ", evens[p]);
    }
    puts("");
  }
}
