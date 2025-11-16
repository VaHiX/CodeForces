// Problem: CF 1769 D1 - Игра в Девятку I
// https://codeforces.com/contest/1769/problem/D1

/*
 * Task: Determine the winner of a card game "Nine" between Alice and Bob.
 * 
 * Game Rules:
 * - Each player has 18 cards from a 36-card deck (9 ranks: 6,7,8,9,T,J,Q,K,A; 4 suits: C,D,S,H)
 * - Players alternate turns, Alice starts first
 * - A card can be played if:
 *   - It's a 9 (any suit) - always playable
 *   - It's a 6,7,8 - playable if the next higher rank of same suit is already on the table
 *   - It's a T,J,Q,K,A - playable if the previous lower rank of same suit is already on the table
 * - If a player cannot play any card, they pass turn to opponent
 * 
 * Approach:
 * - Use minimax with memoization to determine optimal play
 * - State: current set of played cards (bitmask), whose turn it is
 * - For each state, check if current player can win by playing some valid card
 * - If no valid moves exist, opponent wins
 * 
 * Time Complexity: O(2^36 * 18) due to 2^36 possible card combinations and up to 18 cards per player
 * Space Complexity: O(2^36) for memoization table
 * 
 * Algorithms/Techniques: Minimax with memoization (Dynamic Programming)
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
map<char, int> num;
vector<int> mp[2];                    // Stores cards for Alice (0) and Bob (1)
map<long long, bool> dp[2];          // Memoization table for game states
bool dfs(long long s, int op) {       // s: bitmask of played cards, op: whose turn (0 for Alice, 1 for Bob)
  if (dp[op][s])                      // If state already computed
    return dp[op][s];
  int cnt = 0, cnt2 = 0;              // cnt: total cards in hand, cnt2: playable cards
  for (int i = 0; i < mp[op].size(); i++) {  // Check all cards in current player's hand
    int x = mp[op][i];                // x: card value encoded as 9*suit + rank
    if (s & (1ll << x))               // Skip if already played
      continue;
    cnt++;                            // Count total cards
    // Check if card is playable
    if (x % 9 == 3 || x % 9 < 3 && (s & (1ll << (x + 1))) || x % 9 > 3 && (s & (1ll << (x - 1))))
      cnt2++;                         // Count playable cards
  }
  if (!cnt)                           // No cards left, current player already won
    return dp[op][s] = true;
  if (!cnt2)                          // No playable cards, opponent wins next turn
    return dp[op][s] = !dfs(s, !op);
  for (int i = 0; i < mp[op].size(); i++) {  // Try all playable cards
    int x = mp[op][i];
    if (s & (1ll << x))               // Skip if already played
      continue;
    if (x % 9 == 3 || x % 9 < 3 && (s & (1ll << (x + 1))) || x % 9 > 3 && (s & (1ll << (x - 1))))
      // Play card x and check if opponent loses from new state
      dp[op][s] |= !dfs(s | (1ll << x), !op);
  }
  return dp[op][s];
}
int main() {
  num['D'] = 0, num['S'] = 1, num['H'] = 2, num['C'] = 3;  // Suit mapping
  num['6'] = 0, num['7'] = 1, num['8'] = 2, num['9'] = 3, num['T'] = 4,  // Rank mapping
  num['J'] = 5, num['Q'] = 6, num['K'] = 7, num['A'] = 8;
  
  for (int i = 1; i <= 18; i++) {     // Read Alice's cards
    string s;
    cin >> s;
    mp[0].push_back(9 * num[s[1]] + num[s[0]]);  // Encode card as 9*suit + rank
  }
  for (int i = 1; i <= 18; i++) {     // Read Bob's cards
    string s;
    cin >> s;
    mp[1].push_back(9 * num[s[1]] + num[s[0]]);  // Encode card as 9*suit + rank
  }
  
  if (dfs(0, 0))                      // Start from empty state, Alice's turn
    puts("Alice");
  else
    puts("Bob");
  return 0;
}


// https://github.com/VaHiX/CodeForces/