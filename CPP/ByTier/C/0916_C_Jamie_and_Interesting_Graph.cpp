/*
 * Problem URL : https://codeforces.com/contest/916/problem/C
 * Submit Date : 2025-08-31
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
#define N 100
#define inf 100000

using namespace std;

int main() {

  int i, j, k;
  int n, m;
  int p = 100003, x = 10000000;

  cin >> n >> m;

  cout << p << " " << p << endl;
  for (i = 1; i <= n - 2; i++) {
    cout << i << " " << (i + 1) << " 1" << endl;
    p--;
  }

  cout << (n - 1) << " " << (n) << " " << p << endl;
  m -= (n - 1);

  for (i = 1; i < n - 1; i++) {
    for (j = i + 1; j <= n; j++) {

      if (i + 1 == j)
        continue;

      if (!m)
        return 0;

      cout << i << " " << j << " " << x << endl;
      m--;
    }
  }

  return 0;
}
