/*
 * Problem URL : https://codeforces.com/contest/2140/problem/A
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int c = count(s.begin(), s.end(), '0');
    cout << count(s.begin(), s.begin() + c, '1') << "\n";
  }
}
