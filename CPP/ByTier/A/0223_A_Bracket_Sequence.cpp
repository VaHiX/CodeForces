/*
 * Problem URL : https://codeforces.com/contest/223/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
int n, l[100005];
char a[100005];
struct node {
  int i;
  char x;
};
int mx, t, s[100005];
stack<node> q;
int main() {
  memset(l, -1, sizeof(l));
  scanf("%s", a + 1);
  n = strlen(a + 1);
  q.push({1, a[1]});
  for (int i = 1; i <= n; i++) {
    if (a[i] == '[')
      s[i] = s[i - 1] + 1;
    else
      s[i] = s[i - 1];
  }
  for (int i = 2; i <= n; i++) {
    if (q.empty() && (a[i] == ')' || a[i] == ']'))
      continue;
    if ((a[i] == ')' && q.top().x == '(') ||
        (a[i] == ']' && q.top().x == '[')) {
      l[i] = q.top().i;
      q.pop();
    } else if (a[i] == ')' || a[i] == ']') {
      while (!q.empty())
        q.pop();
    } else
      q.push({i, a[i]});
  }
  for (int i = 2; i <= n; i++) {
    if (l[i] < 0)
      continue;
    l[i] = (l[l[i] - 1] == -1 ? l[i] : l[l[i] - 1]);
  }
  for (int i = 2; i <= n; i++) {
    if (l[i] < 0)
      continue;
    if (mx <= s[i] - s[l[i] - 1]) {
      mx = s[i] - s[l[i] - 1];
      t = i;
    }
  }
  printf("%d\n", mx);
  if (mx == 0)
    return 0;
  for (int i = l[t]; i <= t; i++)
    putchar(a[i]);
  return 0;
} // 18335749873051414015