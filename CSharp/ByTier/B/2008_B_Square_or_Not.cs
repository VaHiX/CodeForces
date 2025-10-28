// Problem: CF 2008 B - Square or Not
// https://codeforces.com/contest/2008/problem/B

/*
 * Purpose: Determine if a given binary string could have been generated from a square beautiful binary matrix.
 * A beautiful matrix has 1s on its edges and 0s inside.
 * 
 * Algorithm:
 * 1. Check if the length of the string is a perfect square (n = r * r where r = c).
 * 2. If it is a perfect square, construct the expected edge and inside rows.
 * 3. Validate that the first and last rows match the edge pattern and middle rows match the inside pattern.
 * 
 * Time Complexity: O(n * sqrt(n)) due to checking if n is a perfect square and validating each row.
 * Space Complexity: O(sqrt(n)) for storing the edge and inside row patterns.
 */
using System;
using System.Text;
public class SquareOrNot {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read length of string
      string s = Console.ReadLine(); // Read the string
      bool ans = false; // Flag to store result
      short j = 1; // Start checking for square root from 1
      
      // Loop to find if n is a perfect square
      while (j * j <= n && !ans) {
        if (j * j == n) // If j*j equals n, then n is a perfect square
          ans = true;
        else
          j++; // Increment to check next potential square root
      }
      
      // If n is a perfect square
      if (ans) {
        // Create the edge pattern (all 1s)
        string edge = new string('1', j);
        // Create the inside pattern (1, zeros, 1)
        StringBuilder sb = new StringBuilder();
        sb.Append('1');
        for (short k = 1; k < j - 1; k++)
          sb.Append('0');
        sb.Append('1');
        string inside = sb.ToString();
        
        // Validate each row of the matrix
        for (int k = 0; k < n && ans; k += j) {
          string row = s.Substring(k, j); // Extract the current row
          // Check if it is the first or last row (should be edge pattern)
          // Or if it is a middle row (should be inside pattern)
          if ((k == 0 || k == n - j) && row != edge ||
              k > 0 && k < n - j && row != inside)
            ans = false;
        }
      }
      Console.WriteLine(ans ? "Yes" : "No"); // Print the result
    }
  }
}


// https://github.com/VaHiX/CodeForces/