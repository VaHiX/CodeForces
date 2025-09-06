/*
 * Problem URL : https://codeforces.com/contest/1087/problem/A
 * Submit Date : 2025-08-29
 */

/*
 * Problem URL : https://codeforces.com/contest/1087/problem/A
 * Submit Date : 2025-08-28
 */



#include <bits/stdc++.h>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n")
#define N 100100

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
#define pp pair<string, int>

using namespace std;

int main() {

  int i, j, k;
  int n, m;

  string s, t = "";
  cin >> s;

  n = s.length();
  if (n % 2 == 1)
    k = n / 2;
  else
    k = (n / 2) - 1;

  t.pb(s[k]);

  i = k + 1;
  j = k - 1;
  while (t.length() < n) {
    if (i < n)
      t.pb(s[i]), i++;

    if (j >= 0)
      t.pb(s[j]), j--;
  }

  cout << t;

  return 0;
}
