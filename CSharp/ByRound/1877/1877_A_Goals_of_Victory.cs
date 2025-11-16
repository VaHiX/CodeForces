// Problem: CF 1877 A - Goals of Victory
// https://codeforces.com/contest/1877/problem/A

/*
 * Problem: A. Goals of Victory
 * 
 * Purpose: Given the efficiencies of n-1 teams in a football tournament, compute the efficiency of the missing team.
 * 
 * Algorithm:
 * - The total sum of all team efficiencies in a tournament must equal zero, because every goal scored by one team
 *   is countered by a goal scored by another team in the opposing match.
 * - Thus, if we know the sum of (n-1) efficiencies, the missing efficiency is simply the negative of that sum.
 * 
 * Time Complexity: O(n), where n is the number of teams, as we iterate through the array once to calculate the sum.
 * Space Complexity: O(1), as only a constant amount of extra space is used.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int tc = 0; tc < t; tc++) { // Process each test case
      int n = int.Parse(Console.ReadLine()); // Read number of teams
      int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Read efficiencies of n-1 teams
      int b = 0; // Initialize sum of known efficiencies
      foreach (int i in a) { // Iterate through all known efficiencies
        b += i; // Accumulate the sum
      }
      Console.WriteLine(-b); // The missing efficiency is the negative of the sum
    }
  }
}


// https://github.com/VaHiX/CodeForces/