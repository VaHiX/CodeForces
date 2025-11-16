// Problem: CF 1102 B - Array K-Coloring
// https://codeforces.com/contest/1102/problem/B

/*
Algorithm/Technique: Greedy coloring with sorting
Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing the array of elements

This solution uses a greedy approach to assign colors to elements in the array:
1. It groups elements by their value (using sorting by value)
2. For each group of identical elements, it assigns colors in a round-robin fashion
3. It ensures that each color is used at least once and that no color is used more than once per group
4. If any group has more elements than available colors, it's impossible to color the array
*/

#include <algorithm>
#include <cstdio>
#include <vector>
struct elem {
  long r, x, c;  // r: original index, x: value, c: color
};
bool compA(elem a, elem b) { return a.r < b.r; }  // Comparator for restoring original order
bool compB(elem a, elem b) { return a.x < b.x; }  // Comparator for sorting by value
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<elem> a(n);
  for (long p = 0; p < n; p++) {
    a[p].r = p;           // Store original index
    scanf("%ld", &a[p].x); // Read the value
    a[p].c = -1;          // Initialize color as unassigned
  }
  sort(a.begin(), a.end(), compB);  // Sort by value to group identical elements
  long col(0), cnt(0);              // col: current color index, cnt: count of current value
  bool all(false), possible(true);  // all: if all colors used at least once, possible: if solution exists
  for (long p = 0; p < n; p++) {
    if (p > 0 && a[p - 1].x != a[p].x) {  // If we are moving to a new value
      if (cnt > k) {                      // If the previous group had more elements than colors, impossible
        possible = false;
        break;
      }
      cnt = 0;  // Reset counter for new group
    }
    ++cnt;                  // Increment count of current value
    a[p].c = col + 1;       // Assign current color (1-indexed)
    col++;                  // Move to next color
    if (col >= k) {         // If we've used all colors, reset to start
      all = true;
      col = 0;
    }
  }
  if (!all || cnt > k) {  // If not all colors used or last group too large
    possible = false;
  }
  sort(a.begin(), a.end(), compA);  // Restore original order
  if (possible) {
    puts("YES");
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p].c);
    }
    puts("");
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/