/*
 * Problem URL : https://codeforces.com/problemset/problem/912/B
 * Submit Date : 2025-08-14
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
#include <time.h>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n");
#define nl printf("\n");
#define N 200
#define inf 10000000000
#define pp pair<char, int>

using namespace std;

int main() {

  ll i, j, k;
  ll n, m;

  cin >> n >> k;

  if (k == 1) {
    cout << n;
    return 0;
  }

  m = 1;
  while (m < n) {
    m = 2 * m + 1;
  }

  cout << m;

  return 0;
}
