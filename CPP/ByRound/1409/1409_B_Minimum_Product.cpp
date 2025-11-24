// Problem: CF 1409 B - Minimum Product
// https://codeforces.com/contest/1409/problem/B

/*
B. Minimum Product
Algorithms/Techniques: Greedy approach with two scenarios
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem asks to minimize the product a * b by decrementing a or b at most n times,
with constraints that a >= x and b >= y. The strategy is to try both possible orders:
1. First reduce a as much as possible, then b
2. First reduce b as much as possible, then a
Then take the minimum of the two resulting products.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll A, B, X, Y, N;
    scanf("%lld %lld %lld %lld %lld", &A, &B, &X, &Y, &N);
    
    ll n(N), a(A), b(B);
    
    // Scenario 1: Reduce 'a' first, then 'b'
    ll u = a - X;           // Max possible reduction for 'a'
    u = (u < n) ? u : n;    // Take min of possible and available steps
    a -= u;                 // Apply reduction to 'a'
    n -= u;                 // Decrease remaining steps
    
    u = b - Y;              // Max possible reduction for 'b'
    u = (u < n) ? u : n;    // Take min of possible and available steps
    b -= u;                 // Apply reduction to 'b'
    
    ll resA = a * b;        // Result of first scenario
    
    // Reset values for second scenario
    n = N;
    a = A;
    b = B;
    
    // Scenario 2: Reduce 'b' first, then 'a'
    u = b - Y;              // Max possible reduction for 'b'
    u = (u < n) ? u : n;    // Take min of possible and available steps
    b -= u;                 // Apply reduction to 'b'
    n -= u;                 // Decrease remaining steps
    
    u = a - X;              // Max possible reduction for 'a'
    u = (u < n) ? u : n;    // Take min of possible and available steps
    a -= u;                 // Apply reduction to 'a'
    
    ll resB = a * b;        // Result of second scenario
    
    ll res = (resA < resB) ? resA : resB;  // Take minimum of both scenarios
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/