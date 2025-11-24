// Problem: CF 1932 D - Card Game
// https://codeforces.com/contest/1932/problem/D

/*
Code Purpose:
This code solves the problem of reconstructing possible sequences of card plays in a card game where trump suit is defined, and cards are matched based on suit and rank rules. The algorithm groups cards by suit, sorts them, and attempts to pair them to form valid moves according to the game's rules.

Algorithms/Techniques:
- Grouping and sorting cards by suit
- Greedy pairing strategy
- Validation of trump suit handling and match validity

Time Complexity: O(n log n) per test case due to sorting operations
Space Complexity: O(n) for storing and manipulating card collections
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
#define pii pair<int, int>
#define mk make_pair
#define f first
#define s second
#define eb emplace_back

void solve() {
  int n, m;
  cin >> n;
  char ar[4] = {'C', 'D', 'H', 'S'}, ch;
  cin >> ch;
  for (int i = 0; i < 4; i++) {
    if (ch == ar[i]) {
      m = i;
      break;
    }
  }
  vector<char> v1[4]; // v1[i] stores ranks of cards with suit ar[i]
  for (int i = 0; i < 2 * n; i++) {
    string s1;
    cin >> s1;
    for (int j = 0; j < 4; j++) {
      if (s1[1] == ar[j]) {
        v1[j].push_back(s1[0]); // Store the rank of the card
        break;
      }
    }
  }
  // Sort ranks within each suit
  for (int i = 0; i < 4; i++) {
    sort(v1[i].begin(), v1[i].end());
  }
  int cur = 0; // Tracks the index in trump suit for pairing non-trump cards
  vector<pair<string, string>> ans; // Stores the pairs of moves

  // Process non-trump suits
  for (int i = 0; i < 4; i++) {
    if (i == m) {
      continue; // Skip the trump suit for now
    }
    // Pair up even number of cards from this suit
    for (int j = 0; j < (v1[i].size() / 2) * 2; j += 2) {
      string s1 = "", s2 = "";
      s1 += v1[i][j];
      s1 += ar[i];  // Create string of first card
      s2 += v1[i][j + 1];
      s2 += ar[i];  // Create string of second card
      ans.push_back(make_pair(s1, s2));
    }
    // If an odd number of cards remain, try to pair with trump card
    if (v1[i].size() % 2 != 0 && cur >= v1[m].size()) {
      cout << "IMPOSSIBLE\n";
      return;
    } else if (v1[i].size() % 2 != 0) {
      string s1 = "", s2 = "";
      s1 += v1[i][v1[i].size() - 1];  // Last card in non-trump suit
      s1 += ar[i];
      s2 += v1[m][cur];  // Next trump card
      cur++;
      s2 += ar[m];  // Make it trump suit
      ans.push_back(make_pair(s1, s2));
    }
  }

  // Handle any remaining trump cards
  if ((v1[m].size() - cur) % 2 != 0) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  // Pair remaining trump cards
  for (int j = cur; j < v1[m].size(); j += 2) {
    string s1 = "", s2 = "";
    s1 += v1[m][j];
    s1 += ar[m];
    s2 += v1[m][j + 1];
    s2 += ar[m];
    ans.push_back(make_pair(s1, s2));
  }

  for (auto &x : ans) {
    cout << x.first << " " << x.second << "\n";
  }
}

signed main() {
  cin.tie(0);
  cin.sync_with_stdio(0);
  int t = 1;
  cin >> t;
  for (int i = 0; i < t; i++) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/