// Problem: CF 2103 A - Common Multiple
// https://codeforces.com/contest/2103/problem/A

/*
 * Problem: Maximum Size of Beautiful Subsequence
 * 
 * Description:
 * An array x is beautiful if there exists an array y with distinct elements such that 
 * all products x[i] * y[i] are equal. The goal is to find the maximum size of a subsequence 
 * of the given array that is beautiful.
 *
 * Algorithm/Techniques:
 * - For each test case, we process the input array.
 * - A key insight is that for a subsequence to be beautiful, it must be possible to assign distinct values 
 *   to elements such that their products with corresponding y[i] are equal. 
 *   This effectively means that all elements in the subsequence should have the same value, because:
 *   if x[i] * y[i] = x[j] * y[j], then y[i]/y[j] = x[j]/x[i]. Since y values must be distinct,
 *   we are forced to consider only elements with identical values.
 * - So, the maximum beautiful subsequence size equals the maximum frequency of any element in the array.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing unique elements using HashSet
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      Console.ReadLine(); // Read and ignore the length of array (we don't need it)
      string[] line = Console.ReadLine().Trim().Split(' '); // Read the array elements
      var hs = Array.ConvertAll(line, int.Parse).ToHashSet(); // Convert to HashSet to get unique values
      Console.WriteLine(hs.Count); // Output number of unique elements (maximum size of beautiful subsequence)
    }
  }
}


// https://github.com/VaHiX/codeForces/