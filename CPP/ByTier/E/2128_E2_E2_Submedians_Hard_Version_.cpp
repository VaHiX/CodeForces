/*
 * Problem URL : https://codeforces.com/problemset/problem/2128/E2
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int T, n, k, a[N], s[N], c[N], mn, mx, now;

bool Check(int x, int &ansl, int &ansr) {
  for (int i = 1; i <= n; ++i) {
    s[i] = s[i - 1] + (a[i] >= x ? 1 : -1);
  }
  for (int i = k, mn = n + 1, l = 0; i <= n; ++i) {
    if (s[i - k] < mn) {
      mn = s[i - k], l = i - k;
    }
    if (s[i] >= mn) {
      ansl = l + 1, ansr = i;
      return 1;
    }
  }
  return 0;
}

void Binary(int &ans, int &ansl, int &ansr) {
  int l = 1, r = n;
  while (l <= r) {
    int mid = l + r >> 1;
    if (Check(mid, ansl, ansr)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  Check(r, ansl, ansr), ans = r;
}

void Add(int x, int v) {
  c[x] += v, now += x >= mn ? v : -v;
}

void Solve() {
  fill_n(c + 1, n, 0), now = 0;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int l1, r1, l2, r2;
  Binary(mx, l2, r2);
  for (int i = 1; i <= n; ++i) {
    a[i] = n - a[i] + 1;
  }
  Binary(mn, l1, r1), mn = n - mn + 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = n - a[i] + 1;
  }
  for (int i = l1; i <= r1; ++i) {
    ++c[a[i]], now += a[i] >= mn ? 1 : -1;
  }
  cout << mx - mn + 1 << '\n';
  while (mn <= mx) {
    while (now >= 0) {
      cout << mn << ' ' << l1 << ' ' << r1 << '\n';
      now -= c[mn++] << 1;
    }
    if (l1 > l2) {
      Add(a[--l1], 1);
    } else if (r1 < r2) {
      Add(a[++r1], 1);
    } else if (l1 < l2) {
      Add(a[l1++], -1);
    } else if (r1 > r2) {
      Add(a[r1--], -1);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    Solve();
  }
  return 0;
}