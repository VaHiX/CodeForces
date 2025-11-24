// Problem: CF 2001 A - Make All Equal
// https://codeforces.com/contest/2001/problem/A

/*
 * Problem: Make All Equal
 * Algorithm: Greedy
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to auxiliary array `b`
 *
 * Approach:
 * - The key insight is that we want to minimize operations to make all elements equal.
 * - We count how many times each value appears in the array.
 * - The maximum frequency of any element indicates how many elements can remain
 *   after all operations (since we delete one element at a time from adjacent pairs).
 * - Therefore, the minimum number of operations = total elements - max frequency.
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read array size
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process the current test case
    }
  }
  static void getAns(int n, int[] a) {
    var b = new int[n + 1]; // Count array to track frequency of elements (1-based indexing)
    foreach (var x in a)
      b[x]++; // Increment count for each element
    Console.WriteLine(n - b.Max()); // Minimum operations = total elements - max frequency
  }
}


// https://github.com/VaHiX/codeForces/