/*
 * Problem URL : https://codeforces.com/contest/711/problem/B
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 505
int n;
ll r[N];
ll c[N];
int main() {
  scanf("%d", &n);
  int x, y;
  ll d1 = 0, d2 = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      int p;
      scanf("%d", &p);
      if (p == 0) {
        x = i;
        y = j;
      }
      r[i] += p;
      c[j] += p;
      if (i == j)
        d1 += p;
      if (i == n - j - 1)
        d2 += p;
    }
  if (n == 1) {
    printf("1\n");
    return 0;
  }
  ll m = r[(x + 1) % n] - r[x];
  r[x] += m;
  c[y] += m;
  if (x == y)
    d1 += m;
  if (x == n - y - 1)
    d2 += m;
  int ok = int(m > 0 && d1 == d2);
  for (int i = 0; i < n; i++)
    ok &= int(r[i] == d1 && c[i] == d1);
  if (ok)
    cout << m << endl;
  else
    cout << -1 << endl;
  return 0;
}