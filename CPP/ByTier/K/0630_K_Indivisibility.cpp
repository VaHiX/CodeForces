// Problem: CF 630 K - Indivisibility
// https://codeforces.com/contest/630/problem/K

/*
 * Code Purpose:
 * This program calculates how many integers from 1 to n are not divisible 
 * by any number from 2 to 10. This is equivalent to counting integers that 
 * are coprime with all primes 2, 3, 5, and 7 (since any composite number 
 * in the range 2-10 is a multiple of one of these primes).
 * 
 * Algorithm:
 * The solution uses the inclusion-exclusion principle:
 * - Count numbers divisible by each prime (2, 3, 5, 7)
 * - Subtract numbers divisible by pairs (LCM of two primes)
 * - Add back numbers divisible by triplets (LCM of three primes)
 * - Subtract numbers divisible by all four (LCM of all primes)
 * 
 * Time Complexity: O(1) - constant time calculation
 * Space Complexity: O(1) - only using a few variables
 */

#include <iostream>
using namespace std;

int main() {
  long long n;
  cin >> n;
  // Apply inclusion-exclusion principle to count numbers not divisible by 2..10
  cout << n - (n / 2 + n / 3 + n / 5 + n / 7 - n / 6 - n / 10 - n / 14 -
               n / 15 - n / 21 - n / 35 + n / 30 + n / 42 + n / 70 + n / 105 -
               n / 210);
  return 0;
}


// https://github.com/VaHiX/CodeForces/