/*
 * Problem URL : https://codeforces.com/problemset/problem/1999/E
 * Submit Date : 2025-08-11
 */

#include <cstdio>
#include <vector>

int main() {

  std::vector<long> v(2e5 + 7);
  for (long p = 1; p < v.size(); p++) {
    v[p] = 1 + v[p / 3];
  }
  for (long p = 1; p < v.size(); p++) {
    v[p] += v[p - 1];
  }

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long res = v[b] - 2 * v[a - 1] + v[a];
    printf("%ld\n", res);
  }
}
