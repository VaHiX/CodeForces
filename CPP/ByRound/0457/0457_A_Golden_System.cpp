/*
 * Problem URL : https://codeforces.com/contest/457/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
#define MOD 1000000007
#define MAX 200000
using namespace std;
string nrml(string s) {
  s = "000" + s;
  for (int i = 0; i + 1 < s.size(); ++i) {
    if (s[i] == '1' && s[i + 1] == '1') {
      int j = i + 1;
      while (s[j - 1] == s[j]) {
        s[j - 2] = '1';
        s[j - 1] = s[j] = '0';
        j -= 2;
      }
    }
  }
  return s;
}
void addZeros(string &a, string &b) {
  int mx = max(a.size(), b.size());
  string az(mx - a.size(), '0');
  string bz(mx - b.size(), '0');
  a = az + a;
  b = bz + b;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // cout<<nrml("1011")<<endl;
  string a, b;
  cin >> a >> b;
  a = nrml(a);
  b = nrml(b);
  addZeros(a, b);
  if (a == b)
    cout << "=" << endl;
  else if (a > b)
    cout << ">" << endl;
  else
    cout << "<" << endl;
  return 0;
}
