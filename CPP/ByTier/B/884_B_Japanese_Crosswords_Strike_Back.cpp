/*
 * Problem URL : https://codeforces.com/problemset/problem/884/B
 * Submit Date : 2025-08-16
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
  int n, t, m, x;

  cin >> n >> x;

  int cnt = n - 1;
  for (i = 0; i < n; i++) {
    cin >> m;
    cnt += m;
  }

  if (cnt == x)
    cout << "YES";

  else
    cout << "NO";

  return 0;
}
