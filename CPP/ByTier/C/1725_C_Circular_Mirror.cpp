// Problem: CF 1725 C - Circular Mirror
// https://codeforces.com/contest/1725/problem/C

/*
 * Problem: Circular Mirror
 * 
 * Purpose: Count the number of valid colorings of lamps arranged on a circle such that 
 *          no three lamps forming a right triangle have the same color.
 * 
 * Approach:
 * - The key insight is that three points on a circle form a right triangle if and only 
 *   if one of the arcs between them is exactly half the circumference.
 * - We compute all such "half-circumference" arcs and count how many such pairs exist.
 * - Then, we use inclusion-exclusion or generating functions to calculate valid colorings
 *   based on this count.
 * 
 * Time Complexity: O(N * log(N) + M * min(N, M)) 
 * Space Complexity: O(N + M)
 * 
 * Algorithms/Techniques:
 * - Modular exponentiation (qpow)
 * - Prefix sum for efficient range queries
 * - Two-pointer technique to find pairs with specific arc length properties
 * - Combinatorial math with modular arithmetic
 */

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long LL;
const int N = 3e5 + 5, P = 998244353;
int n, m;
LL dis[N];

// Fast exponentiation with modulo
LL qpow(int a, int b) {
  LL ret = 1;
  while (b) {
    if (b & 1)
      ret = (ret * a) % P;
    a = (1ll * a * a) % P, b >>= 1;
  }
  return ret;
}

// Function to compute the result based on p (number of special pairs)
LL calc(int p) {
  LL ans = 0, tmp = 1ll, C = 1ll;
  for (int i = 0; i <= min(m, p); i++) {
    // Calculate terms of the inclusion-exclusion or generating function
    ans = (ans + tmp * C % P * qpow(1ll * (m - i) * (m - i - 1) % P, p - i) %
                     P * qpow(m - i, n - 2 * p) % P) %
          P;
    // Update combination C(i, p) = C(i-1, p) * (p - i + 1) / i
    C = C * (p - i) % P * qpow(i + 1, P - 2) % P;
    tmp = tmp * (m - i) % P;
  }
  return ans;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> dis[i + 1];
    dis[i + 1] += dis[i];  // Compute prefix sums for arc lengths
  }
  
  int j = 1, p = 0;  // Two pointers to find pairs that make half the circumference
  for (int i = 2; i <= n; i++) {
    while (dis[i] - dis[j] > dis[n + 1] / 2)
      j++;  // Move j forward to adjust window
    if ((dis[i] - dis[j]) * 2 == dis[n + 1])  // If the arc is exactly half the circle
      p++;  // Increment count of valid pairs
  }
  
  cout << calc(p) << endl;  // Compute and output the final answer
  return 0;
}


// https://github.com/VaHiX/CodeForces/