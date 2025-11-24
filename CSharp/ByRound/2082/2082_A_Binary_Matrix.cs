// Problem: CF 2082 A - Binary Matrix
// https://codeforces.com/contest/2082/problem/A

/*
 * Problem: Minimum Changes to Make Binary Matrix "Good"
 * 
 * A binary matrix is called "good" if:
 *   - The XOR of all elements in each row equals 0
 *   - The XOR of all elements in each column equals 0
 * 
 * Objective:
 *   Find the minimum number of elements to change in order to make the given matrix good.
 * 
 * Approach:
 *   - For rows: count how many rows have an odd number of '1's. Let this count be `c`.
 *   - For columns: count how many columns have an odd number of '1's. Let this count be `d`.
 *   - The minimum changes needed is max(c, d).
 * 
 * Time Complexity:
 *   O(n * m) per test case, where n is rows and m is columns.
 * 
 * Space Complexity:
 *   O(n * m) for storing the matrix.
 */

using static System.Math;
using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read dimensions
      var h = int.Parse(line[0]); // Number of rows
      var w = int.Parse(line[1]); // Number of columns
      var s = new string[h]; // Matrix storage
      for (int i = 0; i < h; i++)
        s[i] = Console.ReadLine().Trim(); // Read matrix rows
      getAns(h, w, s); // Compute result
    }
  }
  static void getAns(int h, int w, string[] s) {
    var c = 0; // Count of rows with odd number of '1's
    for (int i = 0; i < h; i++) {
      var t = s[i].Count(z => z == '1'); // Count '1's in row i
      if (t % 2 == 1) // If count is odd
        c++; // Increment row counter
    }
    var d = 0; // Count of columns with odd number of '1's
    for (int i = 0; i < w; i++) {
      var t = 0; // Counter for column i
      for (int j = 0; j < h; j++) {
        if (s[j][i] == '1') // If element is '1'
          t++; // Increment counter
      }
      if (t % 2 == 1) // If count is odd
        d++; // Increment column counter
    }
    Console.WriteLine(Max(c, d)); // Output answer
  }
}


// https://github.com/VaHiX/codeForces/