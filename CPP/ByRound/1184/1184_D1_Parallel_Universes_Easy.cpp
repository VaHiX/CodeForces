// Problem: CF 1184 D1 - Parallel Universes (Easy)
// https://codeforces.com/contest/1184/problem/D1

#include <cstdio>
// Flowerbox:
/*
 * Problem: D1. Parallel Universes (Easy)
 * Purpose: Simulate a multiverse where universes can be added or links
 *          between them can be broken. The Doctor starts in a known position,
 *          and we simulate t operations to track the multiverse length and
 *          the Doctor's position after each operation.
 *
 * Algorithms/Techniques:
 *   - Simulation with state tracking of universe length and Doctor position
 *   - Conditional updates based on action type (insert or break link)
 *   - Efficient handling of index adjustments when inserting or removing universes
 *
 * Time Complexity: O(t * n), where t is number of operations and n is current universe count
 * Space Complexity: O(1) - only using constant extra space for variables
 */
int main() {
  long length, pos, m, t;
  scanf("%ld %ld %ld %ld", &length, &pos, &m, &t);
  while (t--) {
    long action, w;
    scanf("%ld %ld", &action, &w);
    if (action == 0) {
      // Action 0: Break a link between two adjacent universes.
      // The segment NOT containing the Doctor is destroyed.
      // Length decreases by 1.
      // Adjust position accordingly:
      //   - If w < pos, we are removing a universe to the left of the Doctor
      //     so we decrease pos by w (since Doctor's relative position shifts)
      //   - Otherwise, we're removing a universe to the right, so we do not adjust pos.
      length -= ((w < pos) ? w : (length - w));
      pos -= w * (w < pos);  // Adjust doctor's position based on where link is broken
    } else {
      // Action 1: Insert a new universe.
      // Length increases by 1.
      // Doctor's position might shift if insertion happens to the left of him.
      ++length;
      pos += (w <= pos);  // If w <= pos, insert before or at current doctor position
    }
    printf("%ld %ld\n", length, pos);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/