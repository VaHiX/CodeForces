// Problem: CF 1970 F1 - Playing Quidditch (Easy)
// https://codeforces.com/contest/1970/problem/F1

/*
Purpose: This code simulates a Quidditch game between two teams (Gryffindor and Ravenclaw) on a rectangular field. 
It tracks player movements, ball carrying, and scoring events based on the rules provided.

Algorithms/Techniques:
- Grid-based simulation using 2D arrays to represent the field
- Tracking of player positions and the Quaffle's position
- State management for which player is carrying the Quaffle
- Goal detection when the Quaffle is placed in a goal

Time Complexity: O(T * N * M) where T is the number of steps, and N, M are the dimensions of the grid.
Space Complexity: O(N * M) for storing the grid and player positions.
*/

#include <stddef.h>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
typedef pair<int, int> pi;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  pi R[10], B[10]; // Arrays to store positions of red and blue players
  string board[n][m]; // 2D grid representing the field
  pi quaff; // Position of the Quaffle
  string catcher = ""; // Tracks which player is currently carrying the Quaffle
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      string s;
      cin >> s;
      if (s == "..") {
        board[i][j] = s;
      } else if (s == ".Q") {
        quaff = {i, j}; // Initialize Quaffle position
      } else if (s == "RG" || s == "BG") {
        board[i][j] = s; // Record goal positions
      } else {
        char c = s[0];
        if (c == 'R') {
          R[s[1] - '0'] = {i, j}; // Store red player position
        } else {
          B[s[1] - '0'] = {i, j}; // Store blue player position
        }
      }
    }
  }
  int t;
  cin >> t;
  int rp = 0, bp = 0; // Scores for red and blue teams
  for (int time = 0; time < t; time++) {
    string player;
    cin >> player;
    string act;
    cin >> act;
    if (act == "C") {
      string ball;
      cin >> ball;
      catcher = player; // Mark the player as carrying the ball
    } else if (act == "T") {
      catcher = ""; // Release the Quaffle
    } else {
      // Move the player
      pi *ptr = &(player[0] == 'R' ? R : B)[player[1] - '0'];
      if (act == "U") {
        ptr->first--;
      } else if (act == "D") {
        ptr->first++;
      } else if (act == "L") {
        ptr->second--;
      } else {
        ptr->second++;
      }
    }
    // Update Quaffle position if someone is carrying it
    if (catcher != "")
      quaff = (catcher[0] == 'R' ? R : B)[catcher[1] - '0'];
    else {
      // Check if Quaffle is in a goal
      if (board[quaff.first][quaff.second] == "RG") {
        cout << time << " BLUE GOAL\n"; // Red team scores in their own goal, so Blue team gets the point
        rp++;
        quaff = {n / 2, m / 2}; // Reset Quaffle to center
      } else if (board[quaff.first][quaff.second] == "BG") {
        cout << time << " RED GOAL\n"; // Blue team scores in their own goal, so Red team gets the point
        bp++;
        quaff = {n / 2, m / 2}; // Reset Quaffle to center
      }
    }
  }
  cout << "FINAL SCORE: " << bp << " " << rp << "\n";
}


// https://github.com/VaHiX/CodeForces/