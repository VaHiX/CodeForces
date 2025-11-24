// Problem: CF 1008 B - Turn the Rectangles
// https://codeforces.com/contest/1008/problem/B

/*
B. Turn the Rectangles
Algorithm: Greedy approach
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks whether we can arrange n rectangles in non-ascending order of height 
by optionally rotating each rectangle (90 degrees). Each rectangle has two possible 
orientations: (width, height) or (height, width). 

We process the rectangles from left to right. For each rectangle, we try to choose 
the orientation that allows us to maintain a non-ascending sequence in terms of height.

For the first rectangle, we can take either orientation (we pick the one with maximum height).
Then for each subsequent rectangle, we check if we can keep the current height 
(keeping it non-ascending) by choosing an appropriate orientation.

If at any point we cannot maintain the constraint, answer is "NO".
*/

#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, long>> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld %ld", &a[p].first, &a[p].second);
  }
  // Initialize current maximum height with the larger of the two dimensions of the first rectangle
  long cur(a[0].first > a[0].second ? a[0].first : a[0].second);
  bool possible(true);
  for (long p = 1; p < n; p++) {
    // u is the maximum possible height if we keep the rectangle as is
    long u = a[p].first > a[p].second ? a[p].first : a[p].second;
    // v is the minimum possible height if we rotate the rectangle
    long v = a[p].first < a[p].second ? a[p].first : a[p].second;
    // If current max height allows us to use u as new height (keep sequence non-ascending)
    if (cur >= u) {
      cur = u;
    } else if (cur >= v) {
      // Otherwise, if we can use v as new height
      cur = v;
    } else {
      // If neither orientation works, it's impossible
      possible = false;
      break;
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/codeForces/