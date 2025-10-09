/*
 * Problem URL : https://codeforces.com/problemset/problem/710/E
 * Submit Date : 2025-08-21
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
#include <sstream>
#include <stack>
#include <string>
#include <time.h>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 15
#define inf 100000
#define pp pair<int, int>

using namespace std;

int main() {

  ll i, j, k;
  ll n, m, cur;
  ll x, y;

  cin >> n >> x >> y;

  ll *a = new ll[n + 1];

  a[0] = 0;
  a[1] = x;
  for (i = 2; i <= n; i++) {

    if (i % 2)
      k = a[(i + 1) / 2] + x;
    else
      k = a[i / 2];

    a[i] = min(a[i - 1] + x, k + y);
  }

  cout << a[n] << endl;

  return 0;
}
