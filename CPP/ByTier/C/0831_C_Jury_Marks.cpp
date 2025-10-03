/*
 * Problem URL : https://codeforces.com/contest/831/problem/C
 * Submit Date : 2025-09-12
 */

#include <cstdio>
#include <set>
#include <unordered_map>
#include <vector>

int main() {

  long k, n;
  scanf("%ld %ld", &k, &n);
  std::set<long> s;
  long suma(0);
  for (int p = 0; p < k; p++) {
    long a;
    scanf("%ld", &a);
    suma += a;
    s.insert(suma);
  }
  std::vector<long> b(n);
  for (int p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  std::unordered_map<long, long> m;
  long count(0);
  for (int p = 0; p < n; p++) {
    for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
      long g = *it;
      ++m[b[p] - g];
      count += (m[b[p] - g] == n);
    }
  }

  printf("%ld\n", count);

  return 0;
}
