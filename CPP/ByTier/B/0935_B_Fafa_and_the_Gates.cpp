/*
 * Problem URL : https://codeforces.com/problemset/problem/935/B
 * Submit Date : 2025-08-23
 */

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>

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
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n");
#define N 15
#define inf 100000
#define pp pair<char, char>

using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int x, y;
  int a, b;
  int x0, y0;

  string s;

  cin >> n;
  cin >> s;

  ll cnt = 0;
  x = 0, y = 0;

  if (s[0] == 'R')
    x++;
  else
    y++;

  x0 = 0, y0 = 0;
  for (i = 1; i < n; i++) {
    a = x, b = y;
    if (s[i] == 'R')
      a++;
    else
      b++;

    if (a == b) {
      x0 = x;
      y0 = y;
      x = a;
      y = b;
    }

    else {
      if (x == y) {
        if (abs(a - x0) >= 2 || abs(b - y0) >= 2)
          cnt++;
      }

      x0 = x;
      y0 = y;
      x = a;
      y = b;
    }
  }

  printf("%I64d", cnt);

  return 0;
}
