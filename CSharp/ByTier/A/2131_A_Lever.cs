// Problem: CF 2131 A - Lever
// https://codeforces.com/contest/2131/problem/A

/*
 * Problem: The Lever
 * Purpose: Calculate the number of iterations a "Lever" process performs on two arrays `a` and `b`.
 *          In each iteration:
 *            - Decrease `a[i]` by 1 if `a[i] > b[i]`
 *            - Increase `a[i]` by 1 if `a[i] < b[i]`
 *          The process stops when no element in `a` can be decreased (i.e., no `a[i] > b[i]` exists).
 * 
 * Algorithm:
 *   - For each test case, calculate how many times we can decrease elements of array `a` that are greater than corresponding elements in `b`.
 *   - This corresponds to the total excess of `a` over `b` across all indices.
 *   - The number of iterations equals this sum plus 1 (as the last step ends the process due to no more decreases possible).
 *
 * Time Complexity: O(n) per test case, where n is the length of the arrays.
 * Space Complexity: O(n) for storing input arrays.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) { // Loop through each test case
      var n = int.Parse(Console.ReadLine().Trim()); // Read array length
      string[] line = Console.ReadLine().Trim().Split(' '); // Read first array
      var a = Array.ConvertAll(line, int.Parse); // Convert to int array
      line = Console.ReadLine().Trim().Split(' '); // Read second array
      var b = Array.ConvertAll(line, int.Parse); // Convert to int array
      getAns(n, a, b); // Compute and print result
    }
  }
  
  static void getAns(int n, int[] a, int[] b) {
    var big = 0; // Initialize counter for total excess of a over b
    for (int i = 0; i < n; i++) { // Iterate through all indices
      if (a[i] > b[i]) // If a[i] exceeds b[i]
        big += a[i] - b[i]; // Add difference to counter
    }
    Console.WriteLine(big + 1); // Number of iterations is excess + 1
  }
}


// https://github.com/VaHiX/codeForces/