// Problem: CF 1389 A - LCM Problem
// https://codeforces.com/contest/1389/problem/A

/*
 * Problem: LCM Problem
 * 
 * Algorithm/Technique: Mathematical Analysis
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), constant space usage.
 * 
 * Approach:
 * - For a given range [l, r], we need to find two integers x and y such that
 *   l <= x < y <= r and l <= LCM(x, y) <= r.
 * - A key insight is that if we choose x = l and y = 2 * l, then:
 *   - If 2 * l <= r, then y is within the range.
 *   - LCM(l, 2*l) = 2*l, which satisfies the LCM constraint.
 * - The only case where this fails is when 2*l > r, because then we can't 
 *   find a valid y in the range that satisfies the LCM constraint.
 * 
 * Example walkthrough:
 *   Input: l=1, r=1337
 *   2*1 = 2 <= 1337 -> valid -> Output: 1 2
 *   Input: l=13, r=69
 *   2*13 = 26 <= 69 -> valid -> Output: 13 26
 *   Input: l=2, r=4
 *   2*2 = 4 <= 4 -> valid -> Output: 2 4
 *   Input: l=88, r=89
 *   2*88 = 176 > 89 -> invalid -> Output: -1 -1
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    if (2 * l > r) {
      puts("-1 -1");
    } else {
      printf("%ld %ld\n", l, 2 * l);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/