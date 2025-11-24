// Problem: CF 1227 A - Math Problem
// https://codeforces.com/contest/1227/problem/A

/*
Problem: Find the minimal length of a segment that intersects all given segments on a line.

Algorithms/Techniques: 
- Greedy approach to find intersection of all segments
- Key insight: The optimal segment lies within the intersection of all given segments

Time Complexity: O(n) per test case, where n is the number of segments
Space Complexity: O(1), only using constant extra space

*/
#include <cstdio>
#include <algorithm>

int main() {
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    int n;
    scanf("%d", &n);
    int lmx = 0, rmi = 1e9; // lmx: maximum of left bounds, rmi: minimum of right bounds
    while (n--) {
      int l, r;
      scanf("%d %d", &l, &r);
      lmx = std::max(lmx, l); // update max left bound
      rmi = std::min(rmi, r); // update min right bound
    }
    printf("%d\n", std::max(0, lmx - rmi)); // length of intersection segment (can't be negative)
  }
}


// https://github.com/VaHiX/codeForces/