// Problem: CF 538 C - Tourist's Notes
// https://codeforces.com/contest/538/problem/C

/*
 * Problem: Tourist's Notes
 * Purpose: Determine the maximum possible height during a hike given constraints
 *          that consecutive days' heights differ by at most 1, and some notes
 *          may have been lost or distorted.
 * 
 * Approach:
 * - Use the given notes to determine the valid range of possible heights.
 * - For each pair of consecutive notes, check if the difference in height and time
 *   is consistent with the constraint |h[i] - h[i+1]| <= 1.
 * - Compute the maximum possible height by considering the constraints of
 *   the differences between notes and how far we can go from the start or end.
 * 
 * Algorithms:
 *   - Linear scan through notes to validate constraints and compute maximum height.
 * 
 * Time Complexity: O(m), where m is the number of notes.
 * Space Complexity: O(m), to store the notes.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld\n", &n, &m);
  std::vector<long> day(m);
  std::vector<long> height(m);
  for (int p = 0; p < m; p++) {
    long d, h;
    scanf("%ld %ld\n", &d, &h);
    day[p] = d;
    height[p] = h;
  }
  bool possible(1);
  // Calculate the maximum possible height based on the first note
  long ans = height[0] + (day[0] - 1);
  // Calculate the maximum possible height based on the last note
  long final = height[m - 1] + (n - day[m - 1]);
  if (final > ans) {
    ans = final;
  }
  for (int p = 1; p < m; p++) {
    long timeDiff = day[p] - day[p - 1];
    long heightDiff = height[p] - height[p - 1];
    long absDiff = (heightDiff > 0) ? heightDiff : -heightDiff;
    // If time difference is less than the height difference, it's impossible
    if (timeDiff < absDiff) {
      possible = 0;
      break;
    }
    // Compute the maximum possible height between the two notes
    long candidate = (timeDiff + height[p] + height[p - 1]) / 2;
    if (candidate > ans) {
      ans = candidate;
    }
  }
  if (possible) {
    printf("%ld\n", ans);
  } else {
    puts("IMPOSSIBLE");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/