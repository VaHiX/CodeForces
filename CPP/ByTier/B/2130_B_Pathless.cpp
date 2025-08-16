/*
 * Problem URL : https://codeforces.com/problemset/problem/2130/B
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    int sum = accumulate(a.begin(), a.end(), 0);
    int rem = s - sum;

    if (s < sum || rem == 1) {
      vector<int> zeros, twos, ones;
      for (int x : a) {
        if (x == 0)
          zeros.push_back(x);
        else if (x == 2)
          twos.push_back(x);
        else if (x == 1)
          ones.push_back(x);
      }

      for (int x : zeros)
        cout << x << " ";
      for (int x : twos)
        cout << x << " ";
      for (int x : ones)
        cout << x << " ";
      cout << endl;
    } else {
      cout << -1 << endl;
    }
  }
}
