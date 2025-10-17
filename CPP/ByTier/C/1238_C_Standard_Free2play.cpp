/*
 * Problem URL : https://codeforces.com/contest/1238/problem/C
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010101
#define inf 1e18
#define mod 998244353

#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)

#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)

#define pb push_back
#define pp pair<int, int>

using namespace std;

int main() {

  int i, j, k;
  int n, m, q, h;

  sf(q);
  while (q--) {
    sff(h, n);

    queue<int> q;
    int a[n + 1];
    for (i = 0; i < n; i++)
      sf(a[i]), q.push(a[i]);

    q.push(0);
    a[n] = 0;

    int ans = 0;
    q.pop();

    while (!q.empty() && h > 0) {
      k = q.front();

      if (h - k >= 2)
        h = k + 1;

      else {

        q.pop();

        if (h - q.front() > 2)
          ans++;
        else
          q.pop();

        h -= 2;
      }
    }

    pf(ans);
    nl;
  }

  return 0;
}
