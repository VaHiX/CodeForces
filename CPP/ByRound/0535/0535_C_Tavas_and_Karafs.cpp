// Problem: CF 535 C - Tavas and Karafs
// https://codeforces.com/contest/535/problem/C

/*
 * Problem: Tavas and Karafs
 * 
 * Purpose:
 *   Given a sequence of Karafses with heights defined by s[i] = A + (i - 1) * B,
 *   determine the maximum index r such that the subsequence from l to r can be
 *   completely eaten using at most t operations, where each operation can
 *   decrease the height of up to m Karafses by 1.
 * 
 * Approach:
 *   - For each query, perform binary search on the index r to find maximum
 *     valid r such that the sum of heights from l to r can be reduced to 0
 *     within t operations, with each operation affecting at most m Karafses.
 *   - The sum of heights from l to r is computed using arithmetic sequence formula.
 *   - After binary search, adjust the result based on the constraint of maximum
 *     possible r given the total operations available.
 * 
 * Time Complexity: O(n * log(T + l)) where T is the maximum possible value of t
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long long a, b, n;
  scanf("%lld %lld %lld", &a, &b, &n);
  while (n--) {
    long long l, t, m;
    scanf("%lld %lld %lld", &l, &t, &m);
    // If even the first element can't be eaten in t operations, no valid r exists
    if (t < a + (l - 1) * b) {
      puts("-1");
      continue;
    }
    // Binary search for maximum r
    long long left(l), right(t + l), res(left);
    while (left <= right) {
      long long mid = (left + right) / 2;
      // Compute sum of heights from l to mid using arithmetic series formula
      long long sum = (2 * a + (l + mid - 2) * b) * (mid - l + 1) / 2;
      if (sum <= t * m) {
        res = mid;        // Valid, try to find larger r
        left = mid + 1;
      } else {
        right = mid - 1;  // Not valid, decrease r
      }
    }
    // Final adjustment: ensure r does not exceed the upper bound based on sum of heights
    res = (res < (t + b - a) / b) ? res : ((t + b - a) / b);
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/