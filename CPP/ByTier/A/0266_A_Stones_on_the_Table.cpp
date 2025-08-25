/*
 * Problem URL : https://codeforces.com/problemset/problem/266/A
 * Submit Date : 2025-08-09
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
  size_t n;
  cin >> n;
  string s;
  cin >> s;
  s.erase(unique(s.begin(), s.end()), s.end());
  cout << n - s.length() << endl;
  return 0;
}
