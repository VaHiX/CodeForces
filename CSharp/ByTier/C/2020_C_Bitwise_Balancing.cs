// Problem: CF 2020 C - Bitwise Balancing
// https://codeforces.com/contest/2020/problem/C

/*
C. Bitwise Balancing
Algorithm: Bit manipulation using precomputed lookup table for each bit position.
Time Complexity: O(1) per test case (since we process up to 61 bits and the lookup table is constant size)
Space Complexity: O(1) (the dictionary has a fixed size of 8 entries)

The problem requires finding a value 'a' such that (a | b) - (a & c) = d.
This is solved by processing each bit position independently:
- For each bit position i, we determine the values of b[i], c[i], and d[i].
- Based on these three bits, we compute what a[i] should be to satisfy the equation.
- A lookup table `dic` is precomputed for all possible combinations of (b[i], c[i], d[i]).
*/

using System.Collections.Generic;
using System;
public class hello {
  public static Dictionary<string, int> dic; // Precomputed mapping for bit combinations
  static void Main() {
    dic = calc(); // Initialize the lookup table
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read b, c, d
      var b = long.Parse(line[0]);
      var c = long.Parse(line[1]);
      var d = long.Parse(line[2]);
      getAns(b, c, d); // Solve for 'a' in current test case
    }
  }
  
  static Dictionary<string, int> calc() { // Precompute valid bits for all combinations
    var dic = new Dictionary<string, int>();
    for (int a = 0; a < 2; a++) // Loop over possible values of a[i]
      for (int b = 0; b < 2; b++) // Loop over possible values of b[i]
        for (int c = 0; c < 2; c++) { // Loop over possible values of c[i]
          var d = (a | b) - (a & c); // Compute d[i] = (a[i] | b[i]) - (a[i] & c[i])
          dic[b.ToString() + c.ToString() + d.ToString()] = a; // Map b,c,d to required a
        }
    return dic;
  }
  
  static void getAns(long b, long c, long d) { // Calculate final answer for given b, c, d
    var ans = 0L; // Result value initialized to zero
    for (int i = 0; i < 61; i++) { // Process all valid bit positions (up to 61)
      var bb = ((b >> i) & 1) == 1 ? "1" : "0"; // Extract b[i]
      var cc = ((c >> i) & 1) == 1 ? "1" : "0"; // Extract c[i]
      var dd = ((d >> i) & 1) == 1 ? "1" : "0"; // Extract d[i]
      var k = bb + cc + dd; // Concatenate to form key for lookup
      if (k == "100" | k == "011") { // If invalid combination, no solution exists
        Console.WriteLine(-1);
        return;
      }
      if (dic[k] == 1) // Set bit in result if dictionary says a[i] should be 1
        ans |= 1L << i;
    }
    Console.WriteLine(ans); // Print computed value of 'a'
  }
}


// https://github.com/VaHiX/codeForces/