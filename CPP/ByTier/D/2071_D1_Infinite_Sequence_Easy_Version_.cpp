/*
 * Problem URL : https://codeforces.com/problemset/problem/2071/D1
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 5;

bool a[N], pre[N];
int n;

bool get(ll x) {
  if (x <= n)
    return a[x];
  else if (x / 2 <= n)
    return pre[x / 2];
  bool res = pre[n];
  if (!((x / 2) & 1))
    res ^= get(x / 2);
  if (!(n & 1))
    res ^= get(n + 1);
  return res;
}

void _main() {
  ll l, r;
  scanf("%d%lld%lld", &n, &l, &r);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), pre[i] = pre[i - 1] ^ a[i];
  printf("%d\n", get(l));
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    _main();
  return 0;
}