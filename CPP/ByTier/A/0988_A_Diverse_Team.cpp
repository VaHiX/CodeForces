/*
 * Problem URL : https://codeforces.com/contest/988/problem/A
 * Submit Date : 2025-08-30
 */

#include <cstdio>
#include <map>

int main() {

  long n, k;
  scanf("%ld %ld", &n, &k);
  std::map<long, long> m;
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    m[x] = p;
    if (m.size() >= k) {
      break;
    }
  }

  if (m.size() >= k) {
    puts("YES");
    for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
      printf("%ld ", it->second);
    }
    puts("");
  } else {
    puts("NO");
  }

  return 0;
}
