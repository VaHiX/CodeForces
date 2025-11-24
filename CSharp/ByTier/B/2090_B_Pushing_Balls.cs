// Problem: CF 2090 B - Pushing Balls
// https://codeforces.com/contest/2090/problem/B

/*
Problem: B. Pushing Balls
Purpose: Determine if a given grid state can be achieved by pushing balls from the left or top edges of rows/columns, following specific rules about ball movement and collision.
Algorithms/Techniques: 
    - Simulation with backtracking logic
    - Check row-wise and column-wise constraints to ensure the balls could have been pushed in valid order.

Time Complexity: O(n * m) per test case, where n is number of rows and m is number of columns. Each cell is checked a few times in different loops.
Space Complexity: O(n * m) for storing the grid map and the boolean 'ok' array to mark accessible positions.

*/

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) { // Process each test case
      string[] line = Console.ReadLine().Trim().Split(' '); // Read dimensions
      var h = int.Parse(line[0]);
      var w = int.Parse(line[1]);
      getAns(h, w); // Solve current test case
    }
  }
  
  static void getAns(int h, int w) {
    var map = new int[h, w]; // Store the input grid indicating where balls are placed
    
    // Read the grid from input and fill the map
    for (int i = 0; i < h; i++) {
      var s = Console.ReadLine().Trim();
      for (int j = 0; j < w; j++)
        if (s[j] == '1')
          map[i, j] = 1;
    }
    
    // Track whether a cell is "reachable" from left or top (initially all false)
    var ok = new bool[h, w];
    
    // For each row, mark cells that can be reached from the left side
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++)
        if (map[i, j] == 1)
          ok[i, j] = true;
        else
          break; // Stop when hitting an empty cell because further cells in same row are unreachable from left
    }
    
    // For each column, mark cells that can be reached from the top side
    for (int i = 0; i < w; i++) {
      for (int j = 0; j < h; j++)
        if (map[j, i] == 1)
          ok[j, i] = true;
        else
          break; // Stop when hitting an empty cell because further cells in same column are unreachable from top
    }
    
    // Now verify that all cells with balls can actually be reached by both directions
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++)
        if (map[i, j] == 1 && !ok[i, j]) {
          Console.WriteLine("NO"); // If a ball's position cannot be reached from either left or top, it's invalid
          return;
        }
    }
    
    Console.WriteLine("YES"); // All balls can be pushed in valid sequence
  }
}


// https://github.com/VaHiX/codeForces/