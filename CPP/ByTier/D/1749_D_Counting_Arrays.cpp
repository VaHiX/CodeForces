// Problem: CF 1749 D - Counting Arrays
// https://codeforces.com/contest/1749/problem/D

/*
Algorithm: Mathematical inclusion-exclusion principle with precomputation
Time Complexity: O(n log n) due to GCD computations and loop over n elements
Space Complexity: O(1) as we only use a few variables

This code computes the number of ambiguous arrays of lengths from 1 to n,
where each element is in range [1, m]. An ambiguous array has at least two
different removal sequences. The solution uses inclusion-exclusion principle
to count valid arrays by subtracting non-ambiguous ones from total.
*/
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int P = 998244353;
int main() {
  ll n, m, ans = 0, mul = 1, nm = 1, tmp = 1;
  cin >> n >> m;
  for (ll i = 1; i <= n; i++) {
    // If mul <= m and gcd(mul, i) == 1, update mul to include i
    if (mul <= m && __gcd(mul, i) == 1)
      mul *= i;
    // Update nm = m^i mod P (total arrays of length i)
    nm = m % P * nm % P;
    // Update tmp = (m/mul)^i mod P (non-ambiguous arrays)
    tmp = (m / mul) % P * tmp % P;
    // Add contribution to ans: total - non-ambiguous = ambiguous
    ans = (ans + nm - tmp + P) % P;
  }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/