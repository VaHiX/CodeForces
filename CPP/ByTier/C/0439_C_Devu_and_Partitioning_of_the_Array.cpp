/*
 * Problem URL : https://codeforces.com/contest/439/problem/C
 * Submit Date : 2025-09-05
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
#define N 100010
#define inf 100000
#define pp pair<int, int>

using namespace std;

vector<int> v[N];

int main() {

  int i, j, k;
  int n, m, p;
  int kt;

  scanf("%d%d%d", &n, &kt, &p);

  vector<int> ev;
  vector<int> odd;

  for (i = 0; i < n; i++) {
    scanf("%d", &m);

    if (m % 2)
      odd.push_back(m);
    else
      ev.push_back(m);
  }

  if (ev.size() >= p) {
    k = ev.size() - 1;
    for (i = 1; i < p; i++)
      v[i].push_back(ev[k]), k--, ev.pop_back();

    while (ev.size() && p > 0) {
      v[p].push_back(ev[k]);
      k--;
      ev.pop_back();
    }
  }

  else {
    k = ev.size() - 1;
    i = 1;
    while (ev.size() > 0) {
      v[i].push_back(ev[k]);
      k--;
      ev.pop_back();
      i++;
    }

    k = odd.size() - 1;
    for (j = i; j <= p; j++) {
      if (odd.size() < 2) {
        printf("NO\n");
        return 0;
      }

      v[j].push_back(odd[k]);
      odd.pop_back();
      k--;
      v[j].push_back(odd[k]);
      odd.pop_back();
      k--;
    }
  }

  k = ev.size() - 1;
  while (ev.size()) {
    v[1].push_back(ev[k]);
    k--;
    ev.pop_back();
  }

  if (odd.size() < (kt - p)) {
    printf("NO\n");
    return 0;
  }

  k = odd.size() - 1;
  for (i = p + 1; i <= kt; i++) {
    v[i].push_back(odd[k]);
    odd.pop_back();
    k--;
  }

  if (odd.size() % 2) {
    printf("NO\n");
    return 0;
  }

  else {

    k = odd.size() - 1;
    while (odd.size() > 0) {
      v[1].push_back(odd[k]);
      k--;
      odd.pop_back();
    }
  }

  if (ev.size()) {
    printf("NO\n");
    return 0;
  }

  printf("YES\n");
  for (i = 1; i <= kt; i++) {
    printf("%d ", v[i].size());
    for (j = 0; j < v[i].size(); j++)
      printf("%d ", v[i][j]);

    printf("\n");
  }

  return 0;
}
