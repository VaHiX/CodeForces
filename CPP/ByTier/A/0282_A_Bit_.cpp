/*
 * Problem URL : https://codeforces.com/problemset/problem/282/A
 * Submit Date : 2025-08-09
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  int n, x(0);
  cin >> n;

  string s;
  while (n--) {
    cin >> s;
    if (s[1] == '+') {
      ++x;
    } else {
      --x;
    }
  }

  cout << x << endl;
  return 0;
}
