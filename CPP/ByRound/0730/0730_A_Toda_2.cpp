// Problem: CF 730 A - Toda 2
// https://codeforces.com/contest/730/problem/A

/*
Purpose: This code solves the problem of equalizing the ratings of n friends in the video game Toda 2 by strategically losing matches. 
         The goal is to maximize the final equal rating while minimizing the number of matches needed.

Algorithms/Techniques:
- Greedy approach: Always reduce the highest-rated players to match the second-highest.
- Sorting: To efficiently find the highest-rated players.
- Simulation: Simulate match outcomes and adjust ratings accordingly.

Time Complexity: O(n^2 * log(n) + t * n) where t is the number of matches, dominated by sorting operations and iterations.
Space Complexity: O(t * n) to store the match details, where t is the number of matches.
*/

#include <algorithm>
#include <iostream>

using namespace std;

struct num {
  int x, id;
  operator int() const { return x; }
} r[201]; // Array to store ratings and their original indices

int n, f[20001][201]; // n: number of friends, f: matrix to store match participation

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> r[i].x, r[i].id = i; // Read ratings and store original indices
  sort(r, r + n); // Sort the ratings in ascending order
  
  int ans = 0; // Initialize match count
  for (; r[0].x != r[n - 1].x; ans++) { // Continue until all ratings are equal
    int c = 0;
    for (int i = n - 1; i >= 0; i--)
      if (r[i].x == r[n - 1].x) // Count how many players have the highest rating
        c++;
    
    if (c == 1) // If only one player has the highest rating, we need at least 2 to form a match
      c = 2;
    if (c > 5) // If more than 5 players have the highest rating, limit to 5 (max party size)
      c = min(5, c - 2); // Subtract 2 to prioritize the highest-rated players while respecting match constraints
    
    for (int i = n - 1; i >= n - c; i--) { // Reduce the ratings of c highest-rated players
      if (r[i].x) // Ensure rating doesn't go below 0
        r[i].x--;
      f[ans][r[i].id] = 1; // Mark these players as participating in match 'ans'
    }
    sort(r, r + n); // Re-sort to bring the new highest ratings to the end
  }
  
  cout << r[0].x << '\n' << ans << '\n'; // Output final equal rating and number of matches
  for (int i = 0; i < ans; i++, cout << '\n') // Output each match's player participation
    for (int j = 0; j < n; j++)
      cout << f[i][j];
}


// https://github.com/VaHiX/CodeForces/