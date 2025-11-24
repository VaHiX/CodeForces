// Problem: CF 1999 B - Card Game
// https://codeforces.com/contest/1999/problem/B

/*
B. Card Game
	time limit per test2 seconds
	memory limit per test256 megabytes

Algorithms/Techniques: 
    - Enumeration of all possible game outcomes (4 combinations for 2 turns)
    - Comparison function using signum-like logic to determine round winner
    - Mathematical counting of favorable cases based on round results

Time Complexity: O(1) - Fixed number of operations per test case (4 combinations)
Space Complexity: O(1) - Only a constant amount of extra space used

Suneet and Slavic play a card game. The rules of the game are as follows:
Each card has an integer value between 1 and 10.
Each player receives 2 cards which are face-down (so a player doesn't know their cards).
The game is turn-based and consists exactly of two turns. In a round, both players pick a random unflipped card and flip it. The player who flipped a card with a strictly greater number wins the round. In case of equality, no one wins the round.
A player wins a game if he wins the most number of rounds (i.e. strictly greater than the other player). In case of equality, no one wins the game.
Since Suneet and Slavic aren't best friends, you need to calculate the number of ways the game could happen that Suneet would end up as the winner.
*/

#include <cstdio>
int f(int x, int y) { return (x > y) - (x < y); } // Signum function: returns 1 if x>y, -1 if x<y, 0 if x==y
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int a, b, c, d; // Cards of Suneet and Slavic: a,b for Suneet, c,d for Slavic
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int res = 2 * (f(a, c) + f(b, d) > 0) + 2 * (f(a, d) + f(b, c) > 0); // Counting valid scenarios where Suneet wins
    printf("%d\n", res);
  }
}


// https://github.com/VaHiX/codeForces/