// Problem: CF 2104 F - Numbers and Strings
// https://codeforces.com/contest/2104/problem/F

/*
F. Numbers and Strings
time limit per test3 seconds
memory limit per test512 megabytes

Task:
For each integer x from 1 to n, we form the string S(x) by concatenating x and (x+1), 
sorting the digits in non-decreasing order. Count how many distinct strings are formed.

Algorithm/Techniques:
- Precompute all valid strings S(x) for x up to a certain limit.
- Use DFS with pruning to avoid generating invalid numbers that contain digits other than 0 and 9.
- Sort all generated strings to allow efficient binary search during queries.

Time Complexity: O(10^9) in precomputation, but practically faster due to pruning.
Space Complexity: O(10^6) for storing precomputed strings.

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;

int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

const int N = 1000005;
int T, n, a[N], tot, now, las = 1;

// Check if the number contains only 0s and 9s, i.e., it's a valid string in our generation
bool check(int x) {
  int cnt0 = 0, cnt9 = 0;
  while (x) {
    int xx = x % 10;
    x /= 10;
    if (xx != 0 && xx != 9)
      return 1; // If any digit is not 0 or 9, invalid
    if (!xx)
      cnt0++;
    else
      cnt9++;
  }
  return cnt0 != cnt9; // Return true if count of 0s != count of 9s (i.e., not a valid all-zero/all-nine case)
}

// DFS to generate all valid numbers in S(x) form
void dfs(int pos) {
  int xxx = 0;
  if (!now)
    xxx = -1; // Special handling for zero
  if (check(now))
    xxx = 8; // Limit digits to avoid invalid cases
  for (int i = 0; i <= xxx; i++) {
    int tmp = now * 10 + i;
    if (tmp)
      a[++tot] = tmp; // Add valid number to list
    if (pos + 1 <= 9) {
      tmp = tmp * 10 + 9;
      a[++tot] = tmp; // Append 9 and add to list
    }
  }
  if (pos == 9)
    return;
  int tmp1 = now, tmp2 = las;
  for (int i = las; i <= 9; i++) {
    now = tmp1 * 10 + i;
    las = i;
    dfs(pos + 1);
    if (pos == 1) {
      for (int j = 2; j <= 8; j++) {
        now *= 10;
        dfs(j + 1);
      }
    }
  }
  now = tmp1, las = tmp2; // Restore state
}

// Initialize all precomputed valid numbers
void init() {
  for (int i = 1; i <= 9; i++) {
    now = now * 10 + 9;
    a[++tot] = now;
  }
  for (int i = 1; i <= 8; i++) {
    now = i;
    a[++tot] = now;
    for (int j = 2; j <= 9; j++) {
      now = now * 10 + 9;
      a[++tot] = now;
    }
  }
  now = 0;
  dfs(1);
  sort(a + 1, a + tot + 1); // Sort precomputed values for binary search
}

void solve() {
  n = read();
  int ans = upper_bound(a + 1, a + tot + 1, n) - a - 1; // Binary search to count valid values <= n
  printf("%d\n", ans);
}

void clear() {}

int main() {
  init();
  T = read();
  for (int tt = 1; tt <= T; tt++) {
    solve();
    clear();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/