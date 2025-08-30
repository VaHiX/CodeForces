/*
 * Problem URL : https://codeforces.com/contest/2073/problem/E
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
int n;
int stk[210], fa[210], top;
int query(vector<bool> x) {
  printf("query ");
  for (bool v : x) {
    if (v)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
  fflush(stdout);
  int ans;
  scanf("%d", &ans);
  return ans;
}
string Solve(int l, int r) {
  if (l == r)
    return "x";
  for (int j = r; j > l; --j) {
    if (fa[j] == l) {
      string ans = "(";
      ans = ans + Solve(l, j - 1) + "-";
      ans = ans + Solve(j, r) + ")";
      return ans;
    }
  }
  return "";
}
void solve() {
  stk[++top] = 0;
  stk[++top] = 1;
  for (int i = 2; i < n; ++i) {
    vector<bool> x(n);
    for (int i = 0; i < n; ++i)
      x[i] = 0;
    for (int i = 1; i <= top; ++i)
      x[stk[i]] = 1;
    x[i] = 1;
    if (query(x) == (top & 1))
      --top;
    while (1) {
      if (top <= 2) {
        fa[i] = stk[top];
        stk[++top] = i;
        break;
      }
      vector<bool> x(n);
      for (int i = 0; i < n; ++i)
        x[i] = 0;
      for (int i = 1; i <= top - 2; ++i)
        x[stk[i]] = 1;
      x[i] = 1;
      if (query(x) == (top & 1)) {
        fa[i] = stk[top];
        stk[++top] = i;
        break;
      } else
        top -= 2;
    }
  }
  printf("answer ");
  cout << Solve(0, n - 1) << '\n';
  fflush(stdout);
  return;
}
int main() {
  scanf("%d", &n);
  solve();
  return 0;
}