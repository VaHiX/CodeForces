/*
 * Problem URL : https://codeforces.com/problemset/problem/205/B
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll ans, h[100005];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &h[i]);
    ans += max(0ll, h[i - 1] - h[i]);
  }
  printf("%lld", ans);

  return 0;
}