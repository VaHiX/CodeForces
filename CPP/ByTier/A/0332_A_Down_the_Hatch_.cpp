/*
 * Problem URL : https://codeforces.com/problemset/problem/332/A
 * Submit Date : 2025-08-16
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  int n, glasses(0);
  string s;
  cin >> n >> s;
  for (int i = n; i < s.length(); i += n) {
    if (s[i - 1] == s[i - 2] && s[i - 2] == s[i - 3]) {
      ++glasses;
    }
  }
  cout << glasses << endl;
  return 0;
}
