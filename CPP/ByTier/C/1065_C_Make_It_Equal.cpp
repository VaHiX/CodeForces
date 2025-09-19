/*
 * Problem URL : https://codeforces.com/problemset/problem/1065/C
 * Submit Date : 2025-08-19
 */

#include <cstdio>

const int N = 200000;
int n, k;
int eq[N + 2];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int v;
    scanf("%d", &v);
    ++eq[v];
  }
  for (int i = N; i > 0; --i)
    eq[i - 1] += eq[i];
  int t = 0;
  int s = 0;
  for (int i = N; i >= 0 && eq[i] != n; --i) {
    if (s + eq[i] > k) {
      ++t;
      s = 0;
    }
    s += eq[i];
  }
  printf("%d\n", t + (bool)s);
  return 0;
}
