/*
 * Problem URL : https://codeforces.com/contest/298/problem/A
 * Submit Date : 2025-09-06
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  size_t n;
  string s;
  cin >> n >> s;

  for (size_t i = 0; i < n; ++i) {
    if (s[i] != '.') {
      if (s[i] == 'R') {
        while (s[i] == 'R') {
          ++i;
        }
        cout << i << " " << i + 1 << endl;
      } else {
        cout << i + 1 << " " << i << endl;
      }
      break;
    }
  }

  return 0;
}
