// Problem: CF 1921 E - Eat the Chip
// https://codeforces.com/contest/1921/problem/E

/*
 * Problem: Eat the Chip
 * Algorithm: Simulation with optimal play strategy
 * Time Complexity: O(h) where h is the number of rows
 * Space Complexity: O(1)
 * 
 * The problem involves two players (Alice and Bob) moving chips on a grid with specific movement rules.
 * Alice moves down, Bob moves up. The game ends when one player captures the other or no moves are possible.
 * 
 * This solution simulates the game under optimal play conditions:
 * - Alice always moves toward Bob (down)
 * - Bob always moves toward Alice (up)
 * - In each turn, each player chooses the best possible direction based on minimizing distance to the opponent
 * 
 * The key insight is to model the movement and check for win conditions or draw scenarios:
 * - If Alice can reach Bob in an even number of turns (Alice's turn), Alice wins
 * - If Bob can reach Alice in an odd number of turns (Bob's turn), Bob wins  
 * - If no move is possible (board boundaries), it's a draw
 * 
 * The two simulations check for Alice's winning condition first, then Bob's.
*/

using System;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        Solve();
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static void Solve() {
    long n, m;
    long[] x = new long[2];
    long[] y = new long[2];
    string[] input = Console.ReadLine().Split();
    n = long.Parse(input[0]);
    m = long.Parse(input[1]);
    x[0] = long.Parse(input[2]);
    y[0] = long.Parse(input[3]);
    x[1] = long.Parse(input[4]);
    y[1] = long.Parse(input[5]);
    long[] cx = { x[0], y[0], x[1], y[1] }; // Store initial positions
    bool flag = true; // true means Alice's turn, false means Bob's turn
    
    // First simulation: check if Alice can win by moving optimally towards Bob
    while (x[0] <= n && x[1] >= 1 && !(x[0] == x[1] && y[0] == y[1])) {
      if (flag) {
        // Alice's turn - move down
        x[0]++;
        // Adjust y coordinate to move towards Bob
        if (y[0] == y[1]) {
          // Same column - move closer to Bob
          // Choose direction that reduces distance in y, preferring the direction that leads to capture faster
        } else if (y[0] < y[1]) {
          // Alice is left of Bob - move right if possible
          if (y[0] + 1 <= m) {
            y[0]++;
          }
        } else {
          // Alice is right of Bob - move left if possible
          if (y[0] - 1 >= 1) {
            y[0]--;
          }
        }
      } else {
        // Bob's turn - move up
        x[1]--;
        // Adjust y coordinate to move towards Alice
        if (y[0] == y[1]) {
          // Same column - move closer to Alice
          // Check which direction is better for Bob based on current position
          if (y[1] - 1 > m - y[1]) {
            // More space to the left - move left
            if (y[1] - 1 >= 1) {
              y[1]--;
            }
          } else {
            // More space to the right - move right
            if (y[1] + 1 <= m) {
              y[1]++;
            }
          }
        } else if (y[0] < y[1]) {
          // Bob is right of Alice - move left if possible
          if (y[1] + 1 <= m) {
            y[1]++;
          }
        } else {
          // Bob is left of Alice - move right if possible
          if (y[1] - 1 >= 1) {
            y[1]--;
          }
        }
      }
      flag = !flag; // Switch turn
    }
    
    // If we reached the point where chips meet and it's Bob's turn, Bob wins
    if (x[0] == x[1] && y[0] == y[1] && flag == false) {
      Console.WriteLine("Alice");
      return;
    }
    
    // Reset positions
    x[0] = cx[0];
    y[0] = cx[1];
    x[1] = cx[2];
    y[1] = cx[3];
    flag = true;
    
    // Second simulation: check if Bob can win by moving optimally towards Alice
    while (x[0] <= n && x[1] >= 1 && !(x[0] == x[1] && y[0] == y[1])) {
      if (flag) {
        // Alice's turn - move down
        x[0]++;
        // Choose best direction for Alice (moving towards Bob)
        if (y[0] == y[1]) {
          // Same column - move closer to Bob
          // Choose direction that leads to capture faster - prefer moving left if more space to right or vice versa
          if (y[0] - 1 > m - y[0]) {
            // More space to the right - move left
            if (y[0] - 1 >= 1) {
              y[0]--;
            }
          } else {
            // More space to the left - move right
            if (y[0] + 1 <= m) {
              y[0]++;
            }
          }
        } else if (y[0] < y[1]) {
          // Alice is left of Bob - move right if possible
          if (y[0] - 1 >= 1) {
            y[0]--;
          }
        } else {
          // Alice is right of Bob - move left if possible
          if (y[0] + 1 <= m) {
            y[0]++;
          }
        }
      } else {
        // Bob's turn - move up
        x[1]--;
        // Choose best direction for Bob (moving towards Alice)
        if (y[0] == y[1]) {
          // Same column - move closer to Alice
        } else if (y[0] < y[1]) {
          // Bob is right of Alice - move left if possible
          if (y[1] - 1 >= 1) {
            y[1]--;
          }
        } else {
          // Bob is left of Alice - move right if possible
          if (y[1] + 1 <= m) {
            y[1]++;
          }
        }
      }
      flag = !flag; // Switch turn
    }
    
    // If we reached the point where chips meet and it's Alice's turn, Alice wins
    if (x[0] == x[1] && y[0] == y[1] && flag == true) {
      Console.WriteLine("Bob");
      return;
    }
    
    // If no one could capture, it's a draw
    Console.WriteLine("Draw");
  }
}


// https://github.com/VaHiX/CodeForces/