/*
 * Problem URL : https://codeforces.com/contest/1434/problem/A
 * Submit Date : 2025-09-01
 */

#include <algorithm>
#include <cstdio>
#include <functional>
#include <utility>

const int S = 6;
const int N = 100000;
int n, a[S];
std::pair<int, int> b[N * S];

int main() {
  for (int i = 0; i < S; ++i)
    scanf("%d", a + i);
  std::sort(a, a + S, std::greater<int>());
  scanf("%d", &n);
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    int v;
    scanf("%d", &v);
    for (int j = 0; j < S; ++j)
      b[i * S + j] =
          std::make_pair(v - a[j], j + 1 < S ? a[j] - a[j + 1] : ~(1 << 31));
    mx = std::max(mx, v - a[0]);
  }
  std::sort(b, b + n * S);
  int ans = ~(1 << 31);
  for (int i = 0;; ++i) {
    ans = std::min(ans, mx - b[i].first);
    if (b[i].second == ~(1 << 31))
      break;
    mx = std::max(mx, b[i].first + b[i].second);
  }
  printf("%d\n", ans);
  return 0;
}
