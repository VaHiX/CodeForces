// Problem: CF 2090 F1 - Key of Like (Easy Version)
// https://codeforces.com/contest/2090/problem/F1

/*
 * Problem: F1. Key of Like (Easy Version)
 * Algorithm: Dynamic Programming with probability calculation
 * Time Complexity: O(n * l * k) where n is number of members, l is number of locks, k=0 for this version
 * Space Complexity: O(n * l * k) for storing DP states
 *
 * The problem simulates a game where n members take turns to match keys with locks.
 * Each member plays optimally and tries to maximize the expected number of successful matches.
 * This implementation uses dynamic programming with precomputed modular inverses.
 */

#include <cstdio>
#include <iosfwd>

#define Mod 1000000007
#define inv2 500000004
using namespace std;
int read() {
  int num = 0;
  char c = getchar();
  while (c < '0' || c > '9') {
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    num = num * 10 + (c & 15), c = getchar();
  }
  return num;
}
int n, l, k, f[26][5001][100], inv[20000], pre[101], p[100], q[100];
void init() {
  n = read(), l = read(), k = read();
  // Initialize base case for f[0]
  for (int i = 0; i < n; i++) {
    f[0][0][i] = 0;
  }
  // Dynamic programming over layers
  for (int i = 1; i <= l; i++) {
    int s = 1, a = i / n, b = i % n;
    // Compute prefix sum of previous state
    for (int j = 0; j < n; j++) {
      s = s + f[0][i - 1][j], s -= ((s >= Mod) ? Mod : 0);
    }
    s = 1ll * a * s % Mod;
    pre[0] = 0;
    for (int j = 0; j < n; j++) {
      pre[j + 1] = pre[j] + f[0][i - 1][j],
              pre[j + 1] -= ((pre[j + 1] >= Mod) ? Mod : 0);
    }
    pre[n]++, pre[n] -= ((pre[n] >= Mod) ? Mod : 0);
    // Compute segment sums using prefix array
    for (int j = 0; j < b; j++) {
      int temp = pre[j] + pre[n] - pre[n - b + j];
      temp -= ((temp >= Mod) ? Mod : 0), temp += ((temp < 0) ? Mod : 0);
      f[0][i][j] = temp;
    }
    for (int j = b; j < n; j++) {
      int temp = pre[j] - pre[j - b];
      temp += ((temp < 0) ? Mod : 0);
      f[0][i][j] = temp;
    }
    // Final adjustment using modular inverse
    for (int j = 0; j < n; j++) {
      f[0][i][j] = 1ll * (f[0][i][j] + s) * inv[i] % Mod;
    }
  }
  // Higher order DP computations
  for (int d = 1; d <= k; d++) {
    for (int i = 0; i < n; i++) {
      f[d][0][i] = 0;
    }
    for (int i = 1; i <= l; i++) {
      int s = 1, a = i / n, b = i % n;
      // Prefix sum computation
      for (int j = 0; j < n; j++) {
        s = s + f[d][i - 1][j], s -= ((s >= Mod) ? Mod : 0);
      }
      s = 1ll * a * s % Mod;
      pre[0] = 0;
      for (int j = 0; j < n; j++) {
        pre[j + 1] = pre[j] + f[d][i - 1][j],
                pre[j + 1] -= ((pre[j + 1] >= Mod) ? Mod : 0);
      }
      pre[n]++, pre[n] -= ((pre[n] >= Mod) ? Mod : 0);
      // Compute segment sums
      for (int j = 0; j < b; j++) {
        int temp = pre[j] + pre[n] - pre[n - b + j];
        temp -= ((temp >= Mod) ? Mod : 0), temp += ((temp < 0) ? Mod : 0);
        p[j] = temp;
      }
      for (int j = b; j < n; j++) {
        int temp = pre[j] - pre[j - b];
        temp += ((temp < 0) ? Mod : 0);
        p[j] = temp;
      }

      // Another prefix computation
      s = 1, a = i / n, b = i % n;
      for (int j = 0; j < n; j++) {
        s = s + f[d-1][i - 1][j], s -= ((s >= Mod) ? Mod : 0);
      }
      s = 1ll * a * s % Mod;
      pre[0] = 0;
      for (int j = 0; j < n; j++) {
        pre[j + 1] = pre[j] + f[d-1][i - 1][j],
                pre[j + 1] -= ((pre[j + 1] >= Mod) ? Mod : 0);
      }
      pre[n]++, pre[n] -= ((pre[n] >= Mod) ? Mod : 0);

      for (int j = 0; j < b; j++) {
        int temp = pre[j] + pre[n] - pre[n - b + j];
        temp -= ((temp >= Mod) ? Mod : 0), temp += ((temp < 0) ? Mod : 0);
        q[j] = temp;
      }
      for (int j = b; j < n; j++) {
        int temp = pre[j] - pre[j - b];
        temp += ((temp < 0) ? Mod : 0);
        q[j] = temp;
      }

      // Combine results for dp update
      for (int j = 0; j < n; j++) {
        f[d][i][j] = (1ll * p[j] + 1ll * s * d) * inv[i] % Mod;
        if (f[d][i][j] < 0) f[d][i][j] += Mod;
      }
    }
  }
  // Output final results for test case
  for (int i = 0; i < n; i++) {
    printf("%d ", f[k][l][i]);
  }
  printf("\n");
}
void init_inv() {
  inv[1] = 1;
  for (int i = 2; i <= 5000; i++) {
    inv[i] = 1ll * (Mod - Mod / i) * inv[Mod % i] % Mod;
  }
}

int main() {
  init_inv();
  int t = read();
  while (t--) {
    init();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/