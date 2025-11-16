// Problem: CF 952 C - Ravioli Sort
// https://codeforces.com/contest/952/problem/C

/*
 * Algorithm: Ravioli Sort Validation
 * 
 * Purpose:
 *   This program determines whether a given array can be correctly sorted 
 *   using a custom "ravioli sort" algorithm. The algorithm simulates stacks 
 *   of ravioli and checks for valid transitions based on height differences.
 * 
 * Approach:
 *   The key insight is that if any two adjacent elements in the array differ 
 *   by more than 1, then during the sorting process, the ravioli from the taller 
 *   stack will slide onto the shorter one, disrupting the correct sorting order.
 * 
 * Time Complexity: O(n)
 *   - Single pass through the array of size n.
 * 
 * Space Complexity: O(1)
 *   - Only constant extra space is used.
 * 
 * Techniques:
 *   - Linear scan with pairwise comparison
 *   - Early termination if condition fails
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long prev(0), cur(0);  // prev stores previous element, cur is current
  bool possible(true);   // flag to track if sorting is possible
  for (long p = 0; p < n; p++) {
    long cur;
    scanf("%ld", &cur);  // read current element
    // Check if current and previous differ by more than 1
    if (p > 0 && ((cur - prev > 1) || (prev - cur > 1))) {
      possible = false;  // if so, sorting is not possible
      break;             // early exit
    }
    prev = cur;  // update previous to current for next iteration
  }
  puts(possible ? "YES" : "NO");  // output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/