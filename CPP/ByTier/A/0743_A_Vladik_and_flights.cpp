/*
 * Problem URL : https://codeforces.com/contest/743/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
int main() {
  ll i, j, k;
  ll n, a, b;
  string s;

  cin >> n >> a >> b;
  cin >> s;

  a--;
  b--;

  if (s[a] == s[b])
    cout << "0";
  else
    cout << "1";

  return 0;
}
