/*
 * Problem URL : https://codeforces.com/contest/412/problem/B
 * Submit Date : 2025-09-05
 */



#include <bits/stdc++.h>
typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<ll, ll>

using namespace std;

int main() {

  ll i, j, k;
  ll n, x;

  cin >> n >> k;
  ll a[n];

  for (i = 0; i < n; i++)
    cin >> a[i];

  sort(a, a + n, greater<ll>());

  cout << a[k - 1];

  return 0;
}
