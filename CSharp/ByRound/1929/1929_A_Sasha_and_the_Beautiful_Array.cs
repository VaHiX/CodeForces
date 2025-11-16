// Problem: CF 1929 A - Sasha and the Beautiful Array
// https://codeforces.com/contest/1929/problem/A

/*
 * Problem: Sasha and the Beautiful Array
 * 
 * Algorithm/Techniques: Greedy approach
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 * 
 * The beauty of the array is defined as the sum of (a[i] - a[i-1]) for all i from 2 to n.
 * To maximize this sum, we want to arrange the elements such that the difference 
 * between the maximum and minimum elements contributes as much as possible.
 * 
 * Key insight:
 * - If we sort the array, the maximum beauty is achieved when we place the smallest
 *   element first and the largest element last, making the total sum equal to (max - min).
 * - This is because all intermediate differences will cancel out in a sorted sequence, 
 *   leaving only the difference between the last and first elements.
 * 
 * Therefore, we simply need to find the maximum and minimum values in the array,
 * and compute their difference.
 */

using System;
public class SashaAndTheBeautifulArray {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int aMin = 1000000001; // Initialize to a value larger than max possible input
      int aMax = 0;          // Initialize to 0
      for (byte j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]); // Parse current element
        aMin = Math.Min(aMin, aj);    // Update minimum value
        aMax = Math.Max(aMax, aj);    // Update maximum value
      }
      int ans = aMax - aMin; // Beauty is maximum difference
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/