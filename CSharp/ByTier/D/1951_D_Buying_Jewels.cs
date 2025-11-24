// Problem: CF 1951 D - Buying Jewels
// https://codeforces.com/contest/1951/problem/D

/*
 * Problem: Buying Jewels
 * 
 * Algorithm/Technique:
 * - Greedy strategy with optimal stall pricing
 * - The key insight is to use a small number of stalls (at most 2) to ensure Alice buys exactly k jewels.
 * - We set up two stalls with prices (n - k + 1) and 1.
 * - If the condition k > n or k >= n - k + 2 is true, then it's impossible to buy exactly k jewels.
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each test case takes constant time.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

using System;
using System.Collections.Generic;
public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      var input = Console.ReadLine().Split(); // Read n and k
      long n = long.Parse(input[0]); // Number of coins Alice has
      long k = long.Parse(input[1]); // Number of jewels Alice should buy
      
      // Check if it's impossible to buy exactly k jewels
      if (k > n || (k != n && k >= n - k + 2)) {
        Console.WriteLine("NO");
      } else {
        Console.WriteLine("YES");
        Console.WriteLine(2); // Number of stalls needed
        Console.WriteLine($"{n - k + 1} 1"); // Prices for the two stalls
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/