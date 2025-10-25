/*
 * Problem URL : https://codeforces.com/contest/379/problem/C
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
pair<int, int> p[300005];
int ans[300005];
int main() {
  int n, i, curr;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &p[i].first);
    p[i].second = i;
  }
  sort(p, p + n);
  curr = 0;
  for (i = 0; i < n; i++) {
    curr = max(curr + 1, p[i].first);
    ans[p[i].second] = curr;
  }
  for (i = 0; i < n; i++)
    printf("%d ", ans[i]);
  return 0;
}