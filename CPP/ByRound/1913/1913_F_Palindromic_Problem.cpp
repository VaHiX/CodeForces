// Problem: CF 1913 F - Palindromic Problem
// https://codeforces.com/contest/1913/problem/F

/*
 * Problem: F. Palindromic Problem
 * 
 * Algorithm: Manacher's Algorithm for finding palindromes, followed by a dynamic programming approach
 *            to determine the best character replacement to maximize palindromic substrings.
 * 
 * Time Complexity: O(n) for Manacher's algorithm + O(n^2) for DP = O(n^2) in worst case
 * Space Complexity: O(n) for storing hash values, palindrome lengths, and DP table
 * 
 * Approach:
 * 1. Use Manacher's algorithm to compute the longest palindromic substring centered at each point.
 * 2. For each position, calculate how changing that character affects palindromic counts.
 * 3. Use a DP table to track the benefit of changing a character to each possible letter.
 * 4. Select the lexicographically smallest string with maximum palindromes.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define MAXN 300000
long long dp[MAXN + 5][30];
unsigned long long h1[MAXN + 5], h2[MAXN + 5], b[MAXN + 5];
int base = 131;
string s;
int n;
unsigned long long solve1(int x, int y) {
  return h1[y] - h1[x - 1] * b[y - x + 1];
}
unsigned long long solve2(int x, int y) {
  x = n - x + 1, y = n - y + 1;
  return h2[y] - h2[x - 1] * b[y - x + 1];
}
int d1[MAXN + 5], d2[MAXN + 5];
long long sum[MAXN + 5], sum1[MAXN + 5];
void manacher() {
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
      k++;
    d1[i] = k--;
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
      k++;
    d2[i] = k--;
    if (i + k > r) {
      l = i - k - 1;
      r = i + k;
    }
  }
  for (int i = n; i >= 1; i--) {
    d1[i] = d1[i - 1];
    d2[i] = d2[i - 1];
  }
}
int check(int x, int y) {
  if (x < 1 || y > n)
    return 0;
  int l = 0, r = min(x, n - y + 1);
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (solve1(x - mid + 1, x) == solve2(y + mid - 1, y))
      l = mid + 1;
    else
      r = mid - 1;
  }
  return r;
}
int main() {
  cin >> n >> s;
  b[0] = 1;
  for (int i = 1; i <= n; i++) {
    h1[i] = h1[i - 1] * base + s[i - 1] - 'a' + 1;
    h2[i] = h2[i - 1] * base + s[n - i] - 'a' + 1;
    b[i] = b[i - 1] * base;
  }
  manacher();
  long long ans1 = 0, ans = 0;
  for (int i = 1; i <= n; i++)
    ans1 += d1[i] + d2[i];
  for (int i = 1; i <= n; i++) {
    if (d1[i] > 1) {
      int l = i - d1[i] + 1, r = i + d1[i] - 1;
      sum[l]++, sum[i]--, sum1[i] -= i - l;
      sum[i + 1]--, sum[r + 1]++, sum1[r + 1] += r - i;
      sum1[i + 1] += r - i + 1, sum1[r + 1] += -(r - i + 1);
    }
    if (d2[i] == 0)
      continue;
    int l = i - d2[i], r = i + d2[i] - 1;
    sum[l]++, sum[i]--, sum1[i] -= i - l;
    sum[i]--, sum[r + 1]++, sum1[r + 1] += r - i + 1;
    sum1[i] += r - i + 2, sum1[r + 1] += -(r - i + 2);
  }
  for (int i = 1; i <= n; i++)
    sum[i] = sum[i] + sum[i - 1];
  for (int i = 1; i <= n; i++)
    sum[i] = sum[i] + sum1[i];
  for (int i = 1; i <= n; i++)
    sum[i] = sum[i] + sum[i - 1];
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < 26; j++)
      dp[i][j] = -sum[i];
  for (int i = 1; i <= n; i++) {
    int l = i - d1[i], r = i + d1[i];
    if (l >= 1 && r <= n) {
      int len = check(l - 1, r + 1);
      dp[l][s[r - 1] - 'a'] += len + 1;
      dp[r][s[l - 1] - 'a'] += len + 1;
    }
    l = i - d2[i] - 1, r = i + d2[i];
    if (l >= 1 && r <= n) {
      int len = check(l - 1, r + 1);
      dp[l][s[r - 1] - 'a'] += len + 1;
      dp[r][s[l - 1] - 'a'] += len + 1;
    }
  }
  int x = 0, y = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 25; j >= 0; j--) {
      if (dp[i][j] >= ans)
        ans = dp[i][j];
    }
  }
  int f = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 25; j >= 0; j--) {
      if (dp[i][j] == ans && j < s[i - 1] - 'a') {
        x = i, y = j;
        f = 0;
      }
      if (dp[i][j] == ans)
        x = i, y = j;
    }
    if (f == 0)
      break;
  }
  printf("%lld\n", ans1 + ans);
  if (x)
    s[x - 1] = char(y + 'a');
  cout << s;
}


// https://github.com/VaHiX/CodeForces/