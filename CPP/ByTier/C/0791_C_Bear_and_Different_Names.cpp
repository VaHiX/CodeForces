/*
 * Problem URL : https://codeforces.com/problemset/problem/791/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#define N 200
using namespace std;
string s[N], s1;
int n, k;
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    s[i] = "Aa", s[i][0] += i / 26, s[i][1] += i % 26;
  for (int i = 1; i <= n - k + 1; i++) {
    cin >> s1;
    if (s1[0] == 'N')
      s[i + k - 1] = s[i];
  }
  for (int i = 1; i <= n; i++)
    cout << s[i] << ' ';
  printf("\n");
}