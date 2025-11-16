// Problem: CF 1344 A - Hilbert's Hotel
// https://codeforces.com/contest/1344/problem/A

/*
 * Problem: Hilbert's Hotel
 * Algorithm: Check if a permutation of rooms is valid after shuffling.
 *            Each guest in room k moves to room (k + a[k % n]).
 *            We need to verify that no two guests are assigned to the same room.
 *
 * Time Complexity: O(n) per test case, since we process each element once.
 * Space Complexity: O(n) for storing the boolean vector indicating occupied rooms.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<bool> b(n); // Tracks which rooms have been assigned
    bool ans(true);
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      // Compute the destination room for guest in room p
      long to = (p + (n + (a % n))) % n;
      // If this room was already assigned, there's a collision
      if (b[to]) {
        ans = false;
      }
      b[to] = 1; // Mark this room as assigned
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/