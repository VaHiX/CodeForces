/*
 * Problem URL : https://codeforces.com/problemset/problem/244/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  int n, k, a[30];
  bool b[901] = {false};
  cin >> n >> k;
  for (int i = 0; i < k; ++i) {
    cin >> a[i];
    b[a[i]] = true;
  }
  int d = 0;
  for (int i = 0; i < k; ++i) {
    cout << a[i];
    for (int j = 1; j < n; ++j) {
      ++d;
      while (b[d]) {
        ++d;
      }
      cout << " " << d;
    }
    cout << endl;
  }
  return 0;
}
