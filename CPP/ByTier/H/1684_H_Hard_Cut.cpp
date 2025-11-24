// Problem: CF 1684 H - Hard Cut
// https://codeforces.com/contest/1684/problem/H

/*
Algorithm: Greedy + Binary Search
Approach:
1. Calculate the total sum of the binary string (number of 1s).
2. Find the smallest power of 2 that is greater than or equal to the sum.
3. Try to partition the string greedily such that each substring's value sums to the target power of 2.
4. If the current partition fails, double the target and retry.

Time Complexity: O(n log n) where n is the length of the string.
Space Complexity: O(n) for storing answer indices.
*/

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
const int N = 1e6 + 10;
int ans[N][2], t;
string st;
int main() {
  cin >> t;
  while (t--) {
    cin >> st;
    int len = st.length(), sum = 0, d = 1, tot;
    // Count total number of 1s in the binary string
    for (int i = 0; i < len; i++) {
      sum += st[i] - '0';
    }
    // If all are 0s, impossible to form a power of 2
    if (sum == 0) {
      printf("-1\n");
      continue;
    }
    // Find the smallest power of 2 greater than or equal to sum
    while (d < sum)
      d = d * 2;
    while (true) {
      int now = 0, L = 1, tmp = sum;
      tot = 0;
      // Greedily partition the string
      for (int i = 1; i <= len; i++) {
        int t = now;
        // If adding current value doesn't exceed target, continue
        if (sum + t <= d)
          sum = sum + t;
        else {
          // Start a new segment
          ans[++tot][0] = L;
          ans[tot][1] = i - 1;
          L = i;
          now = 0;
        }
        now = now * 2 + st[i - 1] - '0';
      }
      // Add last segment
      ans[++tot][0] = L;
      ans[tot][1] = len;
      // If all segments sum to the target power of 2, break
      if (sum == d)
        break;
      // Otherwise, try a larger power of 2
      sum = tmp;
      d *= 2;
    }
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
      printf("%d %d\n", ans[i][0], ans[i][1]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/