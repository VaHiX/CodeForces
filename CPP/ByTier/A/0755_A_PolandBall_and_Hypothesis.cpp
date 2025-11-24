// Problem: CF 755 A - PolandBall and Hypothesis
// https://codeforces.com/contest/755/problem/A

/*
 * Code Purpose:
 * This program finds a counterexample to PolandBall's hypothesis that there exists a positive integer n such that for all positive integers m, n*m + 1 is a prime number.
 * The approach is to test values of m from 1 to 1000 for the given n and check if n*m + 1 is not prime.
 * 
 * Algorithms/Techniques:
 * - Prime checking using trial division up to sqrt(x)
 * - Brute-force search for m in range [1, 1000]
 * 
 * Time Complexity: O(1000 * sqrt(max_value)) where max_value is approximately n*1000 + 1
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
bool isPrime(long x) {
  // Check if x is a prime number by testing divisibility up to sqrt(x)
  for (long p = 2; p * p <= x; p++) {
    if (x % p == 0) {
      return false; // Found a divisor, so x is not prime
    }
  }
  return true; // No divisors found, x is prime
}

int main() {
  long n;
  scanf("%ld", &n); // Read the input n
  
  // Try values of m from 1 to 1000
  for (long m = 1; m <= 1000; m++) {
    long test = n * m + 1; // Calculate n*m + 1
    if (!isPrime(test)) {
      printf("%ld\n", m); // If not prime, output m as counterexample
      break;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/