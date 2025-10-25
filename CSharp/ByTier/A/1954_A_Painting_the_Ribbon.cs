// Problem: CF 1954 A - Painting the Ribbon
// https://codeforces.com/contest/1954/problem/A

using System;

class Program {
  // Purpose: Determines if Alice can paint the ribbon such that Bob cannot make all parts the same color.
  // Algorithm: The key insight is that if Alice distributes the parts as evenly as possible among m colors,
  //            then the minimum number of parts that must remain unpainted (to prevent Bob from making all same color)
  //            is calculated. If this number exceeds k, then Alice wins.
  // Time Complexity: O(1) - constant time operations
  // Space Complexity: O(1) - only using a fixed amount of variables

  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      string[] input = Console.ReadLine().Split();
      int n = int.Parse(input[0]);  // number of parts
      int m = int.Parse(input[1]);  // number of colors
      int k = int.Parse(input[2]);  // maximum parts Bob can repaint
      
      // Calculate minimum number of parts that will remain unpainted
      // This is the number of parts that cannot be made uniform by Bob's repaints
      // The formula uses ceiling division to distribute n parts among m colors
      // and subtracts this from total to find the minimum number of parts needing to stay same color
      if (n - (n / m + (Convert.ToInt32(n % m != 0))) <= k) {
        Console.WriteLine("NO");
      } else
        Console.WriteLine("YES");
    }
  }
}

// https://github.com/VaHiX/CodeForces/