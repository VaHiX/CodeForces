// Problem: CF 2144 E1 - Looking at Towers (easy version)
// https://codeforces.com/contest/2144/problem/E1

/*
Problem: Looking at Towers (easy version)
Time Complexity: O(n^2) per test case
Space Complexity: O(n)

Algorithms/Techniques:
- Dynamic Programming with prefix and suffix processing
- Monotonic stacks to track visible towers from left and right
- Counting valid subsequences using DP states

This problem counts the number of subsequences where the set of visible heights from left 
and right matches the original sequence. It uses dynamic programming to compute valid 
subsequences ending at each position, considering how elements contribute to visibility.

*/

#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 5100, mod = 998244353;
int h[maxn], f[maxn], g[maxn];
int ff[maxn], gg[maxn];
int cL, cR;
int L[maxn], R[maxn];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int H = 0;
    for (int i = 1; i <= n; i++) {
      cin >> h[i];
      H = max(H, h[i]);
      f[i] = g[i] = 0;
    }
    int m = 0, l = 0, r;
    for (int i = 1; i <= n; i++) {
      if (h[i] == H) {
        m++;
        r = i;
        if (!l) {
          l = i;
        }
      }
    }
    cL = cR = 0;
    // Build monotonic stack from left to find visible elements
    for (int i = 1; i <= n; i++) {
      if (h[i] > L[cL]) {
        L[++cL] = h[i];
      }
    }
    // Build monotonic stack from right to find visible elements
    for (int i = n; i >= 1; i--) {
      if (h[i] > R[cR]) {
        R[++cR] = h[i];
      }
    }
    f[0] = 1;
    ff[0] = f[cL - 1];
    // DP from left to right
    for (int i = 1; i <= n; i++) {
      for (int j = cL; L[j] >= h[i]; j--) {
        f[j] = (f[j] << 1) % mod;
        if (L[j] == h[i]) {
          f[j] = (f[j] + f[j - 1]) % mod;
        }
      }
      ff[i] = f[cL - 1];
    }
    g[0] = 1;
    // DP from right to left
    for (int i = n; i >= 1; i--) {
      gg[i] = (g[cR] + g[cR - 1]) % mod;
      for (int j = cR; R[j] >= h[i]; j--) {
        g[j] = (g[j] << 1) % mod;
        if (R[j] == h[i]) {
          g[j] = (g[j] + g[j - 1]) % mod;
        }
      }
    }
    int ans = 0;
    // Count valid subsequences
    for (int i = 1; i <= n; i++) {
      if (h[i] == H) {
        ans += ff[i - 1] * (long long)gg[i] % mod;
        ans %= mod;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/