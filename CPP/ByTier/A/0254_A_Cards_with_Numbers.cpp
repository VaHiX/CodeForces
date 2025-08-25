/*
 * Problem URL : https://codeforces.com/problemset/problem/254/A
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int n, b[5001], s[600001], j;
int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int a;
  cin >> n;
  for (int i = 1; i <= 2 * n; i++) {
    scanf("%d", &a);
    if (b[a])
      s[j++] = i, s[j++] = b[a], b[a] = 0;
    else
      b[a] = i;
  }
  if (j != 2 * n)
    cout << -1;
  else {
    for (int i = 0; i < j; i += 2)
      printf("%d %d\n", s[i], s[i + 1]);
  }
}
