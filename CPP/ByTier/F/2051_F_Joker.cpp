/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, q, t, x, ans, l, r;
bool b;
struct node {
  int x, y;
} a[3];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> q;
    a[0] = (node){1, -q};
    a[1] = (node){m, m};
    a[2] = (node){n + q + 1, n};
    while (q--) {
      cin >> x;
      b = false;
      for (int i = 0; i < 3; ++i) {
        if (x < a[i].x)
          a[i].x = max(1, a[i].x - 1);
        else if (x > a[i].y)
          a[i].y = min(n, a[i].y + 1);
        else {
          b = true;
          if (a[i].x == a[i].y)
            a[i].x = n + q, a[i].y = -q;
        }
      }
      if (b) {
        a[0] = (node){1, max(1, a[0].y)};
        a[2] = (node){min(n, a[2].x), n};
      }
      l = 0, r = -1, ans = 0;
      for (int i = 0; i < 3; ++i) {
        if (a[i].x > a[i].y)
          continue;
        if (a[i].x > r) {
          ans += max(0, r - l + 1);
          l = a[i].x, r = a[i].y;
        }
        r = max(r, a[i].y);
      }
      ans += max(0, r - l + 1);
      cout << ans << " ";
    }
    cout << "\n";
  }
  return 0;
}