// Problem: CF 2107 A - LRC and VIP
// https://codeforces.com/contest/2107/problem/A

/*
 * Problem: LRC and VIP
 * Purpose: Divide an array of integers into two sequences such that their GCDs are different.
 * Algorithm:
 *   - If all elements are equal, it's impossible (return "NO").
 *   - Otherwise, place the first maximum element in sequence C (2), rest in B (1).
 *   - This ensures one sequence has a max element and others don't, leading to different GCDs.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing result array
 */

using System.Linq;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read size of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Process the input
    }
  }

  static void getAns(int n, int[] a) {
    var amax = a.Max(); // Find maximum element in array
    var amin = a.Min(); // Find minimum element in array
    
    if (amax == amin) { // If all elements are same
      Console.WriteLine("NO"); // Impossible to split into different GCD groups
      return;
    }
    
    var ans = Enumerable.Repeat(1, n).ToArray(); // Initialize result array with 1s (sequence B)
    
    for (int i = 0; i < n; i++) {
      if (a[i] == amax) { // Find first occurrence of maximum element
        ans[i] = 2; // Assign it to sequence C
        break;
      }
    }
    
    Console.WriteLine("YES"); // Solution exists
    Console.WriteLine(string.Join(" ", ans)); // Output assignment
  }
}


// https://github.com/VaHiX/codeForces/