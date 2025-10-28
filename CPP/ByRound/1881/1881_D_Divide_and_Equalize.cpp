// Problem: CF 1881 D - Divide and Equalize
// https://codeforces.com/contest/1881/problem/D

/*
D. Divide and Equalize

Algorithm:
This problem is about checking whether it's possible to make all elements of an array equal by performing operations where we can transfer a divisor from one element to another.

Key insight:
- Each operation transfers a factor (divisor) from one number to another.
- The total prime factorization must be equally distributable among all n elements for the answer to be "YES".
- For each prime factor p, if its total count across all numbers is not divisible by n, then it's impossible to distribute evenly.

Time Complexity: O(n * sqrt(max(a_i))) per test case
Space Complexity: O(k) where k is the number of distinct primes up to max(a_i)

Techniques:
- Prime factorization using trial division
- Map to count occurrences of each prime factor
- Check divisibility of counts by n
*/

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Map to store prime factors and their counts
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // Factorize x and count prime factors
      for (long p = 2; p * p <= x; p++) {
        while (x % p == 0) {
          ++m[p]; // Increment count of prime factor p
          x /= p;
        }
      }
      if (x > 1) {
        ++m[x]; // If x is still greater than 1, then it's a prime factor
      }
    }
    bool res(true); // Flag to determine if all counts are divisible by n
    for (std::map<long, long>::iterator it = m.begin(); res && it != m.end();
         it++) {
      if (it->second % n) { // If count of prime factor is not divisible by n
        res = false;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/