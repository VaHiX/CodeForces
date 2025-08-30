/*
 * Problem URL : https://codeforces.com/problemset/problem/225/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  bool possible(true);
  int n, x, a, b;
  cin >> n >> x;
  while (n--) {
    cin >> a >> b;
    if (x == a || x == b || x == 7 - a || x == 7 - b) {
      possible = false;
    }
    x = 7 - x;
  }
  cout << (possible ? "YES" : "NO") << endl;
  return 0;
}
