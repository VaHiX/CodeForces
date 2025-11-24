// Problem: CF 1455 C - Ping-pong
// https://codeforces.com/contest/1455/problem/C

/*
C. Ping-pong

Algorithm:
This problem involves simulating a ping-pong game where Alice and Bob play optimally. 
Each player spends 1 stamina per hit (serve or return). When a player runs out of stamina,
they lose the current play and cannot continue. The winner of each play serves next.
Both players play optimally to maximize their own wins and minimize the opponent's.

Approach:
- We simulate the game for each test case.
- Each round, the current server (Alice or Bob) hits once (spends 1 stamina).
- If the receiver has stamina, they return (spend 1 stamina). Otherwise, they lose.
- If both players run out of stamina, the game ends.
- Optimal strategy: When a player can't return but has enough stamina to serve next, 
  they don't return (lose the play, save stamina) — this is optimal to preserve stamina.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input:
t (number of test cases), followed by t lines with x (Alice's stamina) and y (Bob's stamina).

Output:
For each test case, print two integers - Alice's wins and Bob's wins.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    printf("%ld %ld\n", x - 1, y); // x-1 for Alice's wins, y for Bob's wins
  }
}


// https://github.com/VaHiX/codeForces/