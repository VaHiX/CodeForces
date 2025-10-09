/*
 * Problem URL : https://codeforces.com/problemset/problem/1236/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010
#define inf 1e9

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
#define pp pair<ll, ll>

using namespace std;

int main() {

  int i, j, k;
  int n, m, t;
  int a, b, c;

  sf(t);
  while (t--) {
    sff(a, b);
    sf(c);

    int ans = 0, cnt;

    int x = min(a, b / 2);
    int rem = b - (2 * x);
    cnt = x + 2 * x;
    x = min(rem, c / 2);
    cnt += x + 2 * x;

    ans = cnt;
    cnt = 0;

    x = min(b, c / 2);
    rem = b - x;
    cnt = x + 2 * x;
    x = min(rem / 2, a);
    cnt += x + 2 * x;

    ans = max(ans, cnt);
    pf(ans);
    nl;
  }

  return 0;
}
