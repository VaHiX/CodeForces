/*
 * Problem URL : https://codeforces.com/contest/884/problem/A
 * Submit Date : 2025-08-31
 */



#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000

using namespace std;

int main() {

  int i, j, k;
  int n, t, m;

  cin >> n >> t;

  int cnt = 0;
  while (n--) {
    cin >> m;

    k = 86400 - m;
    t -= k;
    cnt++;

    if (t <= 0)
      break;
  }

  cout << cnt;

  return 0;
}
