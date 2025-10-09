// Problem: CF 2086 A - Cloudberry Jam
// https://codeforces.com/contest/2086/problem/A

/*
 * Problem: Cloudberry Jam
 * Purpose: Calculate the amount of cloudberries needed to produce n jars of jam.
 * Algorithm: 
 *   - Each jar requires 3 kg of jam.
 *   - To make 3 kg of jam, we need 4 kg of raw ingredients (berries + sugar), since 25% evaporates.
 *   - So for n jars, we need 2*n kg of berries.
 * Time Complexity: O(T), where T is the number of test cases.
 * Space Complexity: O(1), only using a constant amount of space.
 */

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) { // Process each test case
      var n = int.Parse(Console.ReadLine().Trim()); // Read number of jars
      Console.WriteLine(2 * n); // Output required berries (2*n kg)
    }
  }
}


// https://github.com/VaHiX/codeForces/