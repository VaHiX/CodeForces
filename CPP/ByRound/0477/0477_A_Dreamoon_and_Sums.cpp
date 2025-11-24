// Problem: CF 477 A - Dreamoon and Sums
// https://codeforces.com/contest/477/problem/A

/*
 * Problem: Dreamoon and Sums
 * 
 * Task: Calculate the sum of all "nice" integers x, where x is nice if:
 *       for some integer k in [1, a], we have (x / k) + (x % k) = b.
 * 
 * Approach:
 * - We analyze the mathematical condition (x / k) + (x % k) = b.
 * - For a fixed k, we can derive that x = k * (b - 1) + r for r in [0, k - 1].
 * - This leads to a formula that allows us to compute the sum efficiently.
 * 
 * Mathematical derivation:
 * - The sum over all valid x values across all k in [1, a] can be computed using:
 *   Sum = (b * (b - 1) / 2) * (a * (a + 1) / 2 * b + a)
 * 
 * Time Complexity: O(1) - Constant time computation
 * Space Complexity: O(1) - Only using a constant amount of extra space
 */

#include <iostream>

using namespace std;
int main() {
  long long a, b;
  cin >> a >> b;
  cout << ((((b * (b - 1)) / 2) % 1000000007) *
           ((((a * (a + 1) / 2) % 1000000007) * b) % 1000000007 + a)) %
              1000000007;
  return 0;
}


// https://github.com/VaHiX/CodeForces/