// Problem: CF 514 B - Han Solo and Lazer Gun
// https://codeforces.com/contest/514/problem/B

/*
 * Problem: Han Solo and Lazer Gun
 * 
 * Purpose: Determine the minimum number of shots required to destroy all stormtroopers,
 *          where each shot destroys all stormtroopers lying on a line passing through
 *          the gun's position.
 * 
 * Algorithm: 
 *   1. For each stormtrooper, compute the slope of the line connecting the gun to the
 *      stormtrooper.
 *   2. Store unique slopes in a set to count distinct lines.
 *   3. If any stormtrooper lies directly above or below the gun (vertical line), 
 *      increment the count by 1.
 *   4. Return the total number of unique lines (slopes) plus vertical lines.
 * 
 * Time Complexity: O(n log n) due to the set insertion operations.
 * Space Complexity: O(n) for storing slopes in the set.
 */

#include <cstdio>
#include <set>
int main() {
  long n;
  double a, b;
  scanf("%ld %lf %lf\n", &n, &a, &b);
  std::set<double> slopes; // Store unique slopes of lines through gun and stormtroopers
  bool vertical = 0;       // Flag to check if there is a vertical line (same x-coordinate)
  while (n--) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    if (x == a) {
      // If stormtrooper is on the same vertical line as the gun, mark vertical line
      vertical = 1;
    } else {
      // Calculate slope of line from gun to stormtrooper and insert into set
      slopes.insert((y - b) / (x - a));
    }
  }
  // Output the number of unique lines (slopes) plus 1 if there's a vertical line
  printf("%ld\n", slopes.size() + vertical);
  return 0;
}


// https://github.com/VaHiX/CodeForces/