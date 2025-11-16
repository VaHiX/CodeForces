// Problem: CF 1781 E - Rectangle Shrinking
// https://codeforces.com/contest/1781/problem/E

/*
Algorithm: Greedy Interval Scheduling on 2-row Grid
Time Complexity: O(n log n) due to sorting and linear pass
Space Complexity: O(n) for storing rectangles and auxiliary arrays

This solution uses a greedy approach to maximize the area covered by rectangles
in a 2-row grid. It processes rectangles left to right and for each rectangle,
it determines the maximum valid subrectangle that can be placed without overlapping
previous rectangles. It uses an array `now` to track the rightmost boundary of
each row that has been placed so far.

The algorithm:
1. Sort rectangles by left x-coordinate
2. For each rectangle in order:
   - Adjust the rectangle's left coordinate to avoid overlap with previous placement
   - Update the row boundaries to reflect the new placement
3. Calculate final area and output all rectangles with their new coordinates
*/

#include <algorithm>
#include <iostream>

using namespace std;
int T, n, ans;
struct xx {
  int r, id;
} now[3]; // Tracks rightmost x-coordinate for each row (1-indexed)
struct node {
  int x1, y1, x2, y2;
  int id;
} a[200005];
bool cmp(node x, node y) { return x.x1 < y.x1; } // Sort by left x-coordinate
bool idd(node x, node y) { return x.id < y.id; } // Sort by original id
int main() {
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].y1 >> a[i].x1 >> a[i].y2 >> a[i].x2;
      a[i].id = i;
    }
    sort(a + 1, a + n + 1, cmp); // Sort rectangles by left x-coordinate
    now[1].r = now[2].r = 0; // Initialize row boundaries
    for (int i = 1; i <= n; i++) {
      // Adjust left boundary to leave space for previous rectangles
      a[i].x1 = max(a[i].x1, min(now[1].r, now[2].r) + 1);
      // Adjust top row if completely covered by a previous rectangle in row 1
      if (a[i].x2 <= now[1].r)
        a[i].y1 = 2;
      // Adjust bottom row if completely covered by a previous rectangle in row 2
      if (a[i].x2 <= now[2].r)
        a[i].y2 = 1;
      // Skip if no valid area remains after adjustment
      if (a[i].x1 > a[i].x2 || a[i].y1 > a[i].y2)
        continue;
      // For each row in the rectangle, update the boundary and mark overlap
      for (int j = a[i].y1; j <= a[i].y2; j++) {
        if (now[j].r >= a[i].x1) // If there's overlap in row j
          a[now[j].id].x2 = a[i].x1 - 1; // Shrink previous rectangle in row j
        now[j].r = a[i].x2, now[j].id = i; // Update boundary to new rectangle's end
      }
    }
    ans = 0;
    for (int i = 1; i <= n; i++) {
      // If rectangle has no valid area, mark it as removed
      if (a[i].x1 > a[i].x2 || a[i].y1 > a[i].y2) {
        a[i].x1 = a[i].x2 = a[i].y1 = a[i].y2 = 0;
        continue;
      }
      // Add area to total
      ans += (a[i].x2 - a[i].x1 + 1) * (a[i].y2 - a[i].y1 + 1);
    }
    cout << ans << endl;
    sort(a + 1, a + n + 1, idd); // Re-sort to original order
    for (int i = 1; i <= n; i++) {
      cout << a[i].y1 << ' ' << a[i].x1 << ' ' << a[i].y2 << ' ' << a[i].x2
           << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/