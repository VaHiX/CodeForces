/*
 * Problem URL : https://codeforces.com/problemset/problem/639/B
 * Submit Date : 2025-08-14
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
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 1001
#define pp pair<int, int>

using namespace std;

int main() {

  int i, j, k;
  int n, h, d;
  int h2, d2;

  cin >> n >> d >> h;

  if (d > 2 * h || d < h) {
    cout << "-1\n";
    return 0;
  }

  h2 = h;
  k = 1;

  vector<pp> v;

  while (h2--) {
    v.push_back({k, k + 1});
    k++;
  }

  if (d == h) {
    if (k == 2 && n > 2) {
      cout << "-1\n";
      return 0;
    }

    n -= (h + 1);
    k++;
    while (n--) {
      v.push_back({2, k});
      k++;
    }
  }

  else {

    d2 = abs(h - d);
    j = 1;
    k++;
    while (d2--) {
      v.push_back({j, k});
      j = k;
      k++;
    }

    while (k <= n) {
      v.push_back({1, k});
      k++;
    }
  }

  for (pp p : v)
    cout << p.first << " " << p.second << endl;

  return 0;
}
