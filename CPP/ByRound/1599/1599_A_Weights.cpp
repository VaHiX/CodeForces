/*
 * Problem URL : https://codeforces.com/contest/1599/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  int hat[n];
  for (int i = 0; i < n;)
    cin >> hat[i++];
  sort(hat, hat + n);
  string s;
  cin >> s;
  int change = 0;
  for (int i = 1; i < n; i++)
    change += (s[i] != s[i - 1]);
  int l = n - 2 - change;
  int r = n - change;
  cout << hat[r - 1] << " " << s[0] << "\n";
  bool right = s[0] == 'R';
  bool left = right;
  for (int i = 1; i < n; i++) {
    if (s[i - 1] == s[i]) {
      right ^= 1;
      if (right)
        cout << hat[l--] << " R\n";
      else
        cout << hat[l--] << " L\n";
    } else {
      left ^= 1;
      if (left)
        cout << hat[r++] << " R\n";
      else
        cout << hat[r++] << " L\n";
    }
  }
  return 0;
}