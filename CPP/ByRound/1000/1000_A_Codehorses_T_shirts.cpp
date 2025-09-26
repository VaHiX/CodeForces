/*
 * Problem URL : https://codeforces.com/contest/1000/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
int n, a;
int main(void) {
  string s;
  map<string, int> m;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> s, m[s]++;
  for (int i = 0; i < n; i++) {
    cin >> s;
    if (m[s] > 0)
      m[s]--;
    else
      a++;
  }
  cout << a;
}