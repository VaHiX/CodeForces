// Problem: CF 1793 D - Moscow Gorillas
// https://codeforces.com/contest/1793/problem/D

/*
 * Problem: Moscow Gorillas
 * Algorithm: Two-pointer technique with MEX comparison
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * The solution calculates the number of subsegments where the MEX of 
 * subsegments in both permutations p and q are equal.
 * 
 * Key idea:
 * - For each number from 1 to n, we track its position in both permutations
 * - We use a sliding window approach to maintain the range of positions 
 *   covered by numbers 1 to i in both permutations
 * - For each new number, we check if it's already covered or needs a new 
 *   interval calculation using overlapping intervals
 * - Special handling for the first number (MEX = 1)
 * - The doit() and doit2() functions compute counts of valid subsegments
 *   based on overlapping ranges in both arrays
 */

#include <algorithm>
#include <cstdio>

using namespace std;
#define _int64 long long
#define mo 1000000007
int p[210000];
int ppos[210000];
int q[210000];
int qpos[210000];
_int64 doit(int x1, int y1, int x2, int y2) {
  int x, y;
  _int64 tmp;
  x = max(x1, x2);
  y = min(y1, y2);
  if (x <= y) {
    tmp = y - x + 1;
    return tmp * (tmp + 1) / 2;
  } else
    return 0;
}
_int64 doit2(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
  _int64 xx1, yy1, xx2, yy2;
  xx1 = max(x1, x3);
  xx2 = min(x2, x4);
  yy1 = max(y1, y3);
  yy2 = min(y2, y4);
  if ((xx2 >= xx1) && (yy2 >= yy1))
    return (xx2 - xx1 + 1) * (yy2 - yy1 + 1);
  return 0;
}
int main() {
  int i, j, k, n, x, y, l, t, m, o, b1, ll1, rr1, ll2, rr2, x1, y1, x2, y2, x3,
      y3, x4, y4;
  _int64 ans;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &p[i]);
    ppos[p[i]] = i;
  }
  for (i = 0; i < n; i++) {
    scanf("%d", &q[i]);
    qpos[q[i]] = i;
  }
  ans = 0;
  // Handle MEX = 1 case by checking all valid segments where first element is 1
  ans += doit(0, ppos[1] - 1, 0, qpos[1] - 1);
  ans += doit(0, ppos[1] - 1, qpos[1] + 1, n - 1);
  ans += doit(ppos[1] + 1, n - 1, 0, qpos[1] - 1);
  ans += doit(ppos[1] + 1, n - 1, qpos[1] + 1, n - 1);
  // Initialize pointers to current position of element 1 in both arrays
  ll1 = ppos[1];
  rr1 = ppos[1];
  ll2 = qpos[1];
  rr2 = qpos[1];
  for (i = 2; i <= n; i++) {
    // If i is included in current range of both arrays, continue
    if ((ll1 <= ppos[i]) && (ppos[i] <= rr1)) {
    } else if ((ll2 <= qpos[i]) && (qpos[i] <= rr2)) {
    } else {
      // Calculate new potential segment
      if (ppos[i] < ll1) {
        x1 = ppos[i] + 1;
        y1 = ll1;
        x2 = rr1;
        y2 = n - 1;
      } else {
        x1 = 0;
        y1 = ll1;
        x2 = rr1;
        y2 = ppos[i] - 1;
      }
      if (qpos[i] <= ll2) {
        x3 = qpos[i] + 1;
        y3 = ll2;
        x4 = rr2;
        y4 = n - 1;
      } else {
        x3 = 0;
        y3 = ll2;
        x4 = rr2;
        y4 = qpos[i] - 1;
      }
      // Add valid subsegments to answer
      ans += doit2(x1, x2, y1, y2, x3, x4, y3, y4);
    }
    // Update ranges to include current element i
    ll1 = min(ll1, ppos[i]);
    rr1 = max(rr1, ppos[i]);
    ll2 = min(ll2, qpos[i]);
    rr2 = max(rr2, qpos[i]);
  }
  ans++; // Count the initial segment [1, 1]
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/