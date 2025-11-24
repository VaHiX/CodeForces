// Problem: CF 1843 A - Sasha and Array Coloring
// https://codeforces.com/contest/1843/problem/A

/*
 * Problem: Sasha and Array Coloring
 * Purpose: Given an array of integers, find the maximum possible cost of coloring
 *          the array such that each element belongs to exactly one color and
 *          each color has at least one element. The cost of a color is defined
 *          as max(S) - min(S), where S is the set of elements with that color.
 *          
 * Algorithm: 
 *   - Sort the array.
 *   - Pair elements from both ends (smallest with largest).
 *   - For each such pair, compute the difference and accumulate.
 *   
 * Time Complexity: O(n log n) due to sorting; the loop is O(n/2)
 * Space Complexity: O(1) if we don't count input storage, otherwise O(n) for vector
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
    std::vector<long> a(n);           // Create vector to store array elements
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);            // Read each element
    }
    sort(a.begin(), a.end());         // Sort the array to enable optimal pairing
    long cnt(0);
    for (long p = 0; 2 * p < n; p++) {
      cnt += a[n - 1 - p] - a[p];     // Add difference between farthest and closest elements in current pair
    }
    printf("%ld\n", cnt);             // Output result for the test case
  }
}


// https://github.com/VaHiX/codeForces/