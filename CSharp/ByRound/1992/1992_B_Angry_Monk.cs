// Problem: CF 1992 B - Angry Monk
// https://codeforces.com/contest/1992/problem/B

/*
 * Problem: Angry Monk
 * Purpose: Find the minimum number of operations to merge all pieces of a potato casserole into one piece of length n.
 * 
 * Algorithms/Techniques:
 * - Greedy approach
 * - Mathematical optimization
 * 
 * Time Complexity: O(k) per test case, where k is the number of pieces.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 * 
 * Key insight:
 * - Each piece of length x >= 2 contributes (x - 1) operations to split it into pieces of size 1 and (x - 1).
 * - To merge all pieces into one, we need to reduce the number of pieces from k to 1, which requires (k - 1) merge operations.
 * - However, we can be more efficient by strategically choosing which pieces to split and merge.
 * - The formula used: 
 *   - sumCut = total splits needed if we split all pieces of length >= 2
 *   - We subtract the maximum piece length's contribution to avoid double-counting
 *   - The answer is sumCut + (n - max_piece_length)
 * 
 * Example walkthrough:
 *   n = 5, a = [3, 2] -> sumCut = (3-1) + (2-1) = 3, aMax = 3
 *   sumCut = 3 - (3-1) = 1, answer = 1 + (5-3) = 3
 */

using System;
public class AngryMonk {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      parts = Console.ReadLine().Split();
      int sumCut = 0;
      int aMax = 0;
      for (int j = 0; j < k; j++) {
        int aj = int.Parse(parts[j]);
        sumCut += aj - 1; // Add operations needed to split this piece
        aMax = Math.Max(aMax, aj); // Track the largest piece
      }
      sumCut -= aMax - 1; // Remove overcounting for the maximum piece
      int ans = sumCut + (n - aMax); // Final calculation
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/