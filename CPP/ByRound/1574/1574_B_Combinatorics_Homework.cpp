/*
 * Problem URL : https://codeforces.com/contest/1574/problem/B
 * Submit Date : 2025-08-29
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<long> v(3);
    long m;
    scanf("%ld %ld %ld %ld", &v[0], &v[1], &v[2], &m);
    sort(v.rbegin(), v.rend());
    long mn = (v[0] - v[1] - v[2] - 1);
    mn = (mn > 0) ? mn : 0;
    long mx = v[0] + v[1] + v[2] - 3;
    puts(mn <= m && m <= mx ? "YES" : "NO");
  }
}
