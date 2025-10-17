/*
 * Problem URL : https://codeforces.com/problemset/problem/1566/D1
 * Submit Date : 2025-08-26
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> v;
    long cnt(0);
    while (m--) {
      long x;
      scanf("%ld", &x);
      for (long p = 0; p < v.size(); p++) {
        cnt += (v[p] < x);
      }
      v.push_back(x);
    }

    printf("%ld\n", cnt);
  }
}
