// Problem: CF 1680 A - Minimums and Maximums
// https://codeforces.com/contest/1680/problem/A

/*
 * Problem: Minimum possible number of elements in a "beautiful" array.
 * 
 * A beautiful array satisfies:
 * - At least l1 and at most r1 elements equal to its minimum.
 * - At least l2 and at most r2 elements equal to its maximum.
 *
 * Algorithm:
 * We want to minimize the total size of the array while satisfying both constraints.
 * 
 * Key insight:
 * 1. If we use a single value for both min and max (e.g., all elements are same),
 *    then the array size can be min(r1, r2) + max(l1, l2). But since we need at least
 *    l1 elements of min and l2 elements of max, if they overlap, we adjust accordingly.
 *
 * 2. If min and max are different:
 *    - We must have at least l1 elements equal to minimum value.
 *    - We must have at least l2 elements equal to maximum value.
 *    - These could be the same elements (if l1 + l2 <= r1 + r2), but that's a special case.
 * 
 * Approach:
 * Try placing minimums and maximums optimally:
 *   - Find the smaller of r1 and r2 as candidate for overlapping count.
 *   - If we can accommodate both constraints in a shared element, use min(r1,r2) + max(l1,l2) - overlap.
 *     But simpler: take max(l1,l2), since that ensures at least enough minimums/maxes.
 *   - If we cannot use same elements (i.e., there's no overlap in required counts):
 *      -> total = l1 + l2.
 * 
 * Time Complexity: O(1) per test case.
 * Space Complexity: O(1).
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long la, ra, lb, rb;
    scanf("%ld %ld %ld %ld", &la, &ra, &lb, &rb);
    long mn = (la > lb) ? la : lb; // Take max of lower bounds to satisfy both constraints
    // If the minimum of both (mn) can be accommodated without violating limits
    long res = (mn <= ra && mn <= rb) ? mn : (la + lb); // Otherwise, force separate elements
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/