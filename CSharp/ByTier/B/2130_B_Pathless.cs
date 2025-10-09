// Problem: CF 2130 B - Pathless
// https://codeforces.com/contest/2130/problem/B

/*
 * Problem: B. Pathless
 * Purpose: Determine if an array of 0s, 1s, and 2s can be rearranged such that 
 *          Alice cannot find a path from index 1 to n with sum exactly s.
 * Algorithm:
 *   - If the total sum of the array is less than s, Alice can always reach sum s
 *     by going through all elements, so return original array.
 *   - If the total sum equals s, then any path must be exactly the entire array.
 *     So we check if there exists a valid sequence; otherwise return -1.
 *   - If s is greater than sum + 1, no valid arrangement exists since at most
 *     one more step can increase sum by 2 (by visiting 2).
 *   - Otherwise, greedily rearrange all 0s first, then 1s, then 2s to form a valid sequence.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

using System.Collections.Generic;
using System.Linq;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var s = int.Parse(line[1]);
      line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, s, a);
    }
  }

  static void getAns(int n, int s, int[] a) {
    var sum = a.Sum(); // Calculate the total sum of array
    
    if (s < sum) { // If target sum is less than total sum
      Console.WriteLine(string.Join(" ", a)); // Return original array as path exists
      return;
    }
    
    if (s == sum) { // If target equals total sum, path must be whole array
      Console.WriteLine(-1); // Return -1 indicating impossibility to avoid it
      return;
    }
    
    if (s > sum + 1) { // If s is too high for any valid path (since max increment is 2)
      Console.WriteLine(-1); // Impossible to achieve target
      return;
    }

    // Count occurrences of 0, 1, and 2
    var c = new int[3];
    foreach (var x in a)
      c[x]++;

    // Build result by placing all 0s first, then 1s, then 2s
    var ans = new List<int>();
    for (int i = 0; i < c[0]; i++)
      ans.Add(0);
    for (int i = 0; i < c[2]; i++)
      ans.Add(2);
    for (int i = 0; i < c[1]; i++)
      ans.Add(1);

    Console.WriteLine(string.Join(" ", ans));
  }
}


// https://github.com/VaHiX/codeForces/