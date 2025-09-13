/*
 * Problem URL : https://codeforces.com/problemset/problem/1257/C
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
auto max_int = numeric_limits<int>::max();
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t, n, e, i;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> B(n + 1, -1);
    int bst = max_int;
    for (i = 0; i < n; B[e] = i++) {
      cin >> e;
      bst = min(B[e] + 1 ? i - B[e] + 1 : max_int, bst);
    }
    cout << (bst == max_int ? -1 : bst) << '\n';
  }
}