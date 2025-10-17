// Problem: CF 2047 C - Swap Columns and Find a Path
// https://codeforces.com/contest/2047/problem/C

/*
C. Swap Columns and Find a Path

Algorithm:
This problem involves finding the maximum cost path from (1,1) to (2,n) in a 2-row, n-column matrix,
where we can swap columns any number of times before choosing the path.

Key insight:
- We are allowed to swap columns arbitrarily.
- In each column, we need to choose which element (from row 1 or row 2) to include in our path.
- We want to maximize the total sum along a valid path that goes right and down only.
- For any fixed column i, we should take the larger of the two values a[i] and b[i].
- If we pick from a[i], then for the total cost, we also need to consider the maximum value among b[j]
  where j is in all columns where we chose from row 2 (since those contribute more to the path).

Approach:
1. For each column i, decide which of a[i] or b[i] should be included based on maximizing sum of all selected elements.
2. Track:
   - bigsum: total of max(a[i], b[i]) across all columns
   - smaLLmax: maximum value (from the smaller of pair) across all columns

Time Complexity: O(n)
Space Complexity: O(1)

*/

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of matrix
      string[] line = Console.ReadLine().Trim().Split(' '); // Read first row
      var a = Array.ConvertAll(line, int.Parse);
      line = Console.ReadLine().Trim().Split(' '); // Read second row
      var b = Array.ConvertAll(line, int.Parse);
      getAns(n, a, b); // Process the case
    }
  }
  static void getAns(int n, int[] a, int[] b) {
    var bigsum = 0; // Sum of max(a[i], b[i]) for all i
    var smaLLmax = -1000000; // Maximum of min(a[i], b[i]) among all i
    
    // Iterate through each column to determine optimal choice
    for (int i = 0; i < n; i++) {
      if (a[i] >= b[i]) {
        bigsum += a[i]; // Add the larger value to bigsum
        smaLLmax = Max(smaLLmax, b[i]); // Track max of smaller values
      } else {
        bigsum += b[i]; // Add the larger value to bigsum
        smaLLmax = Max(smaLLmax, a[i]); // Track max of smaller values
      }
    }
    
    Console.WriteLine(bigsum + smaLLmax); // Final result = total sum + maximum smaller element from chosen columns
  }
}


// https://github.com/VaHiX/codeForces/