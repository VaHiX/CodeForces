// Problem: CF 1799 A - Recent Actions
// https://codeforces.com/contest/1799/problem/A

/*
 * Problem: Recent Actions on Codeforces
 *
 * Purpose:
 *   Simulate the behavior of a fixed-size "Recent Actions" field where posts are moved to the top 
 *   when they receive actions. If a post is not in the field, it will be added at the top and the 
 *   bottommost post gets removed.
 *
 * Algorithm:
 *   - Use a vector `v` of size `n` initialized with -1 to track removal times.
 *   - Maintain a set `s` for fast lookup of posts currently in the field.
 *   - Process each action (post number) in order, updating the field accordingly.
 *   - When handling a new post:
 *       - If it's not already in the field and there is space (`idx >= 0`) 
 *         place it at position `idx` (from right to left).
 *       - Move pointer `idx` left to indicate next insertion point.
 *   - After all actions, the vector `v` holds for each original post:
 *       - Its removal time or -1 if never removed.
 *
 * Time Complexity: O(m * log m) due to set operations (insertion and counting).
 * Space Complexity: O(n + m) for the vector and set storage.
 */

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> v(n, -1);   // Initialize vector to store removal times
    std::set<long> s;             // Set to keep track of posts currently in the field
    long idx(n - 1);              // Index for placing new posts (start from end)
    for (long p = 1; p <= m; p++) {
      long x;
      scanf("%ld", &x);
      if (!s.count(x) && idx >= 0) {   // If post not in field and space available
        v[idx--] = p;                  // Place at current index and decrement
      }
      s.insert(x);                     // Insert the post into the set
    }
    for (long p = 0; p < v.size(); p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/