/*
 * Problem URL : https://codeforces.com/contest/736/problem/A
 * Submit Date : 2025-09-04
 */

#include <iostream>
#include <vector>
using namespace std;
int main() {
  long long x;
  cin >> x;
  vector<long long> dp = {1, 2};
  while (dp[dp.size() - 1] + dp[dp.size() - 2] <= x) {
    dp.push_back(dp[dp.size() - 1] + dp[dp.size() - 2]);
  }
  cout << dp.size() - 1 << "\n";
  return 0;
} /*1691661111.4039116*/