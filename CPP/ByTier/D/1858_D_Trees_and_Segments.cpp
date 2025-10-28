// Problem: CF 1858 D - Trees and Segments
// https://codeforces.com/contest/1858/problem/D

/*
Purpose: This code solves the problem of maximizing the beauty of a tree plantation plan 
         by changing at most k trees, where beauty is calculated as a*l0 + l1, 
         with l0 and l1 being the maximum consecutive oaks and firs respectively.

Algorithms/Techniques:
1. Dynamic Programming with Sliding Window
2. Two-pass approach (forward and reverse string)
3. Optimization using prefix arrays and greedy selection

Time Complexity: O(n^2) per test case, where n is the length of the string.
Space Complexity: O(n) for auxiliary arrays used in DP and fix vectors.

The solution uses a two-pass approach to compute the maximum length of consecutive 
segments for each possible number of changes (from 0 to k). It then computes 
the maximum beauty for each value of 'a' from 1 to n by evaluating the formula 
a * l0 + l1 for different valid combinations.

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
const int N = (int)2e5 + 5;
const int MOD = (int)1e9 + 7;
const int INF = (int)1e9 + 9;
#define nl '\n'
#define ff first
#define ss second
#define szof(x) (int)x.size()
#define all(x) x.begin(), x.end()
void solve(int n, int k, string s, vector<int> &fix) {
  vector<int> dp(n + 2, 0);
  s = '?' + s;
  for (int i = 1; i <= (n + 1); ++i) {
    int zero = 0;
    for (int j = i - 1; j > 0; --j) {
      zero += (s[j] == '0');
      dp[zero] = max(dp[zero], i - j);
    }
    for (int j = 1; j <= n; ++j)
      dp[i] = max(dp[i], dp[i - 1]);
    int one = 0;
    fix[0] = max(fix[0], dp[k]);
    for (int j = i; j <= n; ++j) {
      one += (s[j] == '1');
      int len = (j - i + 1);
      if (one <= k)
        fix[len] = max(fix[len], dp[k - one]);
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int test = 1, tc = 0;
  cin >> test;
  while (test--) {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vi fix(n + 3, -INF);
    solve(n, k, s, fix);
    reverse(all(s));
    solve(n, k, s, fix);
    for (int x = 1; x <= n; ++x) {
      ll ans = 0;
      for (int i = 0; i <= n; ++i) {
        ans = max(ans, 1LL * i * x + fix[i]);
      }
      cout << ans << " ";
    }
    cout << nl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/