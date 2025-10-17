// Problem: CF 1829 D - Gold Rush
// https://codeforces.com/contest/1829/problem/D

/*
D. Gold Rush

Problem Description:
Given an initial pile of `n` gold nuggets, determine whether it's possible to create a pile of exactly `m` nuggets using allowed operations. An operation splits a pile into two piles such that one has twice as many nuggets as the other.

Approach:
- Reduce both `n` and `m` by their GCD to simplify the problem.
- Factor out powers of 3 from `n` (representing how many times we can split to get 2:1 ratios involving 3s)
- Factor out powers of 2 from `m` (representing how many times we can split to get 2:1 ratios involving 2s)
- Check if the resulting reduced values are both 1 and the number of 2 factors in `m` is less than or equal to the number of 3 factors in `n`.

Time Complexity: O(log(min(n, m))) per test case due to GCD computation and factorization.
Space Complexity: O(1) - constant extra space used.

Algorithms/Techniques: 
- Greatest Common Divisor (Euclidean Algorithm)
- Prime Factorization
- Mathematical Reduction

*/

#include <cstdio>
typedef long long ll;

ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    
    ll g = gcd(m, n);  // Compute GCD to reduce the problem
    n /= g;
    m /= g;
    
    long fn(0);  // Count of factor 3 in n
    while (n % 3 == 0) {
      ++fn;
      n /= 3;
    }
    
    long fm(0);  // Count of factor 2 in m
    while (m % 2 == 0) {
      ++fm;
      m /= 2;
    }
    
    // If both are reduced to 1 and fm <= fn, then solution exists
    puts((n == 1 && m == 1 && fm <= fn) ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/