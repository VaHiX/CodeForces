/*
 * Problem URL : https://codeforces.com/problemset/problem/228/A
 * Submit Date : 2025-08-09
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> s(4);
  cin >> s[0] >> s[1] >> s[2] >> s[3];
  sort(s.begin(), s.end());
  s.erase(unique(s.begin(), s.end()), s.end());
  cout << 4 - s.size() << endl;
  return 0;
}
