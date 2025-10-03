/*
 * Problem URL : https://codeforces.com/contest/1579/problem/E1
 * Submit Date : 2025-09-07
 */

#include <cstdio>
#include <deque>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::deque<long> d;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (d.empty() || x < d.front()) {
        d.push_front(x);
      } else {
        d.push_back(x);
      }
    }

    for (long p = 0; p < n; p++) {
      printf("%ld ", d[p]);
    }
    puts("");
  }
}
