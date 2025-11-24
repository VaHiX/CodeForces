// Problem: CF 1696 B - NIT Destroys the Universe
// https://codeforces.com/contest/1696/problem/B

/*
 * Problem: B. NIT Destroys the Universe
 * 
 * Purpose: Find the minimum number of operations to make all elements in the array equal to 0.
 *          Each operation selects a subarray, computes its mex (minimum excludant), and sets
 *          all elements in that subarray to the mex value.
 * 
 * Algorithm:
 *   - The key insight is identifying contiguous segments where we need to apply operations.
 *   - We track transitions from non-zero values to zero values or end of array.
 *   - A segment is marked for an operation if it contains at least one non-zero element.
 *   - For each such segment, we count how many such segments there are.
 *   - If the count is less than 2, return the count; otherwise, return 2 (since the maximum
 *     required operations to reduce any array to all zeros is 2).
 * 
 * Time Complexity: O(n) per test case, where n is the size of the array (linear scan)
 * Space Complexity: O(1) - uses only a constant amount of extra space
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);           // Count of segments that need operations
    bool cur(0);           // Tracks if we are inside a segment with non-zero elements
    
    while (n--) {
      long x;
      scanf("%ld", &x);
      
      if (x) {
        // If current value is non-zero, we are in a segment that needs an operation
        cur = 1;
      } else if (cur) {
        // Current value is zero but we were previously in a non-zero segment
        // Thus, we mark the end of a segment requiring an operation
        ++cnt;
        cur = 0;
      }
    }
    
    // Add one more count if the array ends while we're in a non-zero segment
    cnt += cur;
    
    // The number of operations needed is at most 2
    cnt = (cnt < 2) ? cnt : 2;
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/