/*
 * Problem URL : https://codeforces.com/problemset/problem/255/B
 * Submit Date : 2025-08-09
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  string s;
  cin >> s;

  int nx(0), ny(0);
  for (char c : s) {
    if (c == 'x') {
      nx += 1;
    } else {
      ny += 1;
    }
  }
  if (nx > ny) {
    s.assign(nx - ny, 'x');
  } else {
    s.assign(ny - nx, 'y');
  }
  cout << s << endl;
  return 0;
}
