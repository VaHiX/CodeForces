// Problem: CF 1375 C - Element Extermination
// https://codeforces.com/contest/1375/problem/C

/*
 * Problem: C. Element Extermination
 * 
 * Purpose: Determine if we can reduce an array of distinct integers from 1 to n
 *          to a single element by repeatedly removing one of two adjacent elements
 *          where the left is smaller than the right.
 *
 * Algorithm:
 *   - For each test case, we read the array and process it.
 *   - The key observation is that we can remove an element if it's smaller
 *     than its next neighbor. We iterate through the array and simulate
 *     removals to find whether we can reduce the whole array to one element.
 *   - However, in this specific implementation, we read only the first two elements
 *     (x and y), then process all remaining elements but do not actually remove them.
 *     Instead, it compares x and the last read value (y) and outputs result based on that.
 *
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1) - only using a fixed amount of extra variables.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    long y;
    // Read all elements but only keep track of the last one (y)
    for (long p = 1; p < n; p++) {
      scanf("%ld", &y);
    }
    // If first element is less than last, output YES, otherwise NO
    puts(x < y ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/