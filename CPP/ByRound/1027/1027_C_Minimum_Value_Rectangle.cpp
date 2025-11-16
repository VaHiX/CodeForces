// Problem: CF 1027 C - Minimum Value Rectangle
// https://codeforces.com/contest/1027/problem/C

/*
Purpose: 
  This code solves the problem of finding four stick lengths that can form a rectangle
  with the minimum value of P^2 / S, where P is the perimeter and S is the area.
  The approach is based on sorting the stick lengths and then identifying pairs
  of equal lengths that can form the sides of the rectangle.
  
Algorithms/Techniques:
  - Sorting to group equal elements together
  - Greedy selection of side pairs to minimize the ratio P^2 / S
  - Mathematically optimizing the rectangle dimensions for minimal ratio
  
Time Complexity: O(n log n) due to sorting, where n is the number of sticks.
Space Complexity: O(n) for storing the stick lengths.
*/
#include <stdio.h>
#include <algorithm>
#include <algorithm>

#define N 1234567
using namespace std;
int t, n, x, y, last, a[N];
int main() {
  scanf("%d", &t);
  while (t--) {
    x = y = -1; // Initialize x and y to -1 to indicate unassigned sides
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]); // Read stick lengths
    sort(a, a + n); // Sort the stick lengths
    for (int i = 1; i < n; ++i)
      if (a[i] == a[i - 1]) { // Found a pair of equal lengths
        if (x == -1)
          x = a[i]; // First side length
        else if (y == -1)
          y = a[i]; // Second side length
        else if ((double)a[i] / last < (double)y / x) // Compare ratios to minimize P^2 / S
          x = last, y = a[i]; // Update with smaller ratio
        last = a[i]; // Update last to current
        i++; // Skip next element as it's already processed
      }
    printf("%d %d %d %d\n", x, x, y, y); // Output the two pairs of sides
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/