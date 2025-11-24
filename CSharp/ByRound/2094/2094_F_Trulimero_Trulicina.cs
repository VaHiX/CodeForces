// Problem: CF 2094 F - Trulimero Trulicina
// https://codeforces.com/contest/2094/problem/F

/* 
 * Problem: F. Trulimero Trulicina
 * Purpose: Generate an n x m grid of integers from 1 to k such that:
 *   - Each integer appears equal number of times
 *   - No two adjacent cells (sharing an edge) have same integer
 *   - Each integer is in range [1, k]
 * 
 * Algorithms/Techniques:
 *   - Normal filling: Fill row-wise with cycling from 1 to k
 *   - Shifted filling: Alternate starting value per row (1 then 2, etc.)
 *   - Decide which pattern to use based on m % k == 0
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for storing the grid
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n, m, k
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      var k = int.Parse(line[2]);
      getAns(n, m, k); // Process the current test case
    }
  }

  // Fills grid row-wise with cycling from 1 to k
  static int[,] normal(int n, int m, int k) {
    var a = new int[n, m]; // Create grid
    var t = 1; // Start value
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        a[i, j] = t; // Assign current value
        t++; // Increment
        if (t > k) // Cycle back to 1 if exceeding k
          t = 1;
      }
    }
    return a;
  }

  // Fills grid alternating starting values per row: row 0 starts at 1, row 1 starts at 2
  static int[,] shift1(int n, int m, int k) {
    var a = new int[n, m]; // Create grid
    var f = true; // Flag to alternate start value
    for (int i = 0; i < n; i++) {
      if (f) { // For even rows: start with 1
        var t = 1;
        for (int j = 0; j < m; j++) {
          a[i, j] = t;
          t++;
          if (t > k)
            t = 1;
        }
        f = false;
      } else { // For odd rows: start with 2
        var t = 2;
        for (int j = 0; j < m; j++) {
          a[i, j] = t;
          t++;
          if (t > k)
            t = 1;
        }
        f = true;
      }
    }
    return a;
  }

  // Prints the grid row by row
  static void print(int n, int m, int[,] ans) {
    var p = new int[m]; // Temporary array to store each row for printing
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++)
        p[j] = ans[i, j]; // Copy current row
      Console.WriteLine(string.Join(" ", p)); // Print the row
    }
  }

  // Decides between normal and shifted grid based on divisibility of m by k
  static void getAns(int n, int m, int k) {
    if (m % k == 0) { // If m is divisible by k, use shift1
      var ans = shift1(n, m, k);
      print(n, m, ans);
    } else { // Otherwise, use normal filling
      var ans = normal(n, m, k);
      print(n, m, ans);
    }
  }
}


// https://github.com/VaHiX/codeForces/