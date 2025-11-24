// Problem: CF 478 A - Initial Bet
// https://codeforces.com/contest/478/problem/A

/*
 * Problem: Determine the initial bet 'b' in a game where coins are passed between players.
 * 
 * Approach:
 * - The total number of coins in the game remains constant throughout the game.
 * - Each of the 5 players initially bets 'b' coins, so the total coins at the start is 5 * b.
 * - At the end of the game, the sum of all coins held by players must equal 5 * b.
 * - Therefore, if the sum of coins at the end is divisible by 5 and greater than 0,
 *   then b = sum / 5. Otherwise, it's impossible to have a valid initial bet.
 * 
 * Time Complexity: O(1) - We perform a fixed number of operations (5 reads and 1 division/check).
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <cstdio>
int main() {
  const int n = 5;           // Number of players
  int sum = 0;               // Variable to store the total coins at the end
  for (int p = 0; p < n; p++) {  // Loop through each player
    int temp;
    scanf("%d", &temp);      // Read the number of coins for current player
    sum += temp;             // Add to the total sum
  }
  if (sum > 0 && sum % n == 0) { // Check if sum is positive and divisible by 5
    printf("%d\n", sum / n); // Output the initial bet b
  } else {
    puts("-1");              // No valid initial bet exists
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/