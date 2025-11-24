// Problem: CF 1855 B - Longest Divisors Interval
// https://codeforces.com/contest/1855/problem/B

/*
B. Longest Divisors Interval
Algorithms/Techniques: Simple factorization and iteration up to sqrt(n)

Time Complexity: O(sqrt(n)) per test case
Space Complexity: O(1)

Given a positive integer n, find the maximum size of an interval [l,r] of positive integers such that,
for every i in the interval (i.e., l <= i <= r), n is a multiple of i.
The solution finds the longest consecutive sequence starting from 1 where all numbers divide n.
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cnt(1);  // Start counting from 1, as 1 always divides any number
    for (ll p = 2; n % p == 0 && p <= n; p++) {  // Check if p divides n and increment cnt
      ++cnt;
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/