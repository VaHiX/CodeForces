// Problem: CF 1876 A - Helmets in Night Light
// https://codeforces.com/contest/1876/problem/A

using System;
public class HelmetsInNightLight {
  /*
   * Problem: Minimize the cost to notify all residents in a village using direct sharing and helmet-based propagation.
   * 
   * Algorithm:
   * - Greedily select residents with the lowest cost per share (b[i] / a[i]) to propagate the message.
   * - Sort residents by their sharing cost (b array) in ascending order, while keeping a array synchronized.
   * - Start by directly informing one resident (cost p).
   * - Then, iteratively use the cheapest available propagators (based on b[i]) to spread the word.
   * - Continue until all residents are informed.
   * 
   * Time Complexity: O(n log n) due to sorting
   * Space Complexity: O(n) for storing arrays a and b
   */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int p = int.Parse(parts[1]);
      parts = Console.ReadLine().Split();
      int[] a = new int[n];
      for (int j = 0; j < n; j++)
        a[j] = int.Parse(parts[j]);
      parts = Console.ReadLine().Split();
      int[] b = new int[n];
      for (int j = 0; j < n; j++)
        b[j] = int.Parse(parts[j]);
      // Sort b array in ascending order and keep a synchronized
      Array.Sort(b, a);
      int m = 1;           // Number of residents already informed
      int k = 0;           // Index of current propagator
      long ans = p;        // Start with cost of informing one resident directly
      while (m < n) {
        if (b[k] >= p) {
          // If the cheapest propagator is more expensive than direct sharing, just pay p for remaining residents
          ans += (n - m) * (long)p;
          m = n;
        } else {
          // Use the current propagator to spread to min(a[k], remaining residents) others
          ans += Math.Min(a[k], n - m) * (long)b[k];
          m = Math.Min(m + a[k], n);
          k++;
        }
      }
      Console.WriteLine(ans);
    }
  }
}

// https://github.com/VaHiX/CodeForces/