/*
 * Problem URL : https://codeforces.com/problemset/problem/1042/B
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, i, j, k;
  cin >> n;
  long c, d[8] = {0};
  for (i = 1; i < 8; i++)
    d[i] = 1000000;
  for (i = 0; i < n; i++) {
    int s = 0;
    string st;
    cin >> c >> st;
    for (j = 0; j < st.length(); j++)
      s |= (1 << (st[j] - 'A'));
    for (j = 0; j < 8; j++)
      d[s | j] = min(d[s | j], d[j] + c);
  }
  if (d[7] >= 1000000)
    cout << "-1";
  else
    cout << d[7];
}