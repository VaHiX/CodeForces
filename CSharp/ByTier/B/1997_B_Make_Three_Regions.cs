// Problem: CF 1997 B - Make Three Regions
// https://codeforces.com/contest/1997/problem/B

using System;
public class MakeThreeRegions {
  // Purpose: Count the number of free cells such that blocking them creates exactly 3 connected regions.
  // Algorithm: 
  // - Iterate through each column (except first and last) to check if a free cell can be blocked
  //   to split the grid into exactly 3 regions.
  // - For each cell (i,j) that is free, verify if it forms a "bridge" between two regions.
  // - Conditions:
  //   1. Cell is free in both rows: c1 = s1[j] == '.' && s2[j] == '.'
  //   2. Its neighbors in the same row are blocked, and neighbors in the other row are free:
  //      c2: s1[j - 1] == 'x' && s1[j + 1] == 'x' && s2[j - 1] == '.' && s2[j + 1] == '.'
  //      c3: s2[j - 1] == 'x' && s2[j + 1] == 'x' && s1[j - 1] == '.' && s1[j + 1] == '.'
  // - If c1 is true and (c2 or c3) is true, then this cell can be blocked to create 3 regions.
  // Time Complexity: O(n) for each test case, where n is the number of columns.
  // Space Complexity: O(1), only using a few variables for computation.
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string s1 = Console.ReadLine();
      string s2 = Console.ReadLine();
      int idxLast = n - 1;
      int ans = 0;
      for (int j = 1; j < idxLast; j++) {
        bool c1 = s1[j] == '.' && s2[j] == '.'; // Check if both cells in column j are free
        bool c2 = s1[j - 1] == 'x' && s1[j + 1] == 'x' && s2[j - 1] == '.' &&
                  s2[j + 1] == '.'; // Check if upper row neighbors are blocked, lower row neighbors are free
        bool c3 = s2[j - 1] == 'x' && s2[j + 1] == 'x' && s1[j - 1] == '.' &&
                  s1[j + 1] == '.'; // Check if lower row neighbors are blocked, upper row neighbors are free
        if (c1 && (c2 || c3))
          ans++; // If all conditions satisfied, increment the result
      }
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/