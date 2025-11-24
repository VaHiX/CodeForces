// Problem: CF 1355 C - Count Triangles
// https://codeforces.com/contest/1355/problem/C

/*
C. Count Triangles
Time Complexity: O(D - C)
Space Complexity: O(1)

The problem asks to count the number of non-degenerate triangles with integer 
sides x, y, z such that A ≤ x ≤ B ≤ y ≤ C ≤ z ≤ D.

Key idea:
- For a valid triangle, the triangle inequality must hold: x + y > z.
- Given constraint A ≤ x ≤ B ≤ y ≤ C ≤ z ≤ D, we iterate over all possible values of z.
- For each fixed z, we determine which combinations of x and y are valid such that
  x + y > z and the constraints on x, y, z are satisfied.
- The calculation uses arithmetic progression sum formula for efficient computation.

Algorithms/Techniques:
- Iterative enumeration with mathematical optimization using arithmetic progression.
- Precomputation of ranges and bounds to avoid brute-force triple loops.

*/

#include <cstdio>
typedef long long ll;

// Calculates the sum of an arithmetic progression: S = n * (2*a + (n-1)*d) / 2
ll calcProgression(ll a, ll d, ll n) { return (2 * a + d * (n - 1)) * n / 2; }

// Returns maximum of two values
ll mx(ll a, ll b) { return (a > b) ? a : b; }

int main(void) {
  ll a, b, c, d;
  scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
  ll ans = 0;
  
  // Iterate over all possible values of z from C to D
  for (ll z = c; z <= d; ++z) {
    // Minimum value x can take such that triangle inequality holds and x <= B
    int minX = mx(a, z - c + 1);
    
    if (minX > b) {
      continue; // No valid x values exist for this z
    }
    
    // Midpoint used to compute starting point based on constraints
    int mid = z - b + 1;
    
    // Start of valid range for x given y = B
    int start = c - mx(b, z - minX + 1) + 1;
    
    if (mid <= minX) {
      // Case where all valid combinations fit into a simple rectangle
      ans += (c - b + 1) * (b - minX + 1);
    } else if (mid > b) {
      // Use arithmetic progression for increasing range
      ans += calcProgression(start, 1, b - minX + 1);
    } else {
      // Mixed case: part with progressive count and rectangular part
      ans +=
          calcProgression(start, 1, mid - minX + 1) + (b - mid) * (c - b + 1);
    }
  }
  
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/