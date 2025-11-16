// Problem: CF 1759 D - Make It Round
// https://codeforces.com/contest/1759/problem/D

#include <iostream>
#include <numeric>

using namespace std;
/*
Code Purpose:
This program finds the roundest possible price after increasing the current price 'n' by a factor 'k' (1 <= k <= m).
A round number has the maximum number of trailing zeros. The algorithm tries to find the maximum number of trailing zeros
by testing powers of 10 and computes the best achievable value under the constraint.

Algorithms/Techniques:
- Greedy approach with GCD (Greatest Common Divisor) to compute the optimal multiplier.
- Testing up to 19 powers of 10 (since 10^19 is sufficient for 10^9 numbers).
- Uses gcd to efficiently compute how many times a power of 10 divides n.

Time Complexity: O(1) per test case (19 iterations, constant operations)
Space Complexity: O(1) - only using a few variables regardless of input size
*/
int main() {
  long long int t, n, m, d, ans, i, k;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (d = 1, i = 0; i < 19; i++, d *= 10) {
      k = d / gcd(d, n); // Compute the minimal k such that (n * k) is divisible by d
      if (k <= m)
        ans = (m / k) * k * n; // Compute the maximum valid value with d trailing zeros
    }
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/CodeForces/