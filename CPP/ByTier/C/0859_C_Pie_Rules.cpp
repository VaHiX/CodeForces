// Problem: CF 859 C - Pie Rules
// https://codeforces.com/contest/859/problem/C

/*
Algorithm: Game Theory / Dynamic Programming on Choices
Approach: This is a classic game theory problem where two players (Alice and Bob) take turns choosing slices of pie. The player with the "decider" token decides who gets the next slice. Since both players play optimally, we simulate the process by always giving the current slice to the player who will benefit more in the long run — i.e., who will end up with a higher total if the game continues optimally from that point.

Time Complexity: O(N) - We iterate through the slices once to process them.
Space Complexity: O(N) - We store the slice sizes in an array of size N.

Techniques Used:
- Greedy choice based on future benefit (optimal substructure)
- Simulated game play with token passing logic
*/

#include <cstdio>
int x[55], n, i = 1, a, b;
int main() {
  scanf("%d", &n);
  while (i++ <= n)
    scanf("%d", x + i);
  while (i--) {
    // At each step, decide who gets the current slice based on who benefits more in the end
    a > b ? b += x[i] : a += x[i];
  }
  // Output the results: smaller total first, then larger total
  printf("%d %d", a < b ? a : b, a < b ? b : a);
}


// https://github.com/VaHiX/CodeForces/