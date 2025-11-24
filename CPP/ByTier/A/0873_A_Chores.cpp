// Problem: CF 873 A - Chores
// https://codeforces.com/contest/873/problem/A

#include <cstdio>
/* 
 * Problem: Luba needs to complete n chores, each taking a[i] time.
 * She can choose at most k chores to do in x time instead of a[i].
 * Goal: Minimize total time.
 *
 * Algorithm:
 * - Since the array is sorted in non-decreasing order,
 *   to minimize total time, we should convert the k largest chores
 *   to x time each.
 * - So we sum up the first (n - k) chores and add k * x.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int main() {
  long n, k, x;
  scanf("%ld %ld %ld", &n, &k, &x);
  long total(0);
  // Sum the first (n - k) chores (the smallest ones)
  for (long p = 0; p < n - k; p++) {
    long a;
    scanf("%ld", &a);
    total += a;
  }
  // Add the time for the k chores done in x time
  total += k * x;
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/