/*
 * Problem URL : https://codeforces.com/problemset/problem/1325/B
 * Submit Date : 2025-08-21
 */

#include <cstdio>
#include <set>

std::set<int> s;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, x;
    scanf("%d", &n);
    while (n--)
      scanf("%d", &x), s.insert(x);
    printf("%d\n", s.size());
    s.clear();
  }
}