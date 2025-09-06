/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;
using node = pair<int, int>;

const int maxn = 2e5 + 5;

int t, n, ma, sum, b[maxn], mp[maxn], s[maxn][2];
node a[maxn], ans;

void A(int f, int x, int c) {
  for (; x <= n; x += x & -x) {
    s[x][f] += c;
  }
}

int Q(int f, int x) {
  int c = 0;
  for (; x >= 1; x -= x & -x) {
    c += s[x][f];
  }
  return c;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
    }

    fill(s[1], s[n + 1], 0);
    ma = sum = 0, b[1] = 1;

    sort(a + 1, a + n + 1, [](node x, node y) { return x.second < y.second; });
    for (int i = 2; i <= n; i++) {
      b[i] = b[i - 1] + (a[i].second != a[i - 1].second);
    }
    for (int i = 1; i <= n; i++) {
      mp[b[i]] = a[i].second, a[i].second = b[i];
      A(0, a[i].second, 1);
    }
    sort(a + 1, a + n + 1);

    for (int i = n; i > 1; i--) {
      A(1, a[i].second, 1), A(0, a[i].second, -1);

      if (a[i].first != a[i - 1].first) {
        for (int l = 1, r = n + 1; l < r;) {
          int mid = (l + r) / 2;
          int b1 = Q(1, mid - 1) - Q(1, 0), b2 = Q(0, mid - 1) - Q(0, 0);
          int b3 = n - i + 1 - b1, b4 = i - 1 - b2;
          // n - i + 1 i - 1
          if (min({b1, b2, b3, b4}) > ma) {
            ma = min({b1, b2, b3, b4}), ans = {a[i].first, mp[mid]};
          }

          (min(b1, b2) < min(b3, b4) ? l = mid + 1 : r = mid);
        }
      }
    }
    cout << ma << '\n';
    cout << ans.first << ' ' << ans.second << '\n';
  }
  return 0;
}