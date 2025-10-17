/*
 * Problem URL : https://codeforces.com/contest/1283/problem/C
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
priority_queue<int> q;
int n, a[200020], d[200020], b[200020];
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", a + i), b[i] = a[i], d[a[i]] = 1;
  for (int i = 1; i <= n; i++)
    if (!d[i])
      q.push(i);
  for (int i = 1; i <= n; i++)
    if (!a[i])
      a[i] = q.top(), q.pop();
  for (int i = 1, j = 0; i <= n; i++)
    if (a[i] == i) {
      while (b[j + 1] || j + 1 == i)
        j = (j + 1) % n;
      swap(a[i], a[j + 1]);
    }
  for (int i = 1; i <= n; i++) {
    printf("%d ", a[i]);
  }
}
