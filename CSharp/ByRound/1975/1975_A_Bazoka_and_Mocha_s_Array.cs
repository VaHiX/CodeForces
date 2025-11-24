// Problem: CF 1975 A - Bazoka and Mocha's Array
// https://codeforces.com/contest/1975/problem/A

/*
 * Problem: Bazoka and Mocha's Array
 * 
 * Purpose:
 *   Determine if an array can be sorted in non-decreasing order by performing
 *   a series of prefix-suffix swaps (rotation operations).
 * 
 * Approach:
 *   - The key insight is that if we can sort the array using rotations, the array
 *     must have at most one "drop" point where an element is greater than the next.
 *   - Additionally, a valid rotation must satisfy that the last element is not
 *     greater than the first (to avoid a wrap-around that would break sorting).
 *   - This solution counts the number of decreasing transitions in the array.
 *   - If there is at most one such transition and no wrap-around from last to first,
 *     the array can be sorted via rotation.
 * 
 * Time Complexity: O(n), where n is the length of the array.
 * Space Complexity: O(n), for storing the array elements.
 * 
 * Algorithms/Techniques:
 *   - Linear scan to count inversions (decreasing transitions)
 *   - Rotation validation by checking wrap-around condition
 */

using System;
public class BazokaAndMochaSArray {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] a = new int[n];
      for (byte j = 0; j < n; j++)
        a[j] = int.Parse(parts[j]);
      
      // Count the number of decreasing transitions in the array
      byte countInv = Convert.ToByte(a[n - 1] > a[0] ? 1 : 0);
      for (byte j = 1; j < n && countInv < 2; j++)
        if (a[j - 1] > a[j])
          countInv++;
      
      // If there is at most one decreasing transition, then it's possible to sort
      bool ans = (countInv < 2);
      Console.WriteLine(ans ? "Yes" : "No");
    }
  }
}


// https://github.com/VaHiX/CodeForces/