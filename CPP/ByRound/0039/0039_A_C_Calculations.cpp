/*
 * Problem URL : https://codeforces.com/problemset/problem/39/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int a, n, p, k, ans, b[1000];
string s;
int main() {
  cin >> a >> s;
  if (s[0] != '-')
    s = '+' + s;
  n = s.size();
  for (int i = 0; i < n; i += 3) {
    if (s[i] == '+')
      k = 1;
    else
      k = -1;
    i++;
    int j = 0;
    for (; s[i] >= '0' && s[i] <= '9'; i++)
      j = 10 * j + s[i] - '0';
    if (s[i] == '*')
      i++;
    else
      j = 1;
    j *= k;
    b[p++] = j;
    ans += (a - (s[i] == 'a')) * j;
  }
  sort(b, b + p);
  for (int i = 1; i <= p; i++)
    ans += i * b[i - 1];
  cout << ans;
}