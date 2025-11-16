// Problem: CF 1970 F2 - Playing Quidditch (Medium)
// https://codeforces.com/contest/1970/problem/F2

/*
 * Problem: F2. Playing Quidditch (Medium)
 * 
 * Purpose:
 * This program simulates a Quidditch game between two teams (Red Gryffindor and Blue Ravenclaw).
 * It tracks player movements, ball handling, scoring, and eliminations according to the game rules.
 * 
 * Algorithms/Techniques:
 * - Grid simulation with movement tracking
 * - State management for players and balls
 * - Collision detection for player-bludger encounters
 * - Goal scoring detection
 * - Event logging with time-stamped outputs
 * 
 * Time Complexity: O(T * (N * M + P)) where T is number of steps, N and M are grid dimensions, P is number of players
 * Space Complexity: O(N * M + P) for storing grid state and player positions
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;
typedef pair<int, int> ppr;

// Helper function to check if a player is already eliminated
bool notFound(vector<string> cemetry, string s) {
  for (int i = 0; i < cemetry.size(); i++) {
    if (cemetry[i] == s)
      return false;
  }
  return true;
}

int main() {
  int n, m, t, red = 0, blue = 0;
  cin >> n >> m;
  vector<string> cemetry; // Stores eliminated players
  vector<vector<string>> a(n, vector<string>(m)); // Grid representation
  vector<ppr> rp(10, ppr(0, 0)); // Red team player positions
  vector<ppr> bp(10, ppr(0, 0)); // Blue team player positions
  vector<ppr> rg; // Red goals
  vector<ppr> bg; // Blue goals
  ppr q, b = ppr(0, 0); // Quaffle and Bludger positions
  string qp = ""; // Player carrying the Quaffle
  
  // Read the initial grid state
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      if (a[i][j][1] == 'Q') // Quaffle
        q = ppr(i + 1, j + 1);
      else if (a[i][j][1] == 'B') // Bludger
        b = ppr(i + 1, j + 1);
      else if (a[i][j] == "RG") // Red goal
        rg.push_back(ppr(i + 1, j + 1));
      else if (a[i][j] == "BG") // Blue goal
        bg.push_back(ppr(i + 1, j + 1));
      else if (a[i][j][0] == 'R') { // Red player
        char ch = a[i][j][1];
        rp[ch - '0'] = ppr(i + 1, j + 1);
      } else if (a[i][j][0] == 'B') { // Blue player
        char ch = a[i][j][1];
        bp[ch - '0'] = ppr(i + 1, j + 1);
      }
    }
  
  cin >> t; // Number of steps

  // Process each step
  for (int i = 0; i < t; i++) {
    string player, op, ball = "";
    cin >> player >> op;
    if (op == "C") {
      cin >> ball;
      qp = player; // Update which player carries the ball
    }
    
    // Handle Blue player movements
    if (player[0] == 'B') {
      char ch = player[1];
      if (op == "U")
        bp[ch - '0'].first--; // Move up
      if (op == "D")
        bp[ch - '0'].first++; // Move down
      if (op == "R")
        bp[ch - '0'].second++; // Move right
      if (op == "L")
        bp[ch - '0'].second--; // Move left
        
      if (op == "T") { // Throw the Quaffle
        for (int j = 0; j < bg.size(); j++) {
          if (bp[ch - '0'] == bg[j]) { // Score in blue goal
            cout << i << " RED GOAL" << endl;
            red++;
            break;
          }
        }
        for (int j = 0; j < rg.size(); j++) {
          if (bp[ch - '0'] == rg[j]) { // Score in red goal
            cout << i << " BLUE GOAL" << endl;
            blue++;
            break;
          }
        }
        qp = ""; // No one carries the quaffle now
        q = ppr((n + 1) / 2, (m + 1) / 2); // Reset quaffle to center
      }
      
      // Check if player is eliminated by bludger
      if (bp[ch - '0'] == b) {
        cout << i << " " << player << " ELIMINATED" << endl;
        cemetry.push_back(player);
      }
    }
    // Handle Bludger movements (special case)
    else if (player[1] == 'B') { // Bludger moves
      if (op == "U")
        b.first--;
      if (op == "D")
        b.first++;
      if (op == "R")
        b.second++;
      if (op == "L")
        b.second--;
      
      // Check collisions with players
      for (int j = 0; j < 10; j++) {
        if (bp[j] != ppr(0, 0) && b == bp[j] &&
            notFound(cemetry, "B" + to_string(j))) { // Blue player hit
          cout << i << " " << "B" << j << " ELIMINATED" << endl;
          cemetry.push_back("B" + to_string(j));
        }
      }
      for (int j = 0; j < 10; j++) {
        if (rp[j] != ppr(0, 0) && b == rp[j] &&
            notFound(cemetry, "R" + to_string(j))) { // Red player hit
          cout << i << " " << "R" << j << " ELIMINATED" << endl;
          cemetry.push_back("R" + to_string(j));
        }
      }
    }
    // Handle Red player movements
    else if (player[0] == 'R') {
      char ch = player[1];
      if (op == "U")
        rp[ch - '0'].first--;
      if (op == "D")
        rp[ch - '0'].first++;
      if (op == "R")
        rp[ch - '0'].second++;
      if (op == "L")
        rp[ch - '0'].second--;
        
      if (op == "T") { // Throw the Quaffle
        for (int j = 0; j < bg.size(); j++) {
          if (rp[ch - '0'] == bg[j]) { // Score in blue goal
            cout << i << " RED GOAL" << endl;
            red++;
            break;
          }
        }
        for (int j = 0; j < rg.size(); j++) {
          if (rp[ch - '0'] == rg[j]) { // Score in red goal
            cout << i << " BLUE GOAL" << endl;
            blue++;
            break;
          }
        }
        qp = ""; // No one carries the quaffle now
        q = ppr((n + 1) / 2, (m + 1) / 2); // Reset quaffle to center
      }
      
      // Check if player is eliminated by bludger
      if (rp[ch - '0'] == b) {
        cout << i << " " << player << " ELIMINATED" << endl;
        cemetry.push_back(player);
      }
    }
  }
  
  // Output final score
  cout << "FINAL SCORE: " << red << " " << blue;
  return 0;
}


// https://github.com/VaHiX/CodeForces/