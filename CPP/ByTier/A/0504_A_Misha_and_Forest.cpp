/*
 * Problem URL : https://codeforces.com/contest/504/problem/A
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 2e6 + 5;
queue<int> q;
int b, d[maxn], s[maxn], ex[maxn], ey[maxn];
int main() {

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &d[i], &s[i]);
    if (d[i] == 1)
      q.push(i);
  }
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    if (d[i] == 1) {
      ex[b] = i;
      ey[b] = s[i];
      b++;

      s[s[i]] ^= i;
      d[s[i]]--;
      if (d[s[i]] == 1)
        q.push(s[i]);
    }
  }
  printf("%d\n", b);
  for (int i = 0; i < b; i++)
    printf("%d %d\n", ex[i], ey[i]);
  return 0;
}
