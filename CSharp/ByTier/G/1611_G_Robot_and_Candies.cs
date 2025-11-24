// Problem: CF 1611 G - Robot and Candies
// https://codeforces.com/contest/1611/problem/G

/* 
 * Problem: Robot and Candies
 * Algorithm: Simulation with greedy approach
 * Time Complexity: O(n * m) where n is number of rows and m is number of columns
 * Space Complexity: O(n * m) for storing the grid
 * 
 * The solution simulates placing a robot on the top row and tracing its path.
 * The robot can move diagonally down-right or down-left. 
 * We simulate the robot's movement and mark collected candies as 0.
 * The key insight is to greedily determine the minimum number of starting positions needed.
 */

using System;
using System.IO;
using System.Text;
namespace Robot_and_Candies {
internal class Program {
  private static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  private static readonly StreamWriter writer = new StreamWriter(
      Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
  private static void Main(string[] args) {
    int t = Next();
    for (int i = 0; i < t; i++) {
      writer.WriteLine(Solve());
    }
    writer.Flush();
  }
  private static int Solve() {
    int n = Next();
    int m = Next();
    var nm = new int[n, m];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        nm[i, j] = Next(true); // Read the grid
      }
    int count = 0;
    for (int i = 0; i < n + m - 1; i++) { // Iterate through diagonals
      if (i == 0) {
        // First diagonal - check if candy exists at (0,0)
        if (nm[0, 0] == 1)
          count++;
      } else if (i == 1) {
        // Second diagonal - process first two cells
        if (n > 1 && nm[1, 0] == 1) {
          count++;
          nm[0, 1] = 0; // Mark candy as collected
        } else if (nm[0, 1] == 1) {
          count++;
        }
      } else {
        // Process remaining diagonals
        int x, y, x1, y1;
        // Calculate coordinates of current diagonal's start point
        if (i < n) {
          y = i;
          x = 0;
        } else {
          y = n - 1;
          x = i - (n - 1);
        }
        // Calculate coordinates of previous diagonal's start point
        if (i - 2 < n) {
          x1 = 0;
          y1 = i - 2;
        } else {
          y1 = n - 1;
          x1 = i - 2 - (n - 1);
        }
        // Process current diagonal
        while (y >= 0) {
          while (y1 >= y) {
            // Propagate candies to next level
            if (nm[y1, x1] == 1 && y1 + 1 < n)
              nm[y1 + 1, x1 + 1] = 1;
            y1--;
            x1++;
            if (x1 >= m)
              y1 = -1;
          }
          // Skip empty cells
          while (y1 >= 0 && nm[y1, x1] == 0) {
            y1--;
            x1++;
            if (x1 >= m)
              y1 = -1;
          }
          // If there's a candy at current position
          if (nm[y, x] == 1) {
            if (y1 < 0) {
              // No candy found in previous diagonal, need new robot
              count++;
              y--;
              x++;
              // Mark all visited candies as collected
              while (y >= 0 && x < m) {
                nm[y, x] = 0;
                y--;
                x++;
              }
              y = -1;
            } else {
              // Process collected candy
              y--;
              x++;
              if (x >= m)
                y = -1;
              // Mark intermediate candies as collected
              while (y > y1) {
                nm[y, x] = 0;
                y--;
                x++;
                if (x >= m)
                  y = -1;
              }
              y1--;
              x1++;
              if (x1 >= m)
                y1 = -1;
            }
          } else {
            // No candy at current position, continue traversing
            y--;
            x++;
            if (x >= m)
              y = -1;
          }
        }
        // Handle remaining cells
        while (y1 >= 0) {
          if (nm[y1, x1] == 1) {
            if (x1 + 1 < m && y1 + 1 < n) {
              // Propagate candy
              nm[y1 + 1, x1 + 1] = 1;
            } else if (x1 + 1 >= m) {
              // Handle special case when going out of bounds
              y1 += 2;
              while (y1 < n && x1 >= 0) {
                if (nm[y1, x1] == 0) {
                  // Set new candy propagation point
                  nm[y1, x1] = 1;
                  break;
                }
                y1++;
                x1--;
              }
              break;
            }
          }
          y1--;
          x1++;
          if (x1 >= m)
            y1 = -1;
        }
      }
    }
    return count;
  }
  private static int Next(bool one = false) {
    int c;
    int res = 0;
    do {
      c = reader.Read();
      if (c == -1)
        return res;
    } while (c < '0' || c > '9');
    res = c - '0';
    if (one)
      return res;
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return res;
      res *= 10;
      res += c - '0';
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/