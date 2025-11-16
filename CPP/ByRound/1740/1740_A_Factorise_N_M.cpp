// Problem: CF 1740 A - Factorise N+M
// https://codeforces.com/contest/1740/problem/A

/*
 * Purpose: This program finds a prime number m such that n + m is not prime,
 *          given a prime number n. The approach is to always output 7 as m,
 *          because for any prime n > 2, n + 7 is even and > 2, hence not prime.
 *          For n = 2, 2 + 7 = 9 = 3 * 3, which is also not prime.
 *          
 * Algorithm:
 *   - For each test case, read a prime number n.
 *   - Output 7 as the value of m.
 *   - This works because:
 *     - If n is odd (all primes > 2 are odd), then n + 7 is even and > 2 => not prime
 *     - If n = 2 (the only even prime), then n + 7 = 9 = 3 * 3 => not prime
 *   
 * Time Complexity: O(1) per test case (constant time)
 * Space Complexity: O(1) (no extra space used)
 */

#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--)
    puts("7");  // Always output 7 as the prime number m
  return 0;
}


// https://github.com/VaHiX/CodeForces/