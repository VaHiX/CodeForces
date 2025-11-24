// Problem: CF 2090 F2 - Key of Like (Hard Version)
// https://codeforces.com/contest/2090/problem/F2

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
  // Initialize the dp table for the first key (0 keys have been used)
  for (int i = 0; i < n; i++) {
    f[0][0][i] = 0;
  }
  // Dynamic programming for each step, considering up to l locks and no counterfeit keys
  for (int i = 1; i <= l; i++) {
    int s = 1, a = i / n, b = i % n;
    // Accumulate the sum from previous states
    for (int j = 0; j < n; j++) {
      s = s + f[0][i - 1][j], s -= ((s >= Mod) ? Mod : 0);
    }
    s = 1ll * a * s % Mod;
    pre[0] = 0;
    // Build prefix sums for state transitions
    for (int j = 0; j < n; j++) {
      pre[j + 1] = pre[j] + f[0][i - 1][j],
              pre[j + 1] -= ((pre[j + 1] >= Mod) ? Mod : 0);
    }
    pre[n]++, pre[n] -= ((pre[n] >= Mod) ? Mod : 0);
    // Assign values based on prefix sums and cycle indices
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
    // Update the expected number of successful matches
    for (int j = 0; j < n; j++) {
      f[0][i][j] = 1ll * (f[0][i][j] + s) * inv[i] % Mod;
    }
  }
  // Dynamic programming for k counterfeit keys
  for (int d = 1; d <= k; d++) {
    // Initialize the dp table for cases with counterfeit keys
    for (int i = 0; i < n; i++) {
      f[d][0][i] = 0;
    }
    for (int i = 1; i <= l; i++) {
      int s = 1, a = i / n, b = i % n;
      // Accumulate from previous states
      for (int j = 0; j < n; j++) {
        s = s + f[d][i - 1][j], s -= ((s >= Mod) ? Mod : 0);
      }
      s = 1ll * a * s % Mod;
      pre[0] = 0;
      // Build prefix sums for state transitions
      for (int j = 0; j < n; j++) {
        pre[j + 1] = pre[j] + f[d][i - 1][j],
                pre[j + 1] -= ((pre[j + 1] >= Mod) ? Mod : 0);
      }
      pre[n]++, pre[n] -= ((pre[n] >= Mod) ? Mod : 0);
      // Assign values to intermediate array p based on prefix sums
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
      // Update intermediate array p with new contributions and modular inverse operations
      for (int j = 0; j < n; j++) {
        p[j] = (p[j] + s + 1ll * d * f[d - 1][i][(j + n - i % n) % n]) % Mod *
               inv[i + d] % Mod;
      }
      // Calculate s for the second loop
      s = 1, a = (i + d) / n, b = (i + d) % n;
      for (int j = 0; j < n; j++) {
        s = s + f[d][i - 1][j], s -= ((s >= Mod) ? Mod : 0);
      }
      s = 1ll * a * s % Mod;
      pre[0] = 0;
      // Build prefix sums again for second loop
      for (int j = 0; j < n; j++) {
        pre[j + 1] = pre[j] + f[d][i - 1][j],
                pre[j + 1] -= ((pre[j + 1] >= Mod) ? Mod : 0);
      }
      pre[n]++, pre[n] -= ((pre[n] >= Mod) ? Mod : 0);
      // Assign values to intermediate array q based on prefix sums
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
      // Update intermediate array q
      for (int j = 0; j < n; j++) {
        q[j] = 1ll * (q[j] + s) * inv[i + d] % Mod;
      }
      // Final update of the main dp table using weighted averages from arrays p and q
      for (int j = 0; j < n; j++) {
        f[d][i][j] = (1ll * (i - 1) * p[j] + 1ll * (i + d - 1) * q[j]) % Mod *
                     inv[(i << 1) + d - 2] % Mod;
      }
    }
  }
  // Output the final expected results for all people
  for (int i = 0; i < n; i++) {
    printf("%d ", f[k][l][i]);
  }
  printf("\n");
  return;
}
void start() {
  inv[1] = 1;
  // Precompute modular inverse for numbers from 2 to 19999
  for (int i = 2; i < 20000; i++) {
    inv[i] = Mod - 1ll * Mod / i * inv[Mod % i] % Mod;
  }
  return;
}
void calculate() { return; }
void solve() {
  start();
  int T = read();
  // Read number of test cases
  while (T--) {
    init(), calculate();
  }
  return;
}
int main() {
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/