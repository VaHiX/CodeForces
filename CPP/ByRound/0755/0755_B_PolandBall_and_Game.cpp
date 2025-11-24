// Problem: CF 755 B - PolandBall and Game
// https://codeforces.com/contest/755/problem/B

/*
B. PolandBall and Game
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

PolandBall is playing a game with EnemyBall. The rules are simple. Players have to say words in turns. You cannot say a word which was already said. PolandBall starts. The Ball which can't say a new word loses.
You're given two lists of words familiar to PolandBall and EnemyBall. Can you determine who wins the game, if both play optimally?

Algorithm:
- Use two sets to store unique words known by each player.
- Count common words between both players.
- Calculate optimal number of moves for each player based on:
  - Common words can be used by either player, but only one can use a common word per turn.
  - Optimal play implies that each player uses their unique words first, then shared words optimally.
- PolandBall wins if he can make more total turns (u) than EnemyBall (v).

Time Complexity: O(n log n + m log m)
Space Complexity: O(n + m)

*/

#include <iostream>
#include <set>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, m;
  std::cin >> n >> m;
  std::set<std::string> a; // Set to store words known by PolandBall
  std::set<std::string> b; // Set to store words known by EnemyBall
  while (n--) {
    std::string x;
    std::cin >> x;
    a.insert(x); // Insert word into PolandBall's set
  }
  while (m--) {
    std::string y;
    std::cin >> y;
    b.insert(y); // Insert word into EnemyBall's set
  }
  long common(0); // Count of words known by both players
  for (std::set<std::string>::iterator setIter = a.begin(); setIter != a.end();
       setIter++) {
    if (b.count(*setIter) > 0) { // Check if word is in both sets
      ++common;
    }
  }
  // u: number of moves PolandBall can make optimally
  long u = (common + 1) / 2 + (a.size() - common);
  // v: number of moves EnemyBall can make optimally
  long v = (common / 2) + (b.size() - common);
  std::cout << ((u > v) ? "YES" : "NO") << std::endl; // Output result based on turn comparison
  return 0;
}


// https://github.com/VaHiX/codeForces/