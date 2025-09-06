/*
 * Problem URL : https://codeforces.com/contest/1330/problem/A
 * Submit Date : 2025-08-26
 */



#include <cstdio>
#include <vector>

int main() {

  const long N = 207;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<bool> b(N, false);
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      b[a] = true;
    }
    long res(0);
    for (long p = 1; p < N; p++) {
      if (b[p]) {
        continue;
      }
      if (x > 0) {
        --x;
      } else {
        res = p - 1;
        break;
      }
    }

    printf("%ld\n", res);
  }

  return 0;
}
