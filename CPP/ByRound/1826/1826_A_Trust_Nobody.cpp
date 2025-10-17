// Problem: CF 1826 A - Trust Nobody
// https://codeforces.com/contest/1826/problem/A

/*
 * Problem: Trust Nobody
 * 
 * Description:
 * There are n people in a group. Each person says "There are at least l_i liars amongst us".
 * Determine if the statements are contradictory, or if it's possible to assign truth-tellers and liars
 * such that all statements are consistent. If possible, output the number of liars.
 * 
 * Algorithm:
 * - For each candidate number of liars (from 0 to n), check if it's a valid solution.
 * - A number k of liars is valid if:
 *   - The count of people who claim there are at least k liars matches exactly the number of truth-tellers.
 *   - That is, the number of people whose l_i <= k equals the number of liars (k).
 * 
 * Time Complexity: O(n^2), as for each test case we iterate up to n times for validation.
 * Space Complexity: O(n), to store the count array of size n + 1.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int t;
int n, cnt[110]; // cnt[i] counts how many people said "at least i liars"
int main() {
  for (cin >> t; t--;) {
    cin >> n;
    fill(cnt, cnt + n + 1, 0); // Initialize count array to zero
    for (int i = 1, x; i <= n; i++)
      scanf("%d", &x), cnt[x]++; // Count how many people said "at least x liars"
    
    int ans = -1;
    for (int i = 0, s = 0; i <= n; i++) {
      s += cnt[i]; // Accumulate the number of people who claimed at least i liars
      if (i == n - s) // If i equals number of truth-tellers, then i is a valid number of liars
        ans = i;
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/