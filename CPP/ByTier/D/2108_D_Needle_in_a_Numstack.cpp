/*
 * Problem URL : https://codeforces.com/problemset/problem/2108/D
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
int n, k;
int ask(int t) {
  int ans;
  cout << "? " << t + 1 << endl;
  cin >> ans;
  return ans;
}
int find(int p, int ans) {
  int l = 1, r = (n - p - 1) / k + 1, mid;
  while (l <= r) {
    mid = (l + r) / 2;
    if (ask(k * (mid - 1) + p) == ans) {
      l = mid + 1;
    } else
      r = mid - 1;
  }
  return r;
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    if (n == 2 * k) {
      cout << "! " << k << " " << k << endl;
      continue;
    }
    int p, ans1, ans2;
    for (p = 0; p < k; p++) {
      ans1 = ask(p);
      ans2 = ask(k * ((n - p - 1) / k) + p);
      if (ans1 != ans2) {
        break;
      }
    }
    if (p == k) {
      cout << "! -1" << endl;
      continue;
    }
    int t = find(p, ans1);
    int r = min(k * t + p - 1, n - k - 1);
    p += max(0, k - 1 - (k * (t - 1) + p));
    int l = k * (t - 1) + p;
    int sta = l;
    for (int i = 1; i < k - p && l < r && sta + i <= r; i++) {
      ans1 = ask(p + i);
      ans2 = ask(k * ((n - (p + i) - 1) / k) + (p + i));
      if (ans1 != ans2) {
        ans2 = ask(sta + i);
        if (ans1 == ans2) {
          l = sta + i;
        } else {
          r = sta + i - 1;
        }
      }
    }
    if (l == r) {
      cout << "! " << l + 1 << " " << n - l - 1 << endl;
    } else {
      cout << "! -1" << endl;
    }
  }
  return 0;
}