/*
 * Problem URL : https://codeforces.com/contest/458/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
#define mxn 100005
using namespace std;
int a[mxn], b[mxn];
char s1[mxn], s2[mxn];
int main() {
  scanf("%s %s", s1, s2);
  int n1 = strlen(s1), n2 = strlen(s2);

  int n = max(n1, n2);
  for (int i = 0; i < n1; i++)
    a[n - n1 + i] = s1[i] - '0';
  for (int i = 0; i < n2; i++)
    b[n - n2 + i] = s2[i] - '0';

  int flag = 0;
  for (int i = 0; i < n && !flag; i++) {
    int mn = min(a[i], b[i]);
    a[i] -= mn;
    b[i] -= mn;

    a[i + 1] += a[i], a[i + 2] += a[i];
    b[i + 1] += b[i], b[i + 2] += b[i];

    if (a[i] > n)
      flag = 1;
    else if (b[i] > n)
      flag = 2;
  }

  if (!flag) {
    if (a[n] > b[n])
      flag = 1;
    else if (a[n] < b[n])
      flag = 2;
    else {
      if (a[n + 1] > b[n + 1])
        flag = 1;
      else if (a[n + 1] < b[n + 1])
        flag = 2;
    }
  }

  if (flag == 1)
    puts(">");
  else if (flag == 2)
    puts("<");
  else
    puts("=");

  return 0;
}
