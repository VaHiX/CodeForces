// Problem: CF 2004 B - Game with Doors
// https://codeforces.com/contest/2004/problem/B

/*
B. Game with Doors
Algorithm: Greedy + Interval Overlap Analysis
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves determining the minimum number of doors to lock between two intervals [l,r] and [L,R] such that Alice (in [l,r]) and Bob (in [L,R]) cannot reach each other. 

Key insight:
- Two segments are reachable if there exists a path from any point in [l,r] to any point in [L,R].
- A path exists if the intervals overlap or are adjacent.
- We need to prevent such connection by locking minimum doors.

Steps:
1. Calculate intersection of intervals: max(l,L) and min(r,R).
2. If intersection exists (mnr >= mxl), then they can meet — we must lock a certain number of doors in between.
3. Otherwise, we still need to break the path by locking doors.
4. Handle edge cases with inequalities.

This solution computes the minimum number of doors to lock using:
- Overlap calculation: max(l,L) and min(r,R)
- Length of overlap region
- Account for case when segments do not intersect
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long L, R;
    scanf("%ld %ld", &L, &R);
    long mxl = (l > L ? l : L);            // Start of overlapping interval
    long mnr = (r < R ? r : R);            // End of overlapping interval
    long len = (mnr - mxl);                // Length of overlap
    long res = len + (l != L) + (r != R);  // Base doors to lock + adjust for segment boundaries
    res = (len >= 0 ? res : 1);            // If no overlap, we still must lock one door
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/