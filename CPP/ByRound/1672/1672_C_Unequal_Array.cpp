// Problem: CF 1672 C - Unequal Array
// https://codeforces.com/contest/1672/problem/C

/*
C. Unequal Array
Purpose: Given an array of integers, find the minimum number of operations to reduce the number of adjacent equal elements to at most 1.
Algorithm: 
    - Identify all consecutive equal elements and their positions.
    - For each group of consecutive equal elements, calculate the minimum operations needed to break them into at most one equality.
    - Use greedy approach: for a contiguous segment of equal elements with length > 2, we need (length - 1) / 2 operations.
Time Complexity: O(n) where n is the total number of elements across all test cases.
Space Complexity: O(1) as we only use a constant amount of extra space.

Input:
    Multiple test cases. Each case has n elements.
Output:
    Minimum operations to ensure at most one equality in array.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev;
    scanf("%ld", &prev);
    long left(0), right(0); // Track the first and last position of a group of equal elements
    for (long p = 2; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == prev) { // If current element equals previous, it's part of same group
        left = (left ? left : p); // Set left to first position or keep existing
        right = p;                // Update right to current position
      }
      prev = x;  // Move to next element
    }
    if (left == right) {  // No equal adjacent elements found
      puts("0");
    } else {
      // If there's a gap between left and right positions, calculate operations needed
      printf("%ld\n", (right > left + 1) ? (right - left - 1) : 1);
    }
  }
}


// https://github.com/VaHiX/codeForces/