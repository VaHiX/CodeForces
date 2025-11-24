// Problem: CF 2053 A - Tender Carpenter
// https://codeforces.com/contest/2053/problem/A

/*
 * Problem: A. Tender Carpenter
 * Algorithm: Check if array can be partitioned into at least 2 subsegments such that each subsegment forms a stable set.
 * A set is stable if any three elements from it can form a non-degenerate triangle.
 * Time Complexity: O(n^2) - in worst case, for each pair we check triangle inequality.
 * Space Complexity: O(1) - only using constant extra space.
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process the current test case
    }
  }
  
  static void getAns(int n, int[] a) {
    for (int i = 0; i < n - 1; i++) { // Iterate through all possible split points
      if (a[i] < a[i + 1]) { // If current element is smaller than next
        if (a[i] * 2 > a[i + 1]) { // Check triangle inequality: 2*a[i] > a[i+1]
          Console.WriteLine("YES");
          return; // Found valid split, exit as we have at least one way to partition
        }
      } else if (a[i + 1] < a[i]) { // If next element is smaller than current
        if (a[i + 1] * 2 > a[i]) { // Check triangle inequality: 2*a[i+1] > a[i]
          Console.WriteLine("YES");
          return; // Found valid split, exit as we have at least one way to partition
        }
      } else { // If elements are equal
        Console.WriteLine("YES");
        return; // Equal elements always form valid triangle (even degenerate)
      }
    }
    Console.WriteLine("NO"); // No valid split found
  }
}


// https://github.com/VaHiX/codeForces/