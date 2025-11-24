// Problem: CF 755 D - PolandBall and Polygon
// https://codeforces.com/contest/755/problem/D

/*
Purpose: 
This program calculates the number of sections (areas) inside a convex polygon after drawing n red segments. 
Each segment connects a vertex to another vertex that is k steps away in clockwise order, where gcd(n, k) = 1.
The algorithm uses modular arithmetic to trace the path and compute how the number of sections increases with each new segment.

Algorithms/Techniques:
- Modular arithmetic to simulate the traversal of the polygon vertices.
- Efficient tracking of how many new regions are created with each new segment.
- Uses symmetry: k is replaced with min(k, n-k) to reduce computation.

Time Complexity: O(n)
Space Complexity: O(1)

*/
#include <cstdio>
typedef long long ll;
int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  ll cur(0), cycle(0), cnt(1); // cur: current vertex, cycle: number of cycles completed, cnt: total sections
  k = (k < n - k) ? k : (n - k); // Optimize k to use the smaller step (symmetry)
  for (int p = 0; p < n; p++) {
    cur += k; // Move k steps forward
    cnt += cycle + 1 + (cur > n); // Update the count of sections
    if (cur > n) { // If we've crossed the last vertex
      cycle += 2; // Increment cycle count by 2 (as per pattern)
      cur %= n; // Wrap around to next cycle
    }
    printf("%lld ", cnt);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/