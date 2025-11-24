// Problem: CF 660 C - Hard Process
// https://codeforces.com/contest/660/problem/C

#include <cstdio>
// Flowerbox describing the code purpose, algorithms, and complexities
/*
 * Problem: C. Hard Process
 * Purpose: Given a binary array and a number k, we can change at most k zeros to ones
 *          to maximize the length of the longest subsegment of 1s.
 * Algorithm: Sliding window technique.
 *            - Use two pointers to maintain a window containing at most k zeros.
 *            - Expand the right pointer and shrink the left when more than k zeros are in window.
 *            - Track the maximum window size.
 * Time Complexity: O(n) - Linear scan with two pointers
 * Space Complexity: O(n) - For storing the array
 */

int a[300001];
int main() {
  int ans = 0, n, k, pi, pj; // ans: max length, pi/pj: start/end of best segment
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1, j = 0, cnt = 0; i <= n; cnt -= !a[i++]) {
    // cnt tracks number of zeros in current window [i, j]
    // While loop expands j while we have <= k zeros
    while (cnt <= k && j <= n)
      cnt += !a[++j]; // increment j and count new zero if a[j] is 0
    // Update the maximum length and positions if current window is better
    if (j - i > ans)
      ans = j - i, pi = i, pj = j;
  }
  printf("%d\n", ans);
  for (int i = 1; i <= n; ++i)
    // Change zeros to ones in the best segment identified
    printf("%d ", a[i] || (i >= pi && i < pj));
}


// https://github.com/VaHiX/CodeForces/