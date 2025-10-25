// Problem: CF 2082 B - Floor or Ceil
// https://codeforces.com/contest/2082/problem/B

/*
 * Problem: B. Floor or Ceil
 * Purpose: Given an integer x and counts of two types of operations (n operations of floor division by 2,
 *          and m operations of ceiling division by 2), compute the minimum and maximum possible values
 *          of x after applying all n + m operations in any order.
 *
 * Algorithms:
 *   - For minimum value: Apply ceiling operations first (to reduce x as much as possible),
 *     then floor operations.
 *   - For maximum value: Apply floor operations first, then ceiling operations.
 *
 * Time Complexity: O(m + n) per test case — each method loops at most m or n times.
 * Space Complexity: O(1) — constant extra space used.
 */

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read x, n, m from input
      var x = int.Parse(line[0]);
      var n = int.Parse(line[1]);
      var m = int.Parse(line[2]);
      getAns(x, n, m); // Compute and output answer for current test case
    }
  }

  // Function to compute the minimum possible value of x after n floor and m ceiling operations
  static int getMin(int x, int n, int m) {
    for (int i = 0; i < m; i++) { // Apply ceiling operations first (to minimize)
      if (x == 0 || x == 1) // Early termination when x becomes 0 or 1
        break;
      x = (x + 1) / 2; // Ceiling division
    }
    for (int i = 0; i < n; i++) { // Then apply floor operations
      if (x == 0) // Early termination
        return 0;
      x /= 2; // Floor division
    }
    return x;
  }

  // Function to compute the maximum possible value of x after n floor and m ceiling operations
  static int getMax(int x, int n, int m) {
    for (int i = 0; i < n; i++) { // Apply floor operations first (to keep x as large as possible)
      x /= 2;
      if (x == 0) // Early termination
        return 0;
    }
    for (int i = 0; i < m; i++) { // Then apply ceiling operations (to maximize)
      if (x == 1) // Early termination
        return 1;
      x = (x + 1) / 2; // Ceiling division
    }
    return x;
  }

  // Main function to calculate and print the min and max values for given x, n, m
  static void getAns(int x, int n, int m) {
    var min = getMin(x, n, m); // Compute minimum value
    var max = getMax(x, n, m); // Compute maximum value
    Console.WriteLine("{0} {1}", min, max);
  }
}


// https://github.com/VaHiX/codeForces/