// Problem: CF 519 C - A and B and Team Training
// https://codeforces.com/contest/519/problem/C

/*
 * Problem: C. A and B and Team Training
 * 
 * Purpose: To determine the maximum number of teams that can be formed 
 *          from n experienced participants and m newbies, where each team 
 *          is either:
 *          - One experienced member and two newbies (1 XP, 2 NB), or
 *          - Two experienced members and one newbie (2 XP, 1 NB).
 * 
 * Algorithm: 
 *   - Enumerate over all possible numbers of the first type of team (1 XP + 2 NB)
 *   - For each such number p:
 *     - Deduct the required XP and NB for these p teams
 *     - Calculate the maximum number of second type teams that can be formed
 *     - Total teams = p + (remaining XP - p) / 2 + (remaining NB - 2 * p)
 *   - Since we want to maximize total teams, we try all valid p values.
 * 
 * Time Complexity: O(n) where n is the number of experienced members
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>

int main() {
  long a, b;
  std::cin >> a >> b;
  // Ensure a <= b for simplicity
  if (b < a) {
    long temp = a;
    a = b;
    b = temp;
  }
  long ans(0);
  // p represents number of teams of type (1 XP, 2 NB)
  for (int p = 0; p <= a && 2 * p <= b; p++) {
    // Calculate max teams we can form with this p
    long test = p + std::min(b - 2 * p, (a - p) / 2);
    if (test > ans) {
      ans = test;
    }
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/