// Problem: CF 1722 C - Word Game
// https://codeforces.com/contest/1722/problem/C

/*
C. Word Game
Algorithm: For each test case, we maintain a vector of sets to store words written by each player.
We count how many players have written each word and award points based on the count:
- 0 players (unique): 3 points
- 1 player (shared): 1 point
- 2 players (common): 0 points

Time Complexity: O(N * M) where N is number of words per player and M is number of test cases
Space Complexity: O(N * M) for storing all the words in sets

*/
#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  const int N = 3;
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::set<std::string>> v(N); // Store words for each of the 3 players
    for (long p = 0; p < N; p++) {
      for (long q = 0; q < n; q++) {
        std::string s;
        std::cin >> s;
        v[p].insert(s); // Insert word into set for player p
      }
    }
    std::vector<long> score(N, 0); // Initialize scores for each player to 0
    for (long p = 0; p < N; p++) {
      for (std::set<std::string>::iterator it = v[p].begin(); it != v[p].end();
           it++) {
        std::string x = *it; // Get current word
        long cnt(0);
        for (long q = 0; q < N; q++) {
          if (q == p) {
            continue; // Skip self counting
          }
          cnt += v[q].count(x); // Count how many other players have this word
        }
        if (cnt == 0) {
          score[p] += 3; // Word unique to this player
        } else if (cnt == 1) {
          score[p] += 1; // Word shared with one other player
        }
        // cnt >= 2 => no points (word shared by two or more players)
      }
    }
    for (long p = 0; p < N; p++) {
      std::cout << score[p] << " "; // Output scores for each player
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/