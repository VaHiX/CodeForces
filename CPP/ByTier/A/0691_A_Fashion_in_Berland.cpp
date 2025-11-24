// Problem: CF 691 A - Fashion in Berland
// https://codeforces.com/contest/691/problem/A

/*
 * Problem: Fashion in Berland
 * 
 * Algorithm/Techniques: Simulation
 * 
 * Time Complexity: O(n), where n is the number of buttons.
 * Space Complexity: O(1), only using a constant amount of extra space.
 * 
 * Description:
 * A jacket is considered properly fastened if:
 * - If there is only 1 button, it must be fastened (value = 1).
 * - If there are more than 1 button, exactly one button should be unfastened (value = 0),
 *   and all others should be fastened (value = 1).
 * 
 * The solution counts how many buttons are unfastened (0s). For valid fastening:
 * - If n == 1, exactly 0 unfastened buttons (i.e., the button should be fastened).
 * - If n > 1, exactly 1 unfastened button (i.e., one button is unfastened and the rest are fastened).
 */

#include <cstdio>
int main() {
  int n;
  scanf("%d\n", &n);
  bool one(0);  // Tracks if we've seen an unfastened button (0) so far
  for (int p = 0; p < n; p++) {
    int x;
    scanf("%d", &x);
    if (x == 1) {
      continue;  // If button is fastened, skip it
    }
    if (one == 0) {
      one = 1;   // First unfastened button encountered
    } else {
      one = 0;   // Second unfastened button found => invalid
      break;
    }
  }
  // Check if fastening is valid based on number of buttons and unfastened buttons
  puts(((n == 1 && one == 0) || (n > 1 && one == 1)) ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/