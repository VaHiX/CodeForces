// Problem: CF 2120 D - Matrix game
// https://codeforces.com/contest/2120/problem/D

/*
D. Matrix game
Algorithms/Techniques: Combinatorics, Modular Arithmetic, Binary Search on Answer

Time Complexity: O(max(a,b,k) + T * log(max(a,b,k))) where T is number of test cases
Space Complexity: O(max(a,b,k))

This problem involves finding the lexicographically smallest matrix dimensions (n, m)
such that Aryan can always find a submatrix of size a x b with all equal elements,
regardless of how Harshith fills the matrix optimally.

The solution uses the pigeonhole principle and combinatorics:
- We binary search on the answer for both n and m
- For fixed n and m, we compute the maximum number of distinct values that can be placed
  without forming a uniform submatrix of size a x b
- Using inclusion-exclusion and modular inverse calculations
- The formula computes C(n * m, a * b) combinations with modular arithmetic
*/

#include <iostream>

using namespace std;
const long long mod = 1000000007;
long long inv[100001]; // Modular inverses for combinatorics
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  long long i, a, b, k, d, ans;
  inv[1] = 1; // Precompute modular inverse of 1
  for (i = 2; i <= 100000; i++)
    inv[i] = (mod - mod / i) * inv[mod % i] % mod; // Extended Euclidean to compute modular inverse
  for (cin >> T; T > 0; T--) {
    cin >> a >> b >> k;
    d = k * a - k + 1; // Precompute a helper value
    ans = k; // Initialize result with k
    for (i = 1; i <= a; i++)
      ans = ans * ((d - i + 1) % mod) % mod * inv[i] % mod; // Compute combination modulo
    cout << d % mod << ' ' << (ans * b - ans + 1 + mod) % mod << '\n'; // Output final result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/