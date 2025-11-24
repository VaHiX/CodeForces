// Problem: CF 765 A - Neverending competitions
// https://codeforces.com/contest/765/problem/A

/*
 * Problem: Determine if Jinotega is at home or at a contest based on the number of flights.
 *
 * Algorithm/Techniques:
 *   - The key insight is that each competition consists of two flights: 
 *     one to the contest and one back home.
 *   - If the total number of flights is even, Jinotega has completed an even number 
 *     of round-trips and is currently at home.
 *   - If the number of flights is odd, Jinotega is in the middle of a trip 
 *     (either going to a contest or returning), so they are at a contest.
 *
 * Time Complexity: O(1) - Only a single read and conditional check.
 * Space Complexity: O(1) - No extra space used beyond input variables.
 */

#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);  // Read the number of flights
  puts((n % 2) ? "contest" : "home");  // If odd number of flights, at contest; else at home
  return 0;
}


// https://github.com/VaHiX/CodeForces/