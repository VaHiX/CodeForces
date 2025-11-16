// Problem: CF 889 A - Petya and Catacombs
// https://codeforces.com/contest/889/problem/A

/*
 * Problem: Petya and Catacombs
 * Purpose: Determine the minimum number of rooms in the catacombs based on Petya's logbook.
 * 
 * Approach:
 * - We simulate the process of visiting rooms and tracking when each room was last visited.
 * - For each note t[i], if we have not seen this value before (i.e., b[t[i]] is 0), 
 *   we mark it as visited. Otherwise, it means we are reusing a previously visited room,
 *   so we increment the total room count (ans).
 * - This greedy approach works because if a room number t[i] appears for the second time,
 *   it indicates that we must have used at least one more room than previously assumed.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
int n, ans, a[200010], b[200010];
int main() {
  scanf("%d", &n);
  ans = 1;  // At least one room is needed
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) {
    if (!b[a[i]]) {
      b[a[i]] = 1;  // Mark the room number as visited
    } else
      ans++;  // A new room is required since we've seen this number before
  }
  printf("%d\n", ans);
}


// https://github.com/VaHiX/CodeForces/