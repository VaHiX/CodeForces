/*
 * Problem URL : https://codeforces.com/contest/1669/problem/B
 * Submit Date : 2025-08-25
 */

#include <iostream>
#include <vector>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, f = -1;
    cin >> n;
    vector<int> v(n + 1, 0);
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      v[x] = v[x] + 1;
      if (v[x] >= 3)
        f = x;
    }
    cout << f << endl;
  }
}