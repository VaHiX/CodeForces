/*
 * Problem URL : https://codeforces.com/problemset/problem/1800/C2
 * Submit Date : 2025-08-18
 */

#include <cstdio>
#include <queue>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::priority_queue<long> ds;
    long long res(0);
    for (long p = 0; p < n; p++) {
      long long x;
      scanf("%lld", &x);
      if (x) {
        ds.push(x);
      } else if (!ds.empty()) {
        res += ds.top();
        ds.pop();
      }
    }

    printf("%lld\n", res);
  }
}
