// Problem: CF 1896 A - Jagged Swaps
// https://codeforces.com/contest/1896/problem/A

using System;
public class JaggedSwaps {
  /*
   * Problem: Determine if a permutation can be sorted using a specific swap operation.
   * 
   * Algorithm:
   * - The allowed operation is swapping adjacent elements a[i] and a[i+1] when a[i-1] < a[i] and a[i] > a[i+1].
   * - This operation resembles the behavior of a bubble sort step in reverse, but not exactly.
   * - Key insight: If the first element is 1, then it might be possible to sort the array.
   * - The problem reduces to checking whether the first element is 1.
   * 
   * Time Complexity: O(1) per test case, since we only read the first element.
   * Space Complexity: O(1), as we use a constant amount of extra space.
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read size of permutation
      string[] parts = Console.ReadLine().Split(); // Read the permutation elements
      byte a0 = byte.Parse(parts[0]); // Get the first element of the permutation
      bool ans = (a0 == 1); // If first element is 1, it's possible to sort
      Console.WriteLine(ans ? "YES" : "NO"); // Output result
    }
  }
}

// https://github.com/VaHiX/CodeForces/