// Problem: CF 1618 C - Paint the Array
// https://codeforces.com/contest/1618/problem/C

/*
C. Paint the Array
Purpose: Given an array of positive integers, find a positive integer d such that when elements are painted red if divisible by d and blue otherwise, no two adjacent elements have the same color.
Algorithms/Techniques: 
  - Greedy approach using GCD to determine potential divisors.
  - Analyze parity groups (even indices vs odd indices) to isolate candidate values.
Time Complexity: O(n * log(max(a[i]))) per test case due to GCD operations.
Space Complexity: O(n) for storing the input array.
*/
#include <cstdio>
#include <vector>
typedef long long ll;

// Euclidean algorithm for computing greatest common divisor
ll gcd(ll a, ll b) { 
    return (b == 0) ? a : gcd(b, a % b); 
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    
    // Compute GCD of elements at even indices
    ll x(0), y(0);
    for (ll p = 0; p < n; p++) {
      if (p % 2 == 0) {
        x = gcd(x, a[p]);  // GCD of elements at even positions
      } else if (p % 2 == 1) {
        y = gcd(y, a[p]);  // GCD of elements at odd positions
      }
    }
    
    bool gx(true), gy(true);
    for (ll p = 0; p < n; p++) {
      // Check if any even-indexed element is divisible by y (odd-group GCD)
      if (p % 2 == 0 && a[p] % y == 0) {
        gy = false;  // Cannot use y as divisor since it would color some even indices blue
      } else if (p % 2 == 1 && a[p] % x == 0) {
        gx = false;  // Cannot use x as divisor since it would color some odd indices blue
      }
    }
    
    // If gx is true, x is a valid choice to paint even positions red and odd blue,
    // so we return x as our answer.
    if (gx) {
      printf("%lld\n", x);
    } else if (gy) {
      // Similar logic applies for y.
      printf("%lld\n", y);
    } else {
      // Neither x nor y works, meaning no valid d exists.
      puts("0");
    }
  }
}


// https://github.com/VaHiX/codeForces/