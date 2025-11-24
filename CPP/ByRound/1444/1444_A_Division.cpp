// Problem: CF 1444 A - Division
// https://codeforces.com/contest/1444/problem/A

/*
 * Problem: Find the largest divisor x of p such that x is not divisible by q.
 *
 * Algorithm:
 * - For each pair (p, q), factorize q into its prime factors.
 * - For each prime factor of q, try to divide p by that factor as many times as possible.
 * - Keep track of the maximum resulting value after this process.
 * - The result is the maximum value among all such divisions.
 *
 * Time Complexity: O(sqrt(q) + log(p)) per test case
 * Space Complexity: O(log(q)) for storing prime factors
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;
int64_t t, A, B, a, b, x, i;
int main() {
  cin >> t;
  while (t--) {
    cin >> A >> B;                    // Read p and q
    set<int64_t> p;                   // Store unique prime factors of q
    b = B;                            // Copy q to b for factorization
    for (i = 2; i * i <= b; ++i) {    // Factorize q into primes
      while (b % i == 0)
        b /= i, p.insert(i);          // Divide out all powers of i and insert i into set
    }
    if (b > 1)
      p.insert(b);                    // If remaining b > 1, it's a prime factor
    
    x = 1;                            // Start with x = 1 (minimum valid divisor)
    for (auto i : p) {                // For each unique prime factor of q
      a = A;                          // Reset a to original p value
      while (a % B == 0)              // While a is divisible by q (which means it includes a factor of q)
        a /= i;                       // Remove one copy of this prime factor from a
      x = max(x, a);                  // Update maximum
    }
    cout << x << "\n";                // Print the result for this test case
  }
}


// https://github.com/VaHiX/codeForces/