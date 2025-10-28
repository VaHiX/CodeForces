// Problem: CF 2002 B - Removals Game
// https://codeforces.com/contest/2002/problem/B

/*
 * Problem: Removals Game
 * 
 * Algorithms/Techniques: 
 *   - Compare prefix and suffix of two permutations to determine if Bob can win
 *   - Check if Alice's array matches Bob's array in either forward or reverse order
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing the arrays a and b.
 * 
 * Approach:
 *   - For each test case, we compare Alice's and Bob's permutations.
 *   - We check if they are identical (forward match) or reverse identical (reverse match).
 *   - If either condition is true, Bob wins; otherwise Alice wins.
 */

using System;
public class RemovalsGame {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] a = new int[n];
      for (int j = 0; j < n; j++)
        a[j] = int.Parse(parts[j]);
      parts = Console.ReadLine().Split();
      int[] b = new int[n];
      for (int j = 0; j < n; j++)
        b[j] = int.Parse(parts[j]);
      
      // Flags to check if arrays match in forward and reverse order
      bool equFor = true;
      bool equRev = true;
      int idxLast = n - 1;
      
      // Iterate through the arrays to check forward and reverse matches
      for (int j = 0; j < n && (equFor || equRev); j++) {
        if (a[j] != b[j])
          equFor = false;  // Mark forward match as false if elements differ
        if (a[j] != b[idxLast - j])
          equRev = false;  // Mark reverse match as false if elements differ
      }
      
      // Determine winner based on whether forward or reverse match exists
      string ans = (equFor || equRev ? "Bob" : "Alice");
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/