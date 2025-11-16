// Problem: CF 1938 F - Forming Groups
// https://codeforces.com/contest/1938/problem/F

/*
 * Problem: Forming Groups
 * 
 * Algorithms/Techniques:
 * - Brute-force over all possible divisors k of n (k > 1)
 * - For each k, simulate all possible positions for student 1 (captain)
 * - Maintain group sums and update them efficiently as student 1 moves
 * - Use GCD to reduce the final ratio to its simplest form
 * 
 * Time Complexity: O(n * d(n)) where d(n) is the number of divisors of n.
 * Space Complexity: O(n) for storing arrays a and g.
 */

#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
using ll = long long;
const int N = 1000005;
int n;
int a[N];
int g[N];

// Fast input function to read integers from stdin
void read(int &rel) {
  bool sign = false;
  char ch;
  while (true) {
    ch = getchar();
    if (ch >= '0' && ch <= '9')
      break;
    if (ch == '-')
      sign = true;
  }
  rel = ch ^ 48;  // Convert char to int
  while (true) {
    ch = getchar();
    if (ch >= '0' && ch <= '9')
      rel = rel * 10 + (ch ^ 48);  // Accumulate digit
    else
      break;
  }
  rel = sign ? -rel : rel;  // Apply sign if needed
}

// Compute greatest common divisor using Euclidean algorithm
int GCD(int a, int b) { return b == 0 ? a : GCD(b, a % b); }

void solve() {
  read(n);
  for (int i = 0; i < n; i++) {
    read(a[i]);
  }

  // Initialize answer with invalid values
  int ans_p = -1, ans_q = -1;
  int m = n;

  // Try all possible values of k that are divisors of n and greater than 1
  for (int k = 2; k <= m; k++) {
    if (m % k)  // Skip k if not a divisor
      continue;

    // Remove all factors of k from m to efficiently get other divisors
    while (m % k == 0)
      m /= k;

    // Reset group sum array
    memset(g, 0, sizeof(g[0]) * k);

    // Initialize group sums for current k
    for (int i = 0; i < n; i++) {
      g[i % k] += a[i];
    }

    // Track maximum and minimum group sums
    int p = -1, q = -1;
    int idx_p, idx_q;

    // Simulate moving captain to different positions
    for (int i = 0; i < n; i++) {
      if (i) {
        // Update sums when captain moves
        int t1 = (i - 1) % k, t2 = i % k;
        g[t1] += a[i] - a[0];  // Adjust sum based on movement
        g[t2] += a[0] - a[i];

        // Fast recalculate max and min if necessary
        if (idx_p == t1 || idx_p == t2) {
          if (g[t1] >= p)
            p = g[t1], idx_p = t1;
          else if (g[t2] >= p)
            p = g[t2], idx_p = t2;
          else
            p = -1;
        } else if (g[t1] > p)
          p = g[t1], idx_p = t1;
        else if (g[t2] > p)
          p = g[t2], idx_p = t2;

        if (idx_q == t1 || idx_q == t2) {
          if (g[t1] <= q)
            q = g[t1], idx_q = t1;
          else if (g[t2] <= q)
            q = g[t2], idx_q = t2;
          else
            q = -1;
        } else if (g[t1] < q)
          q = g[t1], idx_q = t1;
        else if (g[t2] < q)
          q = g[t2], idx_q = t2;
      }

      // Recalculate max if needed
      if (p == -1) {
        int cur = i % k;
        for (int j = 0; j < k; j++) {
          if (p == -1 || g[j] > p ||
              (g[j] == p && (idx_p - cur + n) % n < (j - cur + n) % n)) {
            p = g[j];
            idx_p = j;
          }
        }
      }

      // Recalculate min if needed
      if (q == -1) {
        int cur = i % k;
        for (int j = 0; j < k; j++) {
          if (q == -1 || g[j] < q ||
              (g[j] == q && (idx_q - cur + n) % n < (j - cur + n) % n)) {
            q = g[j];
            idx_q = j;
          }
        }
      }

      // Update global best ratio
      if (ans_p == -1 || (ll)p * ans_q < (ll)ans_p * q) {
        ans_p = p;
        ans_q = q;
      }
    }
  }

  // Reduce the ratio to its simplest form
  int gcd = GCD(ans_p, ans_q);
  ans_p /= gcd;
  ans_q /= gcd;

  printf("%d %d\n", ans_p, ans_q);
}

int main() {
  int yt = 1;
  read(yt);
  while (yt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/