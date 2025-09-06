/*
 * Problem URL : https://codeforces.com/contest/805/problem/A
 * Submit Date : 2025-08-31
 */



#include <bits/stdc++.h>

typedef long long int ll;

#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");

#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie();

  ll i, j, k;
  ll u, v, n;
  ll l, r;

  cin >> l >> r;

  if (l == r)
    cout << l;
  else
    cout << "2";

  cin.clear();
  cin.ignore();

  return 0;
}
