/*
 * Problem URL : https://codeforces.com/contest/769/problem/A
 * Submit Date : 2025-09-01
 */



#include <bits/stdc++.h>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("xxxx");
#define pi 3.1416

#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)

using namespace std;

int main() {

  ll i, j, k;
  ll n;

  cin >> n;
  ll a[n];

  for (i = 0; i < n; i++)
    cin >> a[i];

  sort(a, a + n);

  cout << a[n / 2];

  return 0;
}
