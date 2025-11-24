// Problem: CF 2065 E - Skibidus and Rizz
// https://codeforces.com/contest/2065/problem/E

/*
 * Problem: E. Skibidus and Rizz
 * Purpose: Construct a binary string of length n + m with exactly n 0's and m 1's
 *          such that the maximum balance-value among all substrings is exactly k.
 *
 * Algorithms/Techniques:
 *   - Greedy construction approach based on balancing 0s and 1s.
 *   - Ensure that the maximum imbalance (balance-value) of any substring is exactly k.
 *   - Uses a string builder for efficient concatenation.
 *
 * Time Complexity: O(n + m) per test case
 * Space Complexity: O(n + m) for the constructed string
 */

using System.Text;
using static System.Math;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var n = int.Parse(line[0]);
      var m = int.Parse(line[1]);
      var k = int.Parse(line[2]);
      getAns(n, m, k);
    }
  }

  // Reverses the binary string by flipping '0' to '1' and '1' to '0'
  static void rev(string s) {
    var s2 = s.ToCharArray(); // Convert string to char array for in-place modification
    var n = s.Length;
    for (int i = 0; i < n; i++)
      s2[i] = s2[i] == '1' ? '0' : '1'; // Flip each bit
    Console.WriteLine(new string(s2)); // Output reversed string
  }

  static void getAns(int n, int m, int k) {
    if (Abs(n - m) > k) { // If difference in count exceeds k, impossible to achieve balance k
      Console.WriteLine(-1);
      return;
    }
    if (Max(n, m) < k) { // If the maximum count of either 0 or 1 is less than k, not possible
      Console.WriteLine(-1);
      return;
    }

    var f = false; // Flag to check if we swapped n and m
    if (m > n) {
      var w = n;   // Swap n and m so that n >= m
      n = m;
      m = w;
      f = true;
    }

    var sb = new StringBuilder(); // Use StringBuilder for efficient string building
    sb.Append(new string('0', k)); // Start with k zeros to ensure initial balance
    n -= k; // Reduce n by k since we've already added k 0s

    // Alternate between 1 and 0 to maintain balance around k
    while (n > 0) {
      sb.Append("10"); // Append "10" pattern to alternate bits
      n--;             // Decrease n and m accordingly
      m--;
    }

    // Add remaining 1s if any
    sb.Append(new string('1', m));

    var s = sb.ToString(); // Convert StringBuilder to string

    if (f) // If we swapped n and m earlier, reverse the result to maintain correct counts
      rev(s);
    else
      Console.WriteLine(s); // Otherwise output the constructed string
  }
}


// https://github.com/VaHiX/codeForces/