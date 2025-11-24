// Problem: CF 1955 A - Yogurt Sale
// https://codeforces.com/contest/1955/problem/A

/*
 * Problem: Yogurt Sale
 * 
 * Purpose: 
 *   Given the cost of a single yogurt 'a' and the cost of buying two yogurts together 'b',
 *   determine the minimum cost to buy exactly 'n' yogurts.
 * 
 * Algorithm:
 *   - If 2*a <= b, it's always better to buy individual yogurts (since buying two at promotion is not saving).
 *   - Otherwise, use as many promotion deals as possible and buy remaining yogurts individually.
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each test case is processed in constant time.
 * Space Complexity: O(1), only a constant amount of extra space is used.
 * 
 * Techniques:
 *   - Greedy approach
 *   - Mathematical optimization
 */

using System;
public class YogurtSale {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split(); // Parse input line
      byte n = byte.Parse(parts[0]); // Number of yogurts to buy
      byte a = byte.Parse(parts[1]); // Price of one yogurt
      byte b = byte.Parse(parts[2]); // Price of two yogurts together
      // Calculate minimum cost:
      // If 2*a <= b, it's cheaper to buy individual yogurts
      // Otherwise, use as many promotion deals as possible and buy leftover individually
      short ans = Convert.ToInt16(2 * a <= b ? n * a : (n / 2) * b + (n % 2) * a);
      Console.WriteLine(ans); // Output result for current test case
    }
  }
}


// https://github.com/VaHiX/CodeForces/