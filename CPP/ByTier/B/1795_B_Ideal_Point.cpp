// Problem: CF 1795 B - Ideal Point
// https://codeforces.com/contest/1795/problem/B

/*
B. Ideal Point
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm/Techniques: 
- For each test case, we check if point k can become ideal by examining how many segments cover it from left and right.
- We count how many segments have k as their left endpoint (bl) and how many have k as their right endpoint (br).
- If both bl and br are true, then k is covered by at least one segment on the left and right, which allows it to be ideal if we carefully select segments.

Time Complexity: O(n) per test case, where n is the number of segments.
Space Complexity: O(1), constant extra space used.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    bool bl(false), br(false);  // bl: k is left endpoint of some segment, br: k is right endpoint
    for (long p = 0; p < n; p++) {
      long left(0), right(0);
      scanf("%ld %ld", &left, &right);
      if (k == left) {     // Check if k is a left endpoint
        bl = true;
      }
      if (k == right) {    // Check if k is a right endpoint
        br = true;
      }
    }
    puts(bl && br ? "YES" : "NO");  // If both are true, k can be ideal
  }
}


// https://github.com/VaHiX/codeForces/