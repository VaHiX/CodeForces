// Problem: CF 2066 B - White Magic
// https://codeforces.com/contest/2066/problem/B

/*
B. White Magic
Algorithms/Techniques: Greedy with prefix min and suffix mex tracking using boolean array.
Time Complexity: O(n) amortized per test case, since each element is processed at most twice.
Space Complexity: O(n) for arrays f, c, s.

We call a sequence a1, a2, ..., an magical if for all 1≤i≤n−1 it holds that:
min(a1, ..., ai) ≥ mex(ai+1, ..., an).
The minimum excluded (MEX) of a collection is the smallest non-negative integer not present in the collection.
Given a sequence of n non-negative integers, find the maximum possible length of a magical subsequence.
*/

#include <algorithm>
#include <stdio.h>
using namespace std;

const int p = 1e9 + 7;
int n, f[200002], c[200002]; // f stores filtered input, c precomputes prefix minimums
bool s[200002];              // s tracks which numbers are seen from the right side

void solve() {
  scanf("%d", &n);
  bool t = 0, ok = 1;     // t indicates if we've encountered a zero, ok tracks validity
  int len = 0, tmp = 0;   // len is length of filtered array f, tmp holds current mex candidate

  // Preprocessing: Filter the sequence to remove unnecessary zeros
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    if (x)                  // If x is non-zero, include it in filtered array
      f[++len] = x;
    else if (!t)            // Only add first zero to avoid redundancy
      f[++len] = x, t = 1;
  }

  // Build prefix minimum array c to compute min(a1,...,ai) efficiently
  for (int i = 1; i <= len; i++)
    c[i] = min(c[i - 1], f[i]);

  // Process from right to left to determine which numbers are present in suffix
  for (int i = len; i > 1; i--) {
    if (f[i] <= n)          // Only consider elements within range [0,n]
      s[f[i]] = 1;          // Mark number f[i] as seen
    while (s[tmp])          // Find next mex by counting from zero
      tmp++;
    if (tmp > c[i - 1]) {   // If current mex exceeds prefix min, invalid
      ok = 0;
      break;
    }
  }

  // Output result: original length minus one if invalid (i.e., we can't form a valid subsequence)
  printf("%d\n", len - !ok);

  // Reset s array for next iteration
  for (int i = 1; i <= n; i++)
    if (f[i] <= n)
      s[f[i]] = 0;
}

int main() {
  c[0] = (1 << 30); // Initialize prefix min to large value
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/