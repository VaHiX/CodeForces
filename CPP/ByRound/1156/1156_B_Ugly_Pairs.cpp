/*
 * Problem URL : https://codeforces.com/contest/1156/problem/B
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    string s1, s2;
    for (int i = 0; i < s.size(); i++)
      if (s[i] & 1)
        s1 += s[i];
      else
        s2 += s[i];
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    if (abs(s2[0] - s1[s1.size() - 1]) != 1)
      cout << s1 + s2 << endl;
    else if (abs(s2[s2.size() - 1] - s1[0]) != 1)
      cout << s2 + s1 << endl;
    else
      cout << "No answer" << endl;
  }
}
