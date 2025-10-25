// Problem: CF 1864 B - Swap and Reverse
// https://codeforces.com/contest/1864/problem/B

/*
 * Problem: Swap and Reverse
 * 
 * Algorithm/Technique:
 * - The key insight is that we can swap characters at positions i and i+2, 
 *   and reverse any substring of length k. 
 * - Since we can perform any number of operations, we can rearrange characters 
 *   within even and odd positions independently.
 * - Even positions (0-indexed) can be sorted among themselves, and same for odd positions.
 * - The final lexicographically smallest arrangement depends on whether k is even or odd:
 *   - If k is even, we can arrange all characters in any order -> sort entire string.
 *   - If k is odd, we can only rearrange even and odd positions independently -> merge sorted even and odd arrays.
 * 
 * Time Complexity: O(n log n) due to sorting operations on even and odd character arrays.
 * Space Complexity: O(n) for storing the even and odd character arrays and merged result.
 */
using System;
public class SwapAndReverse {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      string s = Console.ReadLine();
      int countEven = (n + 1) / 2; // Count of characters at even indices (0-indexed)
      int countOdd = n - countEven; // Count of characters at odd indices (0-indexed)
      char[] evenPos = new char[countEven]; // Stores characters at even positions
      char[] oddPos = new char[countOdd]; // Stores characters at odd positions
      for (int j = 0; j < s.Length; j++) {
        if (j % 2 == 0)
          evenPos[j / 2] = s[j]; // Fill even position characters
        else
          oddPos[j / 2] = s[j]; // Fill odd position characters
      }
      Array.Sort(evenPos); // Sort even position characters
      Array.Sort(oddPos); // Sort odd position characters
      char[] arrS = s.ToCharArray();
      Array.Sort(arrS); // Sort entire string to get minimum possible lexicographical arrangement
      char[] letters = Merge(n, evenPos, oddPos); // Merge back sorted even and odd arrays
      // If k is even, we can freely arrange characters -> sort the whole string
      // If k is odd, we have to keep even and odd positions separate -> use merged sorted version
      string ans = (k % 2 == 0 ? new string(arrS) : new string(letters));
      Console.WriteLine(ans);
    }
  }
  private static char[] Merge(int n, char[] e, char[] o) {
    char[] letters = new char[n];
    for (int j = 0; j < n; j++)
      letters[j] = (j % 2 == 0 ? e[j / 2] : o[j / 2]); // Reconstruct based on index parity
    return letters;
  }
}


// https://github.com/VaHiX/CodeForces/