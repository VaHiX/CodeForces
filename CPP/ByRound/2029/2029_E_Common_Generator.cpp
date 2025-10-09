/*
 * Problem URL : https://codeforces.com/contest/2029/problem/E
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
#define MAXN 400069
#define enl '\n'
using namespace std;
int sieve[MAXN];
void testcase() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++)
    cin >> a[i];
  sort(a, a + n);
  int p = 2;
  if (sieve[a[0]] == a[0])
    p = a[0];
  for (int i = 1; i < n; i++)
    if (a[i] - sieve[a[i]] < 2 * p && a[i] != 2 * p) {
      cout << -1 << enl;
      return;
    }
  cout << p << enl;
}
signed main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 2; i <= (int)4e5; i++)
    if (!sieve[i])
      for (int j = i; j <= (int)4e5; j += i)
        if (!sieve[j])
          sieve[j] = i;
  while (t--)
    testcase();
  return 0;
}