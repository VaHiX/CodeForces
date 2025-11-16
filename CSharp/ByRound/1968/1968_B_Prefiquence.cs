// Problem: CF 1968 B - Prefiquence
// https://codeforces.com/contest/1968/problem/B

/*
 * Problem: Prefiquence
 * 
 * Purpose: Given two binary strings a and b, find the maximum length k such that
 *          the prefix of a of length k is a subsequence of b.
 * 
 * Algorithm: Two-pointer technique
 *   - Use two pointers, one for each string (ia for a, ib for b)
 *   - For each character in a, try to find a matching character in b
 *   - If found, increment both pointers and the match count (k)
 *   - If not found, continue searching in b until end
 *   - Continue until either string is exhausted
 * 
 * Time Complexity: O(n + m) where n is length of a, m is length of b
 * Space Complexity: O(1) - only using a few integer variables
 */

using System;
public class Prefiquence {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int m = int.Parse(parts[1]);
      string a = Console.ReadLine();
      string b = Console.ReadLine();
      int ia = 0;  // pointer for string a
      int ib = 0;  // pointer for string b
      int k = 0;   // count of matched characters in prefix of a
      while (ia < n && ib < m) {
        // Move ib until we find the character matching a[ia] or reach end of b
        while (ib < m && b[ib] != a[ia])
          ib++;
        if (ib < m)
          k++;  // we found a match
        ia++;     // move to next character in a
        ib++;     // move to next character in b
      }
      Console.WriteLine(k);
    }
  }
}


// https://github.com/VaHiX/CodeForces/