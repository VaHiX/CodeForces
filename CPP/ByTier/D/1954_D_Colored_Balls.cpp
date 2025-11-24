// Problem: CF 1954 D - Colored Balls
// https://codeforces.com/contest/1954/problem/D

/*
Purpose: This code computes the sum of the minimum number of groups needed to distribute balls of selected colors,
where each group contains at most 2 balls and at most 1 ball of each color.
The approach uses dynamic programming to count the number of ways to form subsets of balls and then computes
the contribution of each subset size to the final answer.

Algorithms/Techniques:
- Dynamic Programming (DP) for counting subsets
- Inclusion-exclusion or direct calculation based on subset sizes
- Modular arithmetic for large numbers
- Efficient handling of group formation logic using mathematical formulae

Time Complexity: O(n * S) where S is the sum of all balls.
Space Complexity: O(S) where S is the sum of all balls.

*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
typedef long long ll;
typedef double db;
const int N = 1e5 + 10;
const ll mod = 998244353;
int add(int x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
  return x;
}
int mul(int x, int y) { return x * 1ll * y % mod; }
void deer() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  int s = accumulate(a.begin(), a.end(), 0);
  vector<int> dp(s + 1);
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = s; j >= a[i]; j--)
      dp[j] = add(dp[j], dp[j - a[i]]);
  }
  int ans = 0;
  for (int j = 0; j <= s; j++)
    ans = add(ans, mul((j + 1) / 2, dp[j]));  // For each subset size, calculate contribution as ceil(j/2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < a[i]; j++)
      ans = add(ans, mul(a[i] - (a[i] + j + 1) / 2, dp[j]));  // Adjust for overcounting by subtracting contributions
  }
  cout << ans << "\n";
  return;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  while (t--) {
    deer();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/