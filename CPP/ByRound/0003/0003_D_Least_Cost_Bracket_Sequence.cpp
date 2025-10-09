/*
 * Problem URL : https://codeforces.com/problemset/problem/3/D
 * Submit Date : 2025-08-09
 */

#include <bits/stdc++.h>
using namespace std;

string s;
set<pair<int, int>> st;
long long b, c, l, r;

int main() {
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(') {
      b++;
    } else if (s[i] == ')') {
      b--;
    } else {
      cin >> l >> r, b--, s[i] = ')', c += r, st.insert({l - r, i});
    }
    while (b < 0 && st.size()) {
      b += 2, s[(*st.begin()).second] = '(', c += (*st.begin()).first,
              st.erase(st.begin());
    }
    if (b < 0) {
      break;
    }
  }
  (b != 0) ? cout << -1 : cout << c << '\n' << s;
}