// Problem: CF 1792 B - Stand-up Comedian
// https://codeforces.com/contest/1792/problem/B

/*
 * Problem: B. Stand-up Comedian
 * Purpose: Maximize the number of jokes Eve can tell before either spectator leaves or all jokes are told.
 * Approach:
 *   - Greedily arrange jokes to keep both spectators happy as long as possible.
 *   - Type 1 jokes (both like): prioritize these first to increase moods.
 *   - Type 2/3 jokes (one likes, one dislikes): handle by transferring mood balance from the one with lower excess.
 *   - Type 4 jokes (neither likes): these decrease both moods. Use them last to avoid early exits.
 *
 * Time Complexity: O(1) per test case - constant number of operations
 * Space Complexity: O(1) - uses fixed-size variables
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    long cnt(a); // Start with type 1 jokes; if a > 0, we can tell all of them
    long m = (b < c ? b : c); // Minimum of type 2 and 3 jokes to pair with type 1
    if (a) {
      cnt += 2 * m; // For each such pair, both spectators get +1 mood (from type 1 joke), then one gets -1 per person (type 2 or 3)
      b -= m;
      c -= m;
    }
    if (b) { // If there are remaining type 2 jokes
      long more = (a < b ? a : b); // Choose minimum between remaining type 1 and type 2 for balance
      b -= more;
      a -= more;
      cnt += more; // Add balanced jokes
    } else { // If no type 2 jokes, handle type 3
      long more = (a < c ? a : c); // Same logic for balancing
      c -= more;
      a -= more;
      cnt += more;
    }
    if (a > 0) { // Remaining type 1 jokes that can be used to adjust moods
      long more = (a < d ? a : d); // Pair remaining type 1 with type 4
      d -= more;
      a -= more;
      cnt += more;
    }
    if (b > 0 || c > 0 || d > 0) { // If any spectators' moods are negative due to type 4 jokes, we add one final joke to make it end
      ++cnt;
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/