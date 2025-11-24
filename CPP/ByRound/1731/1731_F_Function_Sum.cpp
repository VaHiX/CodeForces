// Problem: CF 1731 F - Function Sum
// https://codeforces.com/contest/1731/problem/F

/*
 * Purpose: Calculate the sum of f(a) over all arrays a of size n with elements in [1, k]
 * where f(a) is the sum of all elements at "good" positions.
 * A position i is good if lsl(i) < grr(i), where lsl(i) is the count of elements before i that are smaller,
 * and grr(i) is the count of elements after i that are greater.
 * 
 * Techniques:
 * - Dynamic Programming with precomputed values.
 * - Modular arithmetic for handling large numbers.
 * - Mathematical simplification using inverse modulo.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const long long mod = 998244353;
long long func(long long n, long long k) {
  if (n == 1)
    return 0;
  vector<long long> a(n + 1);
  a[1] = 1;
  long long s = 1;
  for (size_t i = 2; i < static_cast<size_t>(n); i++) {
    s = s * k % mod;  // Compute k^(i-1) mod mod
    a[i] = (a[i - 1] + s * i % mod) % mod;  // Update DP array with cumulative sum
  }
  return a[static_cast<size_t>(n - 1)] *
         ((k + 1) * k % mod * (k - 1) % mod * 166374059 % mod) % mod;
}
int main() {
  long long n, k;
  cin >> n >> k;
  cout << func(n, k) << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/