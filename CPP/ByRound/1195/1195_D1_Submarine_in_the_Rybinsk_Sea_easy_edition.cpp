// Problem: CF 1195 D1 - Submarine in the Rybinsk Sea (easy edition)
// https://codeforces.com/contest/1195/problem/D1

/*
Problem: D1. Submarine in the Rybinsk Sea (easy edition)
Algorithms/Techniques: Digit DP, Mathematical Computation

Time Complexity: O(N * D) where N is the number of integers and D is the number of digits (fixed at 10)
Space Complexity: O(D) for storing digit sums and counts

This code computes the sum of all f(a_i, a_j) for all pairs (i,j) where f(x,y) is a function that
alternates digits of two numbers from right to left. It uses digit-wise computation for efficiency.
*/

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  const ll MOD = 998244353;
  const int N = 10; // Number of digits to consider (max is 10 for 1e9)
  ll n;
  scanf("%lld", &n);
  std::vector<ll> s(N, 0), t(N, 0); // s[i]: sum of digits at position i, t[i]: count of numbers with i+1 digits
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    ll idx(0);
    while (x > 0) {
      s[idx] += x % 10; // Accumulate digit sum at position idx
      ++idx;
      x /= 10;
    }
    ++t[idx - 1]; // Increment count for numbers with idx digits
  }
  ll ma(1), res(0); // ma tracks 100^i, res accumulates final result
  for (long p = 0; p < N; p++) {
    ll mb(1), rem(n); // mb tracks 100^j, rem tracks remaining elements
    for (long q = 0; q < p; q++) {
      // Add contribution of pairs where i-th digit of left number is from a number with fewer digits
      res += 2 * (mb % MOD) * (t[q] % MOD) * (s[p] % MOD);
      res %= MOD;
      mb *= 100;
      mb %= MOD;
      rem -= t[q];
    }
    // Add contribution of pairs where i-th digit is from same length numbers
    res += (s[p] % MOD) * ((((ma % MOD) * (rem % MOD) % MOD) +
                            10 * ((ma % MOD) * (rem % MOD) % MOD)) %
                           MOD);
    res %= MOD;
    ma *= 100;
    ma %= MOD;
  }
  printf("%lld\n", res % MOD);
  return 0;
}


// https://github.com/VaHiX/codeForces/