/*
 * Problem URL : https://codeforces.com/problemset/problem/518/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;

char opp_case(char x) {
  if (x >= 'a') {
    return (char)(x - 32);
  } else {
    return (char)(x + 32);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s, t;
  cin >> s >> t;
  map<char, int> tt;
  for (char x : t)
    tt[x]++;

  int y = 0, w = 0;
  for (char &x : s) {
    if (tt[x] > 0) {
      tt[x]--;
      y++;
      x = ' ';
    }
  }
  for (char x : s) {
    if (tt[opp_case(x)] > 0) {
      tt[opp_case(x)]--;
      w++;
    }
  }
  cout << y << ' ' << w << endl;
  return 0;
}