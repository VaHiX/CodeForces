// Problem: CF 2102 A - Dinner Time
// https://codeforces.com/contest/2102/problem/A

/*
 * Problem: Dinner Time
 * 
 * Description:
 * Given four integers n, m, p, and q, determine whether there exists an integer array a[1], a[2], ..., a[n]
 * such that:
 * 1. The sum of all elements is equal to m.
 * 2. The sum of every p consecutive elements is equal to q.
 *
 * Algorithm:
 * - For each test case, we compute how many complete segments of size p fit into array length n.
 * - If the remainder (r = n % p) is zero, then all segments must sum up to q and total sum must be m.
 *   We check if (n / p) * q == m.
 * - If the remainder is not zero, it's always possible to construct such an array because we can adjust
 *   the last few elements to satisfy both constraints.
 *
 * Time Complexity: O(1) per test case, since we do constant time operations.
 * Space Complexity: O(1), as no extra space is used beyond input storage.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) { // Process each test case
      string[] line = Console.ReadLine().Trim().Split(' '); // Read input line and split
      var n = int.Parse(line[0]); // Length of array
      var m = int.Parse(line[1]); // Total sum required
      var p = int.Parse(line[2]); // Segment length
      var q = int.Parse(line[3]); // Sum of each segment
      getAns(n, m, p, q); // Call helper function to determine answer
    }
  }
  static void getAns(int n, int m, int p, int q) {
    var t = n / p; // Number of complete segments of length p
    var r = n % p; // Remainder when dividing n by p
    
    if (r == 0) // If there is no remainder, all segments are full
      Console.WriteLine(t * q == m ? "YES" : "NO"); // Check if total sum matches
    else
      Console.WriteLine("YES"); // If there's a remainder, it's always possible to construct array
  }
}


// https://github.com/VaHiX/codeForces/