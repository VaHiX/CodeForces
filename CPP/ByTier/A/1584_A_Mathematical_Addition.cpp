// Problem: CF 1584 A - Mathematical Addition
// https://codeforces.com/contest/1584/problem/A

/*
Algorithm: Mathematical Manipulation
Approach:
Given the equation: 
    x/u + y/v = (x+y)/(u+v)
Rearranging:
    x/v + y/u = (x+y)/(u+v) 
Cross multiply to simplify and solve for x and y.
The key insight is that substituting x = u^2 and y = -v^2 works for all valid inputs.
This gives a straightforward and efficient solution.

Time Complexity: O(1) - Each test case is processed in constant time.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll u, v;
    scanf("%lld %lld", &u, &v);
    printf("%lld %lld\n", u * u, -v * v);  // Output x = u^2, y = -v^2
  }
}


// https://github.com/VaHiX/CodeForces/