// Problem: CF 1776 N - Count Permutations
// https://codeforces.com/contest/1776/problem/N

/*
N. Count Permutations
Problem Description:
Given a string s of length n-1 consisting of '<' and '>' characters,
count the number of permutations of 1..n such that:
- If s[i] == '<', then p[i] < p[i+1]
- If s[i] == '>', then p[i] > p[i+1]

Algorithms/Techniques:
Dynamic Programming with Memoization, Optimized with Block-based Updates.
The solution uses a state transition approach where each position's DP values are stored
in blocks of size B=300 to optimize space and time.

Time Complexity: O(n * sqrt(n)) where n is the length of string s.
Space Complexity: O(sqrt(n) * B), where B = 300 is the block size.
*/

#include <cstdio>
#define log __builtin_log2l
constexpr int N = 100010, B = 300;
int T, n, Ch, i, j, t, px, py, x[N], y[N], down[N], right[N];
long double f[B], lf[B], LOG, Ma;
char s[N];

template <typename T> inline void r(T &x) {
  while ((Ch = getchar()) < 48)
    ;
  x = Ch & 15;
  while ((Ch = getchar()) > 47)
    x = (x << 1) + (x << 3) + (Ch & 15);
}
inline void r(char &x) {
  while ((x = getchar()) < 33)
    ;
}

// Returns the hook length for a cell at (i, j)
inline int hook(const int &i, const int &j) {
  return j - down[i] + right[j] - i + 1;
}

int main() {
  r(n);
  LOG = 0;
  // Initialize starting point
  down[1] = x[1] = y[1] = px = py = 1;

  // Parse the string to set up grid structure
  for (i = 2; i <= n; i++) {
    r(s[i]);
    if (s[i] == '<')
      down[++px] = py; // Move downward (y-coordinate unchanged)
    else
      right[py++] = px; // Move right (x-coordinate unchanged)
    x[i] = px;
    y[i] = py;
  }
  right[py] = px;

  // Base case for f[0] initialization with hook at (1,1)
  f[0] = 1. / hook(1, 1);
  t = 1; // Current number of elements in f

  // DP transition loop
  for (i = 2; i <= n; i++) {
    __builtin_memcpy(lf, f, t * sizeof *f); // Save previous state
    if (s[i] == '<') { // If moving left (decreasing)
      // Update first element and others with left transition
      f[0] = lf[0] * i / hook(x[i], y[i]);
      for (j = 1; j + 1 < B && x[i] > j && y[i] + j <= py; j++)
        f[j] = (lf[j - 1] + lf[j]) * i / hook(x[i] - j, y[i] + j);
    } else { // If moving right (increasing)
      // Update all elements with right transition
      for (j = 0; j + 1 < B && x[i] > j && y[i] + j <= py; j++)
        f[j] = (lf[j] + lf[j + 1]) * i / hook(x[i] - j, y[i] + j);
      if (x[i] > j && y[i] + j <= py) {
        f[B - 1] = lf[B - 1] / hook(x[i] - j, y[i] + j);
        j++;
      }
    }
    t = j; // Update the current size of dp array

    // Normalize every 1024 steps to prevent overflow
    if ((i & 1023) == 0) {
      Ma = 0;
      for (j--; ~j; j--)
        if (Ma < f[j])
          Ma = f[j];
      LOG += log(Ma);
      for (j = 0; j < t; j++)
        f[j] /= Ma;
    }
  }

  printf("%.10Lf\n", log(f[0]) + LOG); // Final result computed as log base 2
  return 0;
}


// https://github.com/VaHiX/codeForces/