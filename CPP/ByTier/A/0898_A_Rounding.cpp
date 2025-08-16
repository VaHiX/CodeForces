/*
 * Problem URL : https://codeforces.com/problemset/problem/898/A
 * Submit Date : 2025-08-13
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
#define inf 1000000000
#define pp pair<string, int>

using namespace std;

int main() {

  ll i, j, k;
  ll n, m, t;

  scanf("%I64d", &n);

  m = n % 10;

  if (m == 0) {
    printf("%I64d", n);
    return 0;
  }

  if (m >= 5) {
    t = n / 10;
    printf("%I64d0", t + 1);
  }

  else {
    t = n / 10;
    if (n > 9)
      printf("%I64d0", t);
    else
      printf("0");
  }

  return 0;
}
