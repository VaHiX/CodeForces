/*
 * Problem URL : https://codeforces.com/contest/344/problem/C
 * Submit Date : 2025-09-06
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
#define N 100005
#define inf 100000000
#define pp pair<int, int>

using namespace std;

ll cnt = 0;
void R(ll a, ll b) {
  if (b == 1) {
    cnt += a;
    return;
  }

  if (a > b) {
    ll x = a / b;
    cnt += x;
    a -= (x * b);

    R(a, b);
  }

  else {
    b = b - a;
    cnt++;
    R(b, a);
  }
}

int main() {

  ll i, j, k;
  ll n, m;
  ll a, b;

  cin >> a >> b;
  m = __gcd(a, b);

  a = a / m;
  b = b / m;

  R(a, b);

  cout << cnt;

  return 0;
}
