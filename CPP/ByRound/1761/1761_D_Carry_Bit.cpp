// Problem: CF 1761 D - Carry Bit
// https://codeforces.com/contest/1761/problem/D

/*
Purpose: 
This code computes the number of ordered pairs (a, b) such that 0 <= a, b < 2^n and f(a, b) = k,
where f(a, b) represents the number of carries when adding a and b in binary.
The solution uses combinatorics and dynamic programming principles to count valid pairs efficiently.

Algorithm:
- The key idea is based on analyzing how many carries occur at each bit position during addition.
- For each bit position, the number of carries can be derived using combinations.
- Precompute factorials and use modular arithmetic for efficient computation.
- Use inclusion-exclusion and combinatorial identities to derive final count.

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <iostream>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int n, k;
ll ans, fc[1000005]; // fc[i] stores i! mod (1e9 + 7)

// Fast exponentiation: computes (a^b) % mod
ll qp(ll a, int b) {
  if (b < 0)
    return 0;
  ll ans = 1;
  for (; b; b >>= 1, a = a * a % mod)  // Right shift b to divide by 2, square a each time
    if (b & 1)  // If b is odd, multiply result by current a
      ans = ans * a % mod;
  return ans;
}

// Compute combination C(n, m) = n! / (m! * (n - m)!)
ll c(int n, int m) {
  return n < m ? 0 : fc[n] * qp(fc[m] * fc[n - m] % mod, mod - 2) % mod;
}

int main() {
  cin >> n >> k, fc[0] = 1;  // Read input and initialize factorial array

  if (!k) {
    // Special case: when k=0, there are no carries
    // For each bit position, both a and b must be 0 or 1, giving 3 combinations for each position:
    // (0,0), (0,1), (1,0) -> 3^N combinations
    return cout << qp(3, n), 0;
  }

  // Precompute factorials up to n
  for (int i = 1; i <= n; i++)
    fc[i] = fc[i - 1] * i % mod;

  // Iterate through possible values to calculate contribution to answer using inclusion-exclusion
  for (int i = 1; i <= n + 1 >> 1; i++) {
    // For each valid i (representing number of carry bits or related values),
    // compute combinations and multiply with power of 3 for remaining bits.
    ans = (ans + 
           c(k - 1, i - 1) * 
           (c(n - k, i - 1) * qp(3, n - 2 * i + 1) % mod + 
            c(n - k, i) * qp(3, n - 2 * i) % mod) 
           % mod) % mod;
  }

  cout << ans;
  return 0;
}


// https://github.com/VaHiX/CodeForces/