// Problem: CF 1895 B - Points and Minimum Distance
// https://codeforces.com/contest/1895/problem/B

/*
 * Problem: Points and Minimum Distance
 * 
 * Purpose: Given a sequence of 2n integers, split them into n pairs to form n points.
 *          Find a path that visits all points such that the total Manhattan distance is minimized.
 * 
 * Algorithm:
 *   - Sort the array of 2n integers.
 *   - Pair the first n elements with the last n elements.
 *   - The optimal path will have total distance equal to:
 *     (max_x - min_x) + (max_y - min_y), where x and y are the coordinates of the points.
 *   - The minimum possible path length corresponds to sorting the values and pairing
 *     the lowest n values with the highest n values to minimize the overall span.
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the vector
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(2 * n); // Create vector to hold 2n integers
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &a[p]); // Read all integers into the vector
    }
    sort(a.begin(), a.end()); // Sort the array to optimally pair elements
    
    // Calculate the minimum path length
    // The idea is to minimize the range of x-coordinates and y-coordinates
    long res = (a[2 * n - 1] - a[n]) + (a[n - 1] - a[0]);
    printf("%ld\n", res);
    
    // Print the coordinates of the points
    for (long p = 0; p < n; p++) {
      printf("%ld %ld\n", a[p], a[n + p]); // Pair first n with last n elements
    }
  }
}


// https://github.com/VaHiX/CodeForces/