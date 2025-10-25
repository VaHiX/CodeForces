/*
 * Problem URL : https://codeforces.com/contest/296/problem/D
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define inf 100000000
const int x = 505;

using namespace std;

ll dist[x][x];
int mark[x];

int main() {

  int i, j, k;
  int n, m, t;

  scanf("%d", &n);

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++)
      scanf("%I64d", &dist[i][j]);
  }

  for (i = 1; i <= n; i++)
    mark[i] = 1;

  int *a = new int[n];
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]), mark[a[i]] = 0;

  mark[a[n - 1]] = 1;

  if (n == 1) {
    cout << "0";
    return 0;
  }

  vector<ll> v;
  v.push_back(0);

  m = n - 2;
  mark[a[m]] = 1;
  m--;

  for (k = 1; k <= n; k++) {
    if (!mark[k])
      continue;

    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  ll sum = 0;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (mark[i] && mark[j])
        sum += dist[i][j];
    }
  }

  v.push_back(sum);

  while (m >= 0) {
    mark[a[m]] = 1;

    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        dist[i][j] = min(dist[i][j], dist[i][a[m]] + dist[a[m]][j]);
      }
    }

    sum = 0;
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        if (mark[i] && mark[j])
          sum += dist[i][j];
      }
    }

    v.push_back(sum);
    m--;
  }

  for (i = v.size() - 1; i >= 0; i--)
    printf("%I64d ", v[i]);

  return 0;
}
