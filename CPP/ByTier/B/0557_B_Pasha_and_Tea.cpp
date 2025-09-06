/*
 * Problem URL : https://codeforces.com/contest/557/problem/B
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/557/problem/B
 * Submit Date : 2025-09-02
 */



#include <bits/stdc++.h>

typedef long long int ll;

#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");

#define inf 1000000000000

using namespace std;

int main() {

  ll i, j, k, l;
  ll n, w;

  cin >> n >> w;
  ll a[2 * n];

  for (i = 0; i < 2 * n; i++)
    cin >> a[i];

  sort(a, a + (n * 2));

  double p;
  if (a[0] * 2 <= a[n])
    p = (double)a[0];
  else
    p = (double)a[n] / 2;

  if (p * 3 * n <= w)
    printf("%lf", (double)p * 3 * n);
  else
    printf("%lf", (double)w);

  return 0;
}
