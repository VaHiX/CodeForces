// Problem: CF 1909 E - Multiple Lamps
// https://codeforces.com/contest/1909/problem/E

/*
 * Problem: E. Multiple Lamps
 * 
 * Purpose:
 *   This program solves a problem where we have n lamps and n buttons.
 *   Each button toggles all lamps whose index is a multiple of the button's index.
 *   Some buttons have dependencies: if you press button u, you must also press button v.
 *   Goal: Find a set of buttons to press such that at most floor(n/5) lamps are on,
 *         or return -1 if impossible.
 *
 * Algorithm:
 *   - Precompute valid button combinations for small n (up to 19) using bitmask DP and
 *     dependency constraints.
 *   - For large n, directly press all buttons (which will cause at most n lamps to be on,
 *     and n >= 5 ensures floor(n/5) >= 1).
 *   - For small n, check all valid combinations using precomputed masks.
 *   - Dependency constraints are enforced by ensuring that for each pair (u, v),
 *     if u is pressed, then v must also be pressed.
 *
 * Time Complexity:
 *   - Precomputation: O(2^19 * 19) = O(19 * 2^19) = O(1e6)
 *   - Per test case: O(2^n * m) in worst case for checking validity, but precomputed
 *     e[n] allows efficient validation.
 *
 * Space Complexity:
 *   - O(2^19) for precomputed masks and O(n) for input storage.
 */

#include <algorithm>
#include <cstdio>
#include <iostream>

#define FOR()                                                                  \
  int le = e[u].size();                                                        \
  for (int i = 0; i < le; i++)
#define QWQ cout << "QwQ\n";
#define ll long long
#include <vector>

using namespace std;
const int N = 1010010;
const int qwq = 303030;
const int inf = 0x3f3f3f3f;
int T;
int n, m;
vector<int> e[23]; // Precomputed valid masks for different n values
int dui[N];
int wei[N];
int X[N], Y[N];
inline int read() {
  int sum = 0, ff = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-')
      ff = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    sum = sum * 10 + c - '0';
    c = getchar();
  }
  return sum * ff;
}
int zhuan(int x, int zong) {
  int res = 0;
  for (int i = 1; i <= zong; i++) {
    if (x & (1 << i - 1)) {
      res |= (1 << i - 1);
      for (int j = 2; j * i <= zong; j++) {
        x ^= (1 << j * i - 1);
      }
    }
  }
  return res;
}
void qiu() {
  int da = (1 << 19) - 1;
  for (int i = 1; i <= da; i++)
    wei[i] = wei[i - (i & -i)] + 1;
  for (int i = 5; i <= 19; i++) {
    int deng = i / 5; // Target number of lamps to be on (floor(i/5))
    int dada = (1 << i) - 1; // All possible states for i lamps
    for (int j = 1; j <= dada; j++) {
      if (wei[j] > deng) // If number of lamps on exceeds threshold, skip
        continue;
      e[i].push_back(zhuan(j, i)); // Store valid state
    }
  }
}
int main() {
  qiu();
  T = read();
  while (T--) {
    n = read();
    m = read();
    for (int i = 1; i <= m; i++) {
      X[i] = read();
      Y[i] = read();
    }
    if (n < 5) {
      cout << "-1\n";
      continue;
    }
    if (n > 19) { // For large n, simply press all buttons
      cout << n << endl;
      for (int i = 1; i <= n; i++)
        cout << i << " ";
      cout << endl;
      continue;
    }
    int ans = -1;
    for (int v : e[n]) { // Check all valid combinations for current n
      bool xing = 1;
      for (int i = 1; i <= m; i++) {
        // If button X[i] is pressed but Y[i] is not, this combination is invalid
        if ((v & (1 << X[i] - 1)) && !(v & (1 << Y[i] - 1))) {
          xing = 0;
          break;
        }
      }
      if (xing) {
        ans = v;
        break;
      }
    }
    if (ans == -1) {
      cout << "-1\n";
      continue;
    } else
      cout << wei[ans] << "\n"; // Output number of pressed buttons
    for (int i = 1; i <= n; i++) {
      if (ans & (1 << i - 1))
        cout << i << " "; // Output pressed buttons
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/