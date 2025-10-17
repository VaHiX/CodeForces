

/*
 * Problem URL : https://codeforces.com/problemset/problem/190/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
string a = "", s;
bool e = false;
void rd() {
  if (cin >> s) {
    a += s;
    if (s[0] == 'p') {
      a += "<";
      rd();
      a += ",";
      rd();
      a += ">";
    }
  } else
    e = true;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  rd();
  cout << (e || (cin >> s) ? "Error occurred" : a) << "\n";
}
