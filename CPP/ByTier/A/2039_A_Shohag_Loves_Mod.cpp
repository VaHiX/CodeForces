// Problem: CF 2039 A - Shohag Loves Mod
// https://codeforces.com/contest/2039/problem/A

/*
 * Problem: Shohag Loves Mod
 * 
 * Purpose: 
 *   Generate an increasing sequence of integers from 1 to 100 such that for any two elements
 *   a_i and a_j at positions i and j (i < j), the remainders a_i % i and a_j % j are different.
 * 
 * Algorithm/Techniques:
 *   The approach is to use the sequence where a_i = 2*i - 1 for all i from 1 to n.
 *   This ensures that a_i % i = (2*i - 1) % i = (2*i % i) - (1 % i) = 0 - 1 = -1 ≡ (i - 1) (mod i).
 *   Thus, for i != j, we have (2*i - 1) % i != (2*j - 1) % j because their values modulo i and j are distinct.
 *   The key idea is to choose a_i such that a_i % i is unique across all indices.
 * 
 * Time Complexity: O(n) per test case, where n is the input number.
 * Space Complexity: O(1) — only constant extra space is used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 1; p <= n; p++) {
      // For each position p, assign value 2*p - 1 to ensure unique mod values
      printf("%ld ", 2 * p - 1);
    }
    puts(""); // Print newline after each sequence
  }
}


// https://github.com/VaHiX/CodeForces/