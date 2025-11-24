// Problem: CF 1873 C - Target Practice
// https://codeforces.com/contest/1873/problem/C

/*
 * Purpose: Calculate the total points scored on a 10x10 target based on the placement of arrows.
 *          The target has 5 concentric rings with point values from 1 to 5.
 *          Arrows are counted based on which ring they land in.
 *
 * Algorithms/Techniques:
 *   - Direct ring detection by checking positions in predefined rings
 *   - Iterative scanning of grid edges to identify arrows and assign point values accordingly
 *
 * Time Complexity: O(t * n^2) where t is the number of test cases and n=10 (fixed grid size)
 * Space Complexity: O(n^2) for storing the grid of size 10x10 per test case
 */

using System;
class Program {
  static void Main(string[] args) {
    double E = 1e-6;
    double PI = 3.1415926535;
    double INF = 1e18;
    double MOD = 1e9 + 7;
    int t = int.Parse(Console.ReadLine());
    while (t > 0) {
      int n = 10;
      string[] vec = new string[n];
      for (int i = 0; i < n; i++) {
        vec[i] = Console.ReadLine();
      }
      int sum = 0;
      // Check outermost ring (1 point) - top and bottom edges
      for (int i = 0; i < 10; i++) {
        if (vec[0][i] == 'X') // Top edge
          sum += 1;
        if (vec[9][i] == 'X') // Bottom edge
          sum += 1;
      }
      // Check second ring (1 point) - left and right edges
      for (int i = 1; i < 9; i++) {
        if (vec[i][0] == 'X')
          sum += 1;
        if (vec[i][9] == 'X')
          sum += 1;
      }
      // Check third ring (2 points)
      for (int i = 1; i < 9; i++) {
        if (vec[1][i] == 'X')
          sum += 2;
        if (vec[8][i] == 'X')
          sum += 2;
      }
      // Check fourth ring (2 points)
      for (int i = 2; i < 8; i++) {
        if (vec[i][1] == 'X')
          sum += 2;
        if (vec[i][8] == 'X')
          sum += 2;
      }
      // Check fifth ring (3 points)
      for (int i = 2; i < 8; i++) {
        if (vec[2][i] == 'X')
          sum += 3;
        if (vec[7][i] == 'X')
          sum += 3;
      }
      // Check sixth ring (3 points)
      for (int i = 3; i < 7; i++) {
        if (vec[i][2] == 'X')
          sum += 3;
        if (vec[i][7] == 'X')
          sum += 3;
      }
      // Check seventh ring (4 points)
      for (int i = 3; i < 7; i++) {
        if (vec[3][i] == 'X')
          sum += 4;
        if (vec[6][i] == 'X')
          sum += 4;
      }
      // Check eighth ring (4 points)
      for (int i = 4; i < 6; i++) {
        if (vec[i][3] == 'X')
          sum += 4;
        if (vec[i][6] == 'X')
          sum += 4;
      }
      // Check center ring (5 points)
      for (int i = 4; i < 6; i++) {
        if (vec[4][i] == 'X')
          sum += 5;
        if (vec[5][i] == 'X')
          sum += 5;
      }
      Console.WriteLine(sum);
      t--;
    }
  }
}


// https://github.com/VaHiX/CodeForces/