/*
 * Problem URL : https://codeforces.com/contest/802/problem/N
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 500000;

template <typename Tp>
using min_pq = priority_queue<Tp, vector<Tp>, greater<Tp>>;

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  static int a[N], b[N];
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  for (int i = 0; i < n; i++)
    scanf("%d", &b[i]);
  long long low = 0, hi = 1e18, ans = -1;
  while (low < hi) {
    long long t = (low + hi) / 2;
    min_pq<pair<long long, int>> pq;
    long long sum = 0;
    int cnt = 0;
#if 0
    printf("testing %lld\n", t);
#endif
    for (int i = 0; i < n; i++) {
      pq.push({a[i] - t, 0});
      auto [x, v] = pq.top();
      if (x + b[i] < 0) {
        pq.pop();
        sum += x + b[i];
        // printf("got %lld + %d\n", x, b[i]);
        cnt += v ^ 1;
        pq.push({-b[i], 1});
      }
    }
#if 0
    printf("got %d\n", cnt);
#endif
    if (cnt == k) {
      ans = sum + t * k;
      break;
    } else if (cnt < k)
      low = t + 1;
    else
      hi = t - 1;
  }
  assert(ans != -1);
  printf("%lld\n", ans);
  return 0;
}