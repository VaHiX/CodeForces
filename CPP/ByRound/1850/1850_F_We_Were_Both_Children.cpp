/*
 * Problem URL : https://codeforces.com/problemset/problem/1850/F
 * Submit Date : 2025-08-18
 */

#include <cstdio>
#include <map>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x];
    }

    std::vector<long> v(n + 1, 0);
    long mx(0);
    for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
      long key = it->first;
      long val = it->second;
      for (long p = 1; p * key <= n; p++) {
        v[p * key] += val;
        mx = (mx > v[p * key] ? mx : v[p * key]);
      }
    }

    printf("%ld\n", mx);
  }
}
