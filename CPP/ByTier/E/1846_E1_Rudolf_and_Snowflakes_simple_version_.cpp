/*
 * Problem URL : https://codeforces.com/problemset/problem/1846/E1
 * Submit Date : 2025-08-18
 */

#include <cstdio>
#include <set>

int main() {

  const long N = 1e6 + 7;
  std::set<long> s;

  for (long k = 2; k < 1017; k++) {
    long cur = 1 + k;
    long nxt = k * k;
    while (cur + nxt < N) {
      cur += nxt;
      s.insert(cur);
      nxt *= k;
    }
  }

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(s.count(n) ? "YES" : "NO");
  }
}
