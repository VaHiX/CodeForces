/*
 * Problem URL : https://codeforces.com/problemset/problem/6/D
 * Submit Date : 2025-08-09
 */

#include <bits/stdc++.h>
using namespace std;
int c[15], Min = 1e9;
vector<int> vec, vec2;
int n, a, b;
void dfs(int t, int sum) {
  if (sum >= Min)
    return;
  if (t == n) {
    if (c[n] < 0) {
      Min = sum;
      vec = vec2;
    }
    return;
  }
  for (int i = 0; i <= max(max(c[t - 1] / b, c[t] / a), c[t + 1] / b) + 1; i++)
    if (c[t - 1] - b * i < 0) {
      c[t - 1] -= b * i;
      c[t] -= a * i;
      c[t + 1] -= b * i;
      for (int j = 1; j <= i; j++)
        vec2.push_back(t);
      dfs(t + 1, sum + i);
      c[t - 1] += b * i;
      c[t] += a * i;
      c[t + 1] += b * i;
      for (int j = 1; j <= i; j++)
        vec2.pop_back();
    }
}
int main() {
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]);
  dfs(2, 0);
  printf("%d\n", Min);
  for (auto i : vec)
    printf("%d ", i);
}