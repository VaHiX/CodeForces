// Problem: CF 1514 B - AND 0, Sum Big
// https://codeforces.com/contest/1514/problem/B

/*
B. AND 0, Sum Big
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Baby Badawy's first words were "AND 0 SUM BIG", so he decided to solve the following problem. Given two integers n and k, count the number of arrays of length n such that:
 
 all its elements are integers between 0 and 2^k-1 (inclusive); 
 the bitwise AND of all its elements is 0; 
 the sum of its elements is as large as possible. 
Since the answer can be very large, print its remainder when divided by 10^9+7.

Algorithm: 
- For each bit position, we want to maximize the sum while ensuring that the AND of all elements is 0.
- This means at least one element must have a 0 in each bit position.
- The maximum possible value for the sum is achieved when all but one element are assigned 2^k - 1 (max value) and one is assigned 0.
- So we need to count the number of ways to choose which element is 0, and how many valid arrays there are.

Time Complexity: O(k * t) where t is number of test cases and k is up to 20.
Space Complexity: O(1)

Techniques:
- Modular exponentiation
- Bit manipulation
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll MOD = 1e9 + 7;
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll res(1);
    for (ll p = 0; p < k; p++) {
      res *= n;           // Multiply by n for each bit position
      res %= MOD;         // Apply modulo to prevent overflow
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/