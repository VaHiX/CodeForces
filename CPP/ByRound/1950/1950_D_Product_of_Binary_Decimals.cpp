// Problem: CF 1950 D - Product of Binary Decimals
// https://codeforces.com/contest/1950/problem/D

/*
Problem: D. Product of Binary Decimals

Description:
Given a number n, determine whether it can be represented as a product of binary decimals (numbers whose digits are only 0 or 1).
This problem uses a sieve-like approach to precompute which numbers can be formed as products of binary decimals.

Algorithms/Techniques:
- Preprocessing using a boolean vector to mark numbers that are products of binary decimals.
- Sieve-style iteration over possible factors to update composite results.
- Binary decimal check using digit-by-digit verification (mod 10).

Time Complexity: O(n log n) where n is up to 1e5
Space Complexity: O(n) for the vector storage

*/
#include <cstdio>
#include <vector>

// Check if a number is a binary decimal (all digits are 0 or 1)
bool bindec(long x) {
  while (x) {
    if (x % 10 > 1) {  // If any digit is greater than 1, not binary decimal
      return false;
    }
    x /= 10;  // Move to next digit
  }
  return true;
}

int main() {
  std::vector<bool> v(1e5 + 7, false);  // Vector to store whether each number is a product of binary decimals
  v[1] = true;  // Base case: 1 is trivially a product of binary decimals

  // Mark all binary decimals as valid (initial sieve)
  for (long p = 1; p < v.size(); p++) {
    v[p] = bindec(p);  // Set true if p is a binary decimal
  }

  // Sieve process: mark products of existing binary decimals
  for (long p = 1; p < v.size(); p++) {
    if (!v[p]) {  // Skip if not a binary decimal
      continue;
    }
    for (long q = 1; q <= p && q * p < v.size(); q++) {
      if (v[q]) {  // If q is also a valid product of binary decimals
        v[p * q] = true;  // Mark p*q as valid
      }
    }
  }

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(v[n] ? "YES" : "NO");  // Output result for each test case
  }
}


// https://github.com/VaHiX/codeForces/