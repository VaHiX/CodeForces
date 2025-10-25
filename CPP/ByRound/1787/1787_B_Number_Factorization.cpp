// Problem: CF 1787 B - Number Factorization
// https://codeforces.com/contest/1787/problem/B

/*
B. Number Factorization
Algorithms/Techniques: Prime factorization, greedy approach on exponents.
Time Complexity: O(sqrt(n) + d log d), where d is the number of distinct prime factors of n.
Space Complexity: O(d), where d is the number of distinct prime factors of n.

Given an integer n, we need to find the maximum value of sum(a[i] * p[i]) over all valid
representations of n as a product of powers of integers a[i] (each a[i] being a product of distinct primes).
The key insight is to greedily assign higher values to larger exponents by decomposing and recombining.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> div; // pair<exponent, prime>
    for (long p = 2; p * p <= n; p++) {
      if (n % p) {
        continue;
      }
      div.push_back(std::make_pair(0, p));  // Initialize with zero exponent
      while (n % p == 0) {
        ++div.back().first;  // Count how many times prime p divides n
        n /= p;
      }
    }
    if (n > 1) {
      div.push_back(std::make_pair(1, n)); // Add the last prime factor (if > 1)
    }
    
    sort(div.rbegin(), div.rend()); // Sort in descending order of primes
    
    long total(0);
    while (!div.empty()) {
      long cur(1);
      for (long p = 0; p < div.size(); p++) {
        cur *= div[p].second;   // Multiply current product by next prime
        --div[p].first;         // Decrease exponent
      }
      total += cur;  // Add contribution to the result
      
      while (!div.empty() && div.back().first <= 0) {
        div.pop_back();  // Remove primes with zero or negative exponents
      }
    }
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/