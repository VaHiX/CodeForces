/*
 * Problem URL : https://codeforces.com/problemset/problem/621/B
 * Submit Date : 2025-08-23
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

using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int x, y;

  cin >> n;

  map<int, int> add;
  map<int, int> subtract;

  ll cnt = 0;

  for (i = 1; i <= n; i++) {
    cin >> x >> y;

    cnt += add[x + y];
    add[x + y]++;
    cnt += subtract[x - y];
    subtract[x - y]++;
  }

  cout << cnt;

  return 0;
}
