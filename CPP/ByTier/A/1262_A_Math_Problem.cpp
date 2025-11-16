// Problem: CF 1262 A - Math Problem
// https://codeforces.com/contest/1262/problem/A

/*
Problem: Find the minimum length of a segment that intersects all given segments on a line.

Algorithms/Techniques: 
- Greedy approach to find intersection of all segments
- For each test case, we compute the maximum left boundary and minimum right boundary
  among all segments. The optimal segment is [max_left, min_right].

Time Complexity: O(n) per test case, where n is the number of segments
Space Complexity: O(1), only using a few variables

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long mn(1e9 + 7), mx(-1); // Initialize min right boundary and max left boundary
    long n;
    scanf("%ld", &n);
    while (n--) {
      long left, right;
      scanf("%ld %ld", &left, &right);
      mn = (mn < right) ? mn : right;  // Update minimum right boundary
      mx = (mx > left) ? mx : left;    // Update maximum left boundary
    }
    printf("%ld\n", (mn < mx) ? (mx - mn) : 0); // Length of intersection segment, 0 if no intersection
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/