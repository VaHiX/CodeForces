// Problem: CF 2082 C - Math Division
// https://codeforces.com/contest/2082/problem/C

/*
C. Math Division
Algorithm: Dynamic Programming with expectation calculation using bit manipulation
Time Complexity: O(n) per test case, where n is the length of binary string
Space Complexity: O(n) for the dp array

This problem involves computing the expected number of operations to reduce a number x to 1,
where each operation is either floor(x/2) or ceil(x/2) with equal probability (1/2).
The solution uses dynamic programming from right to left on the binary representation.
For each bit position, we compute the expected number of steps based on whether the bit is '1' or '0'.
The inverse of 2 modulo 1e9+7 is precomputed for efficiency.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;
const ll inv2 = 5e8 + 4, mod = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  vector<int> dp(n); // dp[i] stores expected operations for suffix starting at i
  string s;
  cin >> s;
  ll ans = 0;
  // Process from right to left
  for (int i = n - 1; i > 0; i--)
    // If current bit is '1', we have a contribution to the expected value
    // Multiply by inverse of 2 (probability) and add to total answer
    ans = (ans + (s[i] == '1')) * inv2 % mod;
  // Add base case: n-1 operations needed to reduce from n-bit number to 1,
  // plus the expected additional operations computed above
  cout << (n - 1 + ans) % mod << '\n';
  return;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/