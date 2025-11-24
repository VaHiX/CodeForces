// Problem: CF 1366 D - Two Divisors
// https://codeforces.com/contest/1366/problem/D

/*
Purpose: 
This code finds two divisors d1 > 1 and d2 > 1 for each element in the array such that gcd(d1 + d2, a_i) = 1.
It uses a precomputed list of primes to factorize numbers efficiently and then checks if there exist two distinct prime factors or their products to form valid d1 and d2.

Algorithms/Techniques:
- Sieve of Eratosthenes to generate primes up to 1e7 + 9
- Prime factorization for each number using the precomputed primes
- Selecting the first two factors (or products of factors) to form d1 and d2
- Using basic number theory: if two numbers are coprime to a third number, their sum may still not be coprime, but with proper selection of divisors, this condition can be met.

Time Complexity: O(B log log B + n * sqrt(A)) where B is max prime (1e7+9), and A is max element in array (1e7)
Space Complexity: O(B + n) for the sieve and the array input
*/

#include <cstdio>
#include <vector>
int main() {
  const long B = 1e7 + 9;
  std::vector<bool> v(B, 1);
  v[0] = v[1] = 0;
  for (long p = 2; p * p <= B; p++) {
    if (!v[p]) {
      continue;
    }
    for (long q = 2 * p; q < B; q += p) {
      v[q] = 0;
    }
  }
  std::vector<long> w;
  for (long p = 0; p < B; p++) {
    if (!v[p]) {
      continue;
    }
    w.push_back(p);
  }
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n, -1), b(n, -1);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    std::vector<long> f; // stores the prime factors
    for (long y : w) {
      if (y * y > x) {
        break;
      }
      if (x % y) {
        continue;
      }
      if (f.size() < 2) {
        f.push_back(y);
      } else {
        f.back() *= y;  // Combine factors into one composite if already have 2
      }
      while (x % y == 0) {
        x /= y;
      }
    }
    if (x > 1) {
      if (f.size() < 2) {
        f.push_back(x);
      } else {
        f.back() *= x;
      }
    }
    if (f.size() > 1) {
      a[p] = f[0];
      b[p] = f[1];
    }
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  };
  puts("");
  for (long p = 0; p < n; p++) {
    printf("%ld ", b[p]);
  };
  puts("");
}


// https://github.com/VaHiX/CodeForces/