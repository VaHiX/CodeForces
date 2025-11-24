// Problem: CF 1483 A - Basic Diplomacy
// https://codeforces.com/contest/1483/problem/A

/*
 * Problem: Basic Diplomacy
 * Algorithm: Greedy selection with constraint handling
 * Time Complexity: O(m * k), where k is the average number of available friends per day
 * Space Complexity: O(n + m)
 *
 * Approach:
 * - For each day, select a friend from the list of available friends.
 * - Track how many times each friend has been selected.
 * - If any friend is selected more than ceil(m/2) times, we must reassign some of their previous selections.
 * - We use a greedy strategy to reassign such friends' selections to other valid friends.
 */

#include <iosfwd>
#include <stdio.h>
using namespace std;

int c[200000], d[200000], cnt[200000]; // c: chosen friends, d: backup for reassignment, cnt: count of selections

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
      cnt[i] = 0; // Reset selection count for each test case
    int p = 0; // p: friend who exceeds the limit (if any)
    for (int i = 1; i <= m; i++) {
      int k;
      scanf("%d%d", &k, c + i); // Read k (available friends) and first friend
      cnt[c[i]]++; // Increment count of the selected friend
      if (cnt[c[i]] > m + 1 >> 1) // If selected more than ceil(m/2) times
        p = c[i]; // Mark this friend as problematic
      if (k > 1)
        scanf("%d", d + i); // If more than one friend available, read second
      else
        d[i] = 0; // No second friend available
      for (int j = 1; j <= k - 2; j++) { // Skip the rest of friends (no need to store)
        int x;
        scanf("%d", &x);
      }
    }
    int q = 0;
    if (p) {
      q = cnt[p] - (m + 1 >> 1); // Calculate how many times p was overused
      for (int i = 1; i <= m; i++) {
        if (!q) // If no correction needed, stop
          break;
        if (c[i] == p && d[i]) { // Try to reassign p's selection to d[i]
          c[i] = d[i]; // Change the choice
          q--; // Decrease counter
        }
      }
    }
    if (q) // If still overused, impossible
      puts("NO");
    else {
      puts("YES");
      for (int i = 1; i <= m; i++)
        printf("%d ", c[i]);
      putchar('\n');
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/