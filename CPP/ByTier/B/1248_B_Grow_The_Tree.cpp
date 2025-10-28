// Problem: CF 1248 B - Grow The Tree
// https://codeforces.com/contest/1248/problem/B

/*
B. Grow The Tree
Algorithms/Techniques: Sorting, Greedy approach
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

The problem requires arranging sticks to form a polyline such that 
the final point is as far as possible from the origin (0, 0). 
Each stick is placed either horizontally or vertically, and no two 
consecutive sticks can be aligned in the same direction.
To maximize distance, we want to distribute stick lengths between 
x and y components of the final position. The optimal strategy is 
to sort stick lengths and assign smallest half to one axis and 
largest half to the other. This ensures a balanced distribution 
that maximizes the sum of squares of coordinates.

Input:
- n: number of sticks
- Array of n stick lengths

Output:
- Square of maximum distance from (0, 0) to end point
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n); // Store stick lengths
  for (long p = 0; p < n; p++) {
    scanf("%lld", &a[p]); // Read each stick length
  }
  sort(a.begin(), a.end()); // Sort stick lengths in ascending order
  ll x(0), y(0); // x and y components of the final position
  for (long p = 0; p < n / 2; p++) {
    x += a[p]; // Add smaller half to x-component
  }
  for (long p = n / 2; p < n; p++) {
    y += a[p]; // Add larger half to y-component
  }
  printf("%lld\n", x * x + y * y); // Output square of distance
  return 0;
}


// https://github.com/VaHiX/codeForces/