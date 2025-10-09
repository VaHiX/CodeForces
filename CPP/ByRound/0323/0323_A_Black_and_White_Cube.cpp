/*
 * Problem URL : https://codeforces.com/contest/323/problem/A
 * Submit Date : 2025-09-06
 */

// jiudge: 4139
#include <bits/stdc++.h>
using namespace std;

int main() {
  int k;

  cin >> k;
  if (k % 2) {
    cout << -1;
    return 0;
  } else {
    for (int i = 1; i <= k; i++) {
      int d = i % 2;
      for (int j = 1; j <= k; j++) {
        int e;
        e = (j + 1) / 2 % 2;
        if (!d)
          e = -e + 1;
        int f = e;
        for (int x = 1; x <= k; x += 2) {
          if (f)
            cout << "bb";
          else
            cout << "ww";
          f = -f + 1;
        }
        cout << '\n';
      }
      cout << '\n';
    }
  }

  return 0;
}