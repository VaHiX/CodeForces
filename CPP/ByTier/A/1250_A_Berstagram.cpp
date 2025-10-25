// Problem: CF 1250 A - Berstagram
// https://codeforces.com/contest/1250/problem/A

/*
 * Problem: Berstagram
 * Algorithm: Simulation with position tracking
 * Time Complexity: O(n + m)
 * Space Complexity: O(n)
 *
 * Description:
 * We simulate a social media feed where posts can be reordered based on likes.
 * Each like causes a post to move up one position if it's not already at the top.
 * For each post, we track its minimum and maximum position throughout all operations.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> which(n + 1), where(n + 1), top(n + 1), bottom(n + 1);
  for (long p = 1; p <= n; p++) {
    top[p] = bottom[p] = which[p] = where[p] = p;
  }
  for (long p = 0; p < m; p++) {
    long x;
    scanf("%ld", &x);
    long pos = where[x]; // Get current position of post x
    if (pos <= 1) {
      continue; // If already at top, no movement needed
    }
    long y = which[pos - 1]; // Get the post above x
    where[x] = pos - 1;      // Move x up one position
    which[pos - 1] = x;      // Update which array for new place of x
    where[y] = pos;          // Move y down one position
    which[pos] = y;          // Update which array for new place of y
    top[x] = (top[x] < where[x]) ? top[x] : where[x]; // Update min position of x
    bottom[y] = (bottom[y] > where[y]) ? bottom[y] : where[y]; // Update max position of y
  }
  for (long p = 1; p <= n; p++) {
    printf("%ld %ld\n", top[p], bottom[p]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/