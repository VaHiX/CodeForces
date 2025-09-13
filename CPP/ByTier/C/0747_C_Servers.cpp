/*
 * Problem URL : https://codeforces.com/problemset/problem/747/C
 * Submit Date : 2025-08-19
 */

#include <bits/stdc++.h>

typedef long long int ll;
#define pp pair<ll, ll>

#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)

using namespace std;

int main() {
  ll i, j;
  ll n, q, c = 0;
  ll unc, count, ct;

  cin >> n >> q;
  ll t[q], d[q], k[q];

  for (i = 0; i < q; i++)
    cin >> t[i] >> k[i] >> d[i];

  unc = n;
  ct = 0;
  map<ll, ll> timer;
  for (i = 1; i <= n; i++)
    timer[i] = 0;

  for (i = 0; i < q; i++) {
    ct = t[i];
    c = 0, count = 0;

    for (j = 1; j <= n; j++) {
      if (timer[j] <= ct && timer[j] != 0) {
        timer[j] = 0;
        unc++;
      }
    }

    if (k[i] > unc) {
      cout << "-1" << endl;
    }

    else {
      for (j = 1; j <= n; j++) {
        if (timer[j] == 0 && k[i] > 0) {
          timer[j] = ct + d[i];
          unc--;
          count += j;
          k[i]--;
        }
      }
      cout << count << endl;
    }
  }

  return 0;
}
