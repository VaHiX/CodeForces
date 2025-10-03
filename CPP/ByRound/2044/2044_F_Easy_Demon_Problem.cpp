/*
 * Problem URL : https://codeforces.com/contest/2044/problem/F
 * Submit Date : 2025-08-25
 */

#include <iostream>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int a[2 * N], b[2 * N], visa[2 * N], visb[2 * N], ans[2 * N];
ll suma, sumb;
int n, m, q;
ll mabs(ll a) { return max(a, -a); }
int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    suma += a[i];
  }
  for (int i = 0; i < m; i++) {
    scanf("%d", &b[i]);
    sumb += b[i];
  }
  for (int i = 0; i < n; i++) {
    ll d = suma - a[i];
    if (mabs(d) < N)
      visa[d + N] = 1;
  }
  for (int i = 0; i < m; i++) {
    ll d = sumb - b[i];
    if (mabs(d) < N)
      visb[d + N] = 1;
  }
  for (int i = 1; i < N; i++)
    for (int j = 1; i * j < N; j++) {
      ans[N + i * j] |= visa[N + i] && visb[N + j];
      ans[N + i * j] |= visa[N - i] && visb[N - j];
      ans[N - i * j] |= visa[N + i] && visb[N - j];
      ans[N - i * j] |= visa[N - i] && visb[N + j];
    }
  while (q--) {
    int x;
    scanf("%d", &x);
    if (ans[x + N])
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}