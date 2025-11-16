// Problem: CF 893 A - Chess For Three
// https://codeforces.com/contest/893/problem/A

/*
 * Purpose: Determine if a sequence of chess game winners is valid according to the tournament rules.
 *          In each game, two players compete and one becomes spectator for the next game.
 *          The spectator in the current game becomes a player in the next game, and the loser becomes
 *          the new spectator.
 *
 * Algorithm: Simulate the game sequence.
 *            - Use an array `play` to represent who is playing (1) or spectating (0) at any time.
 *            - Initially, Alex (1) and Bob (2) play, Carl (3) is spectator.
 *            - For each game winner, check if that player is currently playing.
 *            - If valid, update the playing/spectating status for next game.
 *
 * Time Complexity: O(n), where n is the number of games.
 * Space Complexity: O(1), as we use a fixed-size array of size 4.
 */

#include <cstdio>
int main() {
  int play[4] = {0};  // play[i] = 1 if player i is playing, 0 if spectating
  play[1] = play[2] = 1;  // Alex and Bob are playing initially, Carl is spectating
  long n;
  scanf("%ld", &n);
  bool res(true);
  for (long p = 0; p < n; p++) {
    int win;
    scanf("%d", &win);
    // Check if the winner is currently playing
    if (!play[win]) {
      res = false;
      break;
    }
    // Switch roles: winner keeps playing, others switch (play -> spectate or vice versa)
    for (int u = 1; u <= 3; u++) {
      if (u == win) {
        continue;  // Winner continues playing
      }
      play[u] = 1 - play[u];  // Toggle playing/spectating status
    }
  }
  puts(res ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/