/*
 * Problem URL : https://codeforces.com/problemset/problem/1975/C
 * Submit Date : 2025-08-12
 */

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <set>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    if (n == 2) {
      printf("%ld\n", v[0] < v[1] ? v[0] : v[1]);
      continue;
    }

    std::multiset<long> s;
    s.insert(v[0]);
    s.insert(v[1]);
    s.insert(v[2]);
    long res(*std::next(s.begin(), 1));
    for (long p = 3; p < n; p++) {
      s.erase(s.find(v[p - 3]));
      s.insert(v[p]);
      long cand = *(std::next(s.begin(), 1));
      res = (res > cand ? res : cand);
    }

    printf("%ld\n", res);
  }
}
