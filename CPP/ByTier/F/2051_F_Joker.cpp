// Problem: CF 2051 F - Joker
// https://codeforces.com/contest/2051/problem/F

/*
Purpose: This code solves the problem of tracking the number of distinct positions a joker can occupy in a deck of cards after a sequence of operations. Each operation moves a card from a specified position to either the beginning or end of the deck.

Approach:
- Use a segment-based tracking technique with three segments (a[0], a[1], a[2]) to represent intervals of possible positions for the joker.
- For each operation, update the segments based on where the moved card is located relative to the current segments.
- Count the total number of distinct positions covered by these intervals.

Time Complexity: O(q) per test case, since each operation processes a fixed number of segments (3) and q operations are processed.
Space Complexity: O(1) as only a fixed-size array of 3 segments is used.

Algorithms/Techniques: 
Segment tracking, interval merging, greedy interval counting
*/

#include <algorithm>
#include <iostream>

using namespace std;
int n, m, q, t, x, ans, l, r;
bool b;
struct node {
  int x, y;
} a[3]; // Three intervals tracking possible joker positions

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> q;
    // Initialize segments: 
    // a[0] = (1, -q) -> represents range starting from 1
    // a[1] = (m, m) -> initial joker position
    // a[2] = (n + q + 1, n) -> represents range at the end
    a[0] = (node){1, -q};
    a[1] = (node){m, m};
    a[2] = (node){n + q + 1, n};
    while (q--) {
      cin >> x;
      b = false;
      // Update segments based on location of moved card
      for (int i = 0; i < 3; ++i) {
        if (x < a[i].x)
          a[i].x = max(1, a[i].x - 1);  // Shift left boundary if needed
        else if (x > a[i].y)
          a[i].y = min(n, a[i].y + 1);  // Shift right boundary if needed
        else {
          b = true;
          // If the card was in segment, collapse the segment to a single point
          if (a[i].x == a[i].y)
            a[i].x = n + q, a[i].y = -q;
        }
      }
      // Adjust segments after a collapse
      if (b) {
        a[0] = (node){1, max(1, a[0].y)};   // Adjust first interval
        a[2] = (node){min(n, a[2].x), n};   // Adjust third interval
      }
      l = 0, r = -1, ans = 0;
      // Merge and count intervals
      for (int i = 0; i < 3; ++i) {
        if (a[i].x > a[i].y)
          continue;  // Skip invalid intervals
        if (a[i].x > r) {
          ans += max(0, r - l + 1);  // Add previous interval length
          l = a[i].x, r = a[i].y;    // Start new interval
        }
        r = max(r, a[i].y);  // Extend current interval
      }
      ans += max(0, r - l + 1);  // Add last interval
      cout << ans << " ";
    }
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/