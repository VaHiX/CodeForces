// Problem: CF 2036 D - I Love 1543
// https://codeforces.com/contest/2036/problem/D

/*
D. I Love 1543
Time Complexity: O(n * m) where n and m are dimensions of the grid, as each cell is visited once per layer.
Space Complexity: O(n * m) for the visited boolean array and temporary storage.

Algorithms/Techniques:
- Layer-by-layer traversal of a 2D grid in clockwise direction
- For each layer, check for sequence "1543" in the order of traversal
- Use BFS-like approach to traverse each layer with direction vectors
*/

using static System.Math;
using System.Collections.Generic;
using System;
public class hello {
  public static int[] dx, dy;
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var h = int.Parse(line[0]);
      var w = int.Parse(line[1]);
      var map = new int[h, w];
      for (int i = 0; i < h; i++) {
        var s = Console.ReadLine().Trim();
        for (int j = 0; j < w; j++)
          map[i, j] = s[j] - '0'; // Convert char digit to int
      }
      getAns(h, w, map);
    }
  }
  static int check(int h, int w, int[,] map, bool[,] visited, int x, int y) {
    var map2 = new List<int>(); // Stores the sequence of digits in current layer
    var d = 0; // Direction index
    while (d < 4) {
      var nx = x + dx[d];
      var ny = y + dy[d];
      if (nx >= 0 && nx < h && ny >= 0 && ny < w && !visited[nx, ny]) {
        map2.Add(map[nx, ny]);
        x = nx;
        y = ny;
        visited[nx, ny] = true; // Mark as visited to avoid re-traversal
      } else
        d++; // Change direction if cannot move in current direction
    }
    var n = map2.Count;
    var c = 0;
    for (int i = 0; i < n; i++) {
      if (map2[i] == 1) { // Check for pattern starting with 1
        // Check for the exact sequence 1543 in circular order
        if (map2[(i + 1) % n] == 5 && map2[(i + 2) % n] == 4 &&
            map2[(i + 3) % n] == 3)
          c++;
      }
    }
    return c; // Return count of occurrences of 1543 in this layer
  }
  static void getAns(int h, int w, int[,] map) {
    dx = new int[] { 0, 1, 0, -1 }; // Direction vectors: right, down, left, up
    dy = new int[] { 1, 0, -1, 0 };
    var visited = new bool[h, w];
    var imax = Min(h, w); // Maximum number of layers to traverse
    var ans = 0;
    for (int i = 0; i < imax / 2; i++) {
      ans += check(h, w, map, visited, i, i); // Traverse each layer starting from (i, i)
    }
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/