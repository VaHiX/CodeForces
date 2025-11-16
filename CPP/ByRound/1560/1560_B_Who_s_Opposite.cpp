// Problem: CF 1560 B - Who's Opposite?
// https://codeforces.com/contest/1560/problem/B

/*
B. Who's Opposite?
Purpose: Given three people a, b, c in a circle where a looks at b (and vice versa), determine who c looks at.
         If no valid circle exists, return -1.

Algorithm:
- For a circle of n people numbered 1 to n, person i looks at person (i + n/2) % n if n is even.
- From known a and b, we deduce n using the fact they are opposite: |a - b| = n/2 ⇒ n = 2 * |a - b|.
- We can also verify that c must be within [1, n] for it to be valid.

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    ll d = b - a; // Compute difference between a and b
    if (d < 0) {
      d = -d; // Take absolute value of difference
    }
    ll n = 2 * d; // Circle size is twice the distance between opposite people
    
    // Determine who c looks at based on circle size
    ll res = c + ((c <= d) ? d : (-d));  // If c is in first half, look forward, else backward
    
    // If c, a, or b is outside the circle range, invalid
    if (c > n || b > n || a > n) {
      res = -1;
    }
    
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/