/*
 * Problem URL : https://codeforces.com/problemset/problem/913/A
 * Submit Date : 2025-08-16
 */

#define _CRT_SECURE_NO_WARNINGS

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
#include <time.h>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 150010
#define inf 1000000000
#define pp pair<int, int>

using namespace std;

int main() {

  ll i, j, k;
  ll n, m;
  ll x, y;

  scanf("%I64d%I64d", &n, &m);

  x = 2;
  y = 1;
  while (y < n) {
    if (x > m) {
      cout << m << endl;
      return 0;
    }

    x *= 2;
    y++;
  }

  if (x == m)
    cout << '0' << endl;

  else
    cout << (m % x) << endl;

  return 0;
}
