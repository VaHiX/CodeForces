/*
 * Problem URL : https://codeforces.com/problemset/problem/2070/F
 * Submit Date : 2025-08-23
 */

#include <array>
#include <cassert>
#include <iostream>
using namespace std;
int n, m;
int bitmask[5 << 17];
int dp[1 << 20][21];
long long count[1 << 20][21];
int weights[20];
long long result[4 << 17];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    string str;
    cin >> str;
    for (char c : str)
      bitmask[i] |= 1 << c - 'A';
  }
  int oddBitmask = 0, totalSum = 0;
  for (int i = 0; i < n; i++) {
    cin >> weights[i];
    if (weights[i] % 2 == 1)
      oddBitmask |= 1 << i;
    totalSum += weights[i];
  }
  for (int i = 0; i < m; i++)
    dp[bitmask[i]][__builtin_popcount(bitmask[i] & oddBitmask)]++;
  int oddCount = __builtin_popcount(oddBitmask);
  for (int k = 0; k < n; k++)
    for (int i = 0; i < 1 << n; i++)
      if (i >> k & 1) {
        for (int j = 0; j <= oddCount; j++)
          dp[i][j] += dp[i ^ (1 << k)][j];
      }
  for (int i = 0; i < 1 << n; i++) {
    for (int j = 0; j <= oddCount; j++) {
      if (j + j <= oddCount)
        count[i][j + j] += (long long)dp[i][j] * (dp[i][j] - 1) / 2;
      for (int k = j + 1; j + k <= oddCount; k++)
        count[i][j + k] += (long long)dp[i][j] * dp[i][k];
    }
  }
  for (int k = 0; k < n; k++)
    for (int i = 0; i < 1 << n; i++)
      if (i >> k & 1) {
        for (int j = 0; j <= oddCount; j++)
          count[i][j] -= count[i ^ (1 << k)][j];
      }
  for (int i = 0; i < 1 << n; i++) {
    int oddBits = __builtin_popcount(i & oddBitmask);
    int remainingWeight = 0;
    for (int j = 0; j < n; j++)
      if (!(i >> j & 1))
        remainingWeight += weights[j];
    result[remainingWeight] += count[i][oddBits];
  }
  for (int i = 0; i <= totalSum; i++)
    cout << result[i] << (i == totalSum ? "\n" : " ");
}
