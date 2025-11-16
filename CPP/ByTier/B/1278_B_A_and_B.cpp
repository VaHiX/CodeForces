// Problem: CF 1278 B - A and B
// https://codeforces.com/contest/1278/problem/B

/*
B. A and B
Algorithm: 
This problem requires finding the minimum number of operations to make two integers `a` and `b` equal, where each operation adds an increasing value (1, 2, 3, ...) to either `a` or `b`. 

Key insight:
The difference between `a` and `b` must be covered by a sequence of consecutive integers (1, 2, 3, ..., x). If the total sum of these operations is S = x*(x+1)/2, then we need to check whether it's possible to make the difference equal using these operations.

The minimum x can be found using binary search or iteration over increasing values of x until:
1. The total sum of 1 to x is at least the absolute difference.
2. The parity (even/odd) of the difference matches the parity of the sum.

Time Complexity: O(sqrt(D)) where D is the absolute difference between a and b, in the worst case we iterate up to sqrt(2*D).
Space Complexity: O(1) - only using a few variables for computation.

*/

#include <cstdio>
typedef long long ll;

// Function to check if a given difference d can be achieved with x operations
bool check(ll d, ll x) {
  ll s = x * (x + 1) / 2; // Sum of first x natural numbers
  if (d > s) {
    return false; // Difference is greater than possible sum
  }
  return (d % 2 == s % 2); // Parity condition: difference and sum must have same parity
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    ll d = a - b;
    if (d < 0) {
      d = -d; // Take absolute difference
    }
    if (d <= 0) {
      puts("0"); // Already equal
      continue;
    }
    ll x(0);
    while (!check(d, x)) { // Find minimum x such that condition is satisfied
      ++x;
    }
    printf("%lld\n", x);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/