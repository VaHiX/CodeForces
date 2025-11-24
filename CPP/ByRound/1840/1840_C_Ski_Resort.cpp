// Problem: CF 1840 C - Ski Resort
// https://codeforces.com/contest/1840/problem/C

/*
C. Ski Resort

Purpose:
This code solves the problem of counting the number of ways to choose consecutive vacation days 
at a ski resort such that:
1. The vacation lasts at least k days.
2. The temperature on each day does not exceed q degrees.

Algorithm:
- Uses a sliding window technique to track consecutive days where temperature <= q.
- For each valid segment of length >= k, the number of subsegments of length >= k is added to result.
- Time Complexity: O(n) per test case, Space Complexity: O(1)

Techniques:
- Linear scan with running counter for consecutive valid days.
- Mathematical formula to count valid subsegments in a window.

Input Format:
- t test cases
- For each test case: n k q followed by n temperatures

Output Format:
- Number of valid vacation periods per test case
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, q;
    scanf("%ld %ld %ld", &n, &k, &q);
    long long cnt(0), res(0); // cnt: current length of valid consecutive days; res: total ways
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= q) {
        ++cnt; // extend the current valid segment
      } else {
        cnt = 0; // reset the segment as temperature exceeds q
      }
      // Add number of valid subsegments ending at current day with length >= k
      res += (cnt >= k) ? (cnt - k + 1) : 0;
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/