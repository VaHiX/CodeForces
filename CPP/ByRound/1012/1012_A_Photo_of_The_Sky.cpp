// Problem: CF 1012 A - Photo of The Sky
// https://codeforces.com/contest/1012/problem/A

/*
Problem: Photo of The Sky
Algorithms/Techniques: Sorting, two pointers, brute force on sorted array

Time Complexity: O(n * log n)
Space Complexity: O(n)

The problem involves finding the minimal area of a rectangle that can contain all given points,
where points are given in a flattened list (x1, y1, x2, y2, ..., xn, yn).
Since we don't know which numbers correspond to which coordinates, we try different combinations
by sorting and checking possible x and y ranges.

The approach:
1. Sort the input array.
2. Try all possible ways to split the sorted array into two parts representing x and y coordinates.
3. Calculate the rectangle area for each configuration and keep track of minimum.
*/

#include <stdio.h>
#include <algorithm>

#define ll long long
int a[200005];
int n;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n * 2; i++)
    scanf("%d", a + i); // Read all coordinates into array
  
  std::sort(a, a + n * 2); // Sort the coordinates
  
  ll ans = a[n - 1] - a[0]; // Initial case: first n elements are x, last n are y
  ans *= a[n * 2 - 1] - a[n]; // Calculate area
  
  for (int i = 1; i < n; i++) {
    // Try splitting at position i: first i elements as x coords, next n-i as y coords
    ll h = a[i + n - 1] - a[i]; // Height of rectangle using these coordinates
    ll w = a[2 * n - 1] - a[0]; // Width is always max_x - min_x (which are fixed)
    ans = std::min(ans, h * w); // Update minimum area
  }
  
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/codeForces/