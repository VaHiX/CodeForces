// Problem: CF 1884 B - Haunted House
// https://codeforces.com/contest/1884/problem/B

using System;
public class HauntedHouse {
  /*
   * Problem: Make a binary number divisible by 2^i using adjacent swaps.
   * 
   * Algorithm:
   * For each i from 1 to n:
   *   - Determine how many swaps are needed to move the rightmost '0' to the i-th position from the end.
   *   - This ensures the number is divisible by 2^i (last i bits must be 0).
   *   - Use a greedy approach to count swaps needed by tracking the rightmost 0 bit.
   * 
   * Time Complexity: O(n^2) in worst case due to repeated LastIndexOf calls, but with optimization it's effectively O(n)
   * Space Complexity: O(n) for the output array
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      long[] ans = new long[n];
      int idxLast = n - 1;
      int idxLast0 = s.LastIndexOf('0'); // Find the last '0' in the string
      long countSwap = 0;
      for (int j = 0; j < n; j++) {
        if (idxLast0 < 0)
          ans[j] = -1; // No '0' found, impossible to make divisible by 2^i
        else {
          int d = idxLast - idxLast0; // Distance to move the last '0' to correct position
          countSwap += d; // Accumulate the number of swaps
          ans[j] = countSwap; // Store the total swaps for current i
          idxLast0 = idxLast0 > 0 ? s.LastIndexOf('0', idxLast0 - 1) : -1; // Find the next '0' from the left
          idxLast--; // Move target position one step to the left
        }
      }
      Console.WriteLine(string.Join(" ", ans));
    }
  }
}

// https://github.com/VaHiX/CodeForces/