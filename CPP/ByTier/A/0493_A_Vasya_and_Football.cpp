// Problem: CF 493 A - Vasya and Football
// https://codeforces.com/contest/493/problem/A

/*
 * Purpose: This program determines the first moment in time when players receive red cards during a football match.
 *          It processes a series of fouls and tracks yellow cards to determine when a second yellow card leads to a red card.
 *          The output lists the team name, player number, and time of the first red card per player.
 *
 * Algorithm:
 *   - Use a set to track which players have received a red card to avoid duplicate red card entries.
 *   - Use another set to track players who have received a yellow card.
 *   - For each foul:
 *     - If it's a red card and the player hasn't already received a red card, record the red card event.
 *     - If it's a yellow card and the player hasn't received a yellow card yet, record that they received a yellow card.
 *     - If a player already received a yellow card and the current foul is a yellow card, skip to prevent duplicate yellow cards.
 *   - When a player receives a red card (either directly or from two yellow cards), store the event.
 *   - Output all red card events in chronological order.
 *
 * Time Complexity: O(n log n), where n is the number of fouls. Because operations on sets are logarithmic.
 * Space Complexity: O(n), for storing data about players and events.
 */

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <utility>

int main() {
  const int D = 1000; // Offset to distinguish home and away players
  std::string homeName;
  std::cin >> homeName;
  std::string awayName;
  std::cin >> awayName;
  std::set<int> playerSet; // Tracks players who have received a yellow card
  std::set<int> penaltySet; // Tracks players who have received a red card
  std::vector<std::pair<int, int>> penaltyVec; // Stores {player_number, time} of red cards
  int n;
  std::cin >> n;
  while (n--) {
    int time;
    char team;
    int number;
    char card;
    std::cin >> time >> team >> number >> card;
    if (team == 'a') {
      number += D; // Offset to distinguish away players
    }
    if (penaltySet.find(number) != penaltySet.end()) {
      // Player already received a red card, skip further processing
      continue;
    } else if (card == 'y' && playerSet.find(number) == playerSet.end()) {
      // First yellow card for this player
      playerSet.insert(number);
    } else if (card == 'r' || playerSet.find(number) != playerSet.end()) {
      // Direct red card or second yellow card → red card
      penaltyVec.push_back(std::pair<int, int>(number, time));
      penaltySet.insert(number);
    }
  }
  // Output results in chronological order
  for (int p = 0; p < penaltyVec.size(); p++) {
    std::string teamName = (penaltyVec[p].first < D) ? homeName : awayName;
    int number = (penaltyVec[p].first < D) ? penaltyVec[p].first
                                           : (penaltyVec[p].first - D);
    int time = penaltyVec[p].second;
    std::cout << teamName << " " << number << " " << time << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/