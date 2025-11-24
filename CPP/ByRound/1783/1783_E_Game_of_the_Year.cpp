// Problem: CF 1783 E - Game of the Year
// https://codeforces.com/contest/1783/problem/E

/*
Purpose: 
  This code determines for how many values of k (from 1 to n), Monocarp will kill all bosses in a game where players take turns making attempts to kill bosses.
  The key idea is to compute a difference array that indicates when each boss is killed by Monocarp or Polycarp, and then checks for valid k values by verifying
  that for a given k, the pattern of kills repeats every k steps. 

Algorithms/Techniques:
  - Difference Array technique to track which player kills a boss at each attempt
  - Prefix sum to aggregate the differences into a cumulative count
  - Brute-force check over all possible k from 1 to n, but optimized using the prefix sum and difference array logic

Time Complexity: O(n^2) in worst case due to checking all k values, although optimized with prefix sum preprocessing.
Space Complexity: O(n) for storing arrays s, a, b, and ans.
*/

#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
int T, n, ans[200010], top, s[200010], a[200010], b[200010];

// Function to check if a given k is valid:
// it ensures that the kill pattern (Monocarp vs Polycarp) is consistent
// across all boss groups of size k.
bool check(int x) {
  for (int i = x; i <= n; i += x)
    if (s[i] != s[i - x]) // Compare prefix sums to check if the pattern repeats
      return 0;
  return 1;
}

int main() {
  for (scanf("%d", &T); T--;) {
    scanf("%d", &n), memset(s, 0, (n + 1) << 2), top = 0;
    // Read Monocarp's kill attempts
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    // Read Polycarp's kill attempts and build difference array s
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &b[i]);
      if (a[i] > b[i])
        ++s[b[i]], --s[a[i]]; // Update difference array: +1 at b[i], -1 at a[i]
    }
    // Compute prefix sum of difference array to get cumulative counts
    for (int i = 1; i <= n; ++i)
      s[i] += s[i - 1];
    // Check all k values from 1 to n for validity
    for (int i = 1; i <= n; ++i)
      if (check(i))
        ans[++top] = i;
    printf("%d\n", top);
    for (int i = 1; i <= top; ++i)
      printf("%d ", ans[i]);
    putchar('\n');
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/