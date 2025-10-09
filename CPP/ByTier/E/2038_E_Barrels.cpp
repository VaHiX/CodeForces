/*
 * Problem URL : https://codeforces.com/contest/2038/problem/E
 * Submit Date : 2025-09-05
 */

#include <bits/stdc++.h>

using namespace std;
constexpr int _ = 2e5 + 5, mod = 998244353;

int n, a[_], h[_], f[_];
double b[_];

void work() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i] = b[i - 1] + a[i];
  }
  stack<int> st;
  st.push(1);
  h[1] = 1e9;
  for (int i = 2; i <= n; ++i) {
    cin >> h[i];
    while (h[st.top()] <= h[i]) {
      st.pop();
    }
    f[i] = st.top();
    st.push(i);
  }
  double x = a[n], y = 0;
  int j = n;
  for (int i = n; i > 1; --i) {
    // cout << i << " " << j << " " << x << " " << y << " " << h[i] / (i - j +
    // 1) << endl;
    x += 1.0 * h[i] / (i - j + 1);
    while (x > h[j]) {
      y += (x - h[j]) * (i - j + 1);
      x = h[j];
      if (y + b[j - 1] - b[f[j] - 1] >= x * (j - f[j])) {
        x = (y + b[j - 1] - b[f[j] - 1] + x * (i - j + 1)) / (i - f[j] + 1);
        y = 0;
        j = f[j];
      }
    }
    if (j == i) {
      x = y + a[i - 1];
      y = 0;
      --j;
    }
  }
  printf("%.10lf\n", x);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  // cin >> T;
  while (T--) {
    work();
  }
}
