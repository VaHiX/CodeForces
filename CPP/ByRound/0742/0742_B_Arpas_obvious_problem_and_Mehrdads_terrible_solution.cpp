/*
 * Problem URL : https://codeforces.com/contest/742/problem/B
 * Submit Date : 2025-09-02
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 1001
#define mod 1000000007

using namespace std;

int main() {

  ll i, j, k;
  ll n, m, x;

  cin >> n >> x;

  map<ll, ll> mp;
  for (i = 0; i < n; i++) {
    cin >> m;
    mp[m]++;
  }

  ll cnt = 0, y;
  map<ll, ll>::iterator p = mp.begin();

  while (p != mp.end()) {
    m = x ^ p->first;

    if (m == p->first)
      y = (p->second - 1) * p->second;

    else
      y = p->second * mp[m];

    cnt += y;
    p++;
  }

  cout << cnt / 2 << endl;

  return 0;
}
