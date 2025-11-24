// Problem: CF 2132 E - Arithmetics Competition
// https://codeforces.com/contest/2132/problem/E

/*
E. Arithmetics Competition
Algorithm: Using prefix sums and ternary search to find optimal number of cards to select from each player's set.
Time Complexity: O(n log n + m log m + q * log(min(n, m)))
Space Complexity: O(n + m)

Problem Description:
In an arithmetic competition, Vadim (with n cards) and Kostya (with m cards) need to maximize the sum of selected cards for each round.
Each round has constraints on how many cards each can select.
We use sorting, prefix sums, and ternary search to optimize performance.

*/
using System;
using System.Linq;

public class Program {
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    for (int _ = 0; _ < t; _++) {
      Solve();
    }
  }
  
  public static void Solve() {
    string[] line = Console.ReadLine().Split();
    int n = int.Parse(line[0]);
    int m = int.Parse(line[1]);
    int q = int.Parse(line[2]);
    
    // Read Vadim's cards and sort in descending order for greedy selection
    int[] a = Console.ReadLine().Split().Select(int.Parse).ToArray();
    Array.Sort(a);
    Array.Reverse(a); // Sort in descending order
    
    // Precompute prefix sum for Vadim's cards
    long[] pa = new long[n + 1];
    for (int i = 0; i < n; i++) {
      pa[i + 1] = pa[i] + a[i];
    }
    
    // Read Kostya's cards and sort in descending order
    int[] b = Console.ReadLine().Split().Select(int.Parse).ToArray();
    Array.Sort(b);
    Array.Reverse(b); // Sort in descending order
    
    // Precompute prefix sum for Kostya's cards
    long[] pb = new long[m + 1];
    for (int i = 0; i < m; i++) {
      pb[i + 1] = pb[i] + b[i];
    }
    
    // Process each query
    for (int i = 0; i < q; i++) {
      string[] query = Console.ReadLine().Split();
      int x = int.Parse(query[0]); // Max cards Vadim can take
      int y = int.Parse(query[1]); // Max cards Kostya can take  
      int z = int.Parse(query[2]); // Total cards to pick together
      
      // Determine valid range of cards Vadim can pick from [l, r]
      int l = Math.Max(z - y, 0); // Min Vadim picks (if needed)
      int r = Math.Min(x, z);     // Max Vadim picks (limited by x)

      if (l > r) {
        l = r;
      }
      
      long best = 0;
      
      // Use ternary search to find the optimal number of cards for Vadim
      while (r - l > 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        
        long s1 = pa[m1] + pb[z - m1]; // Sum if Vadim picks m1 cards
        long s2 = pa[m2] + pb[z - m2]; // Sum if Vadim picks m2 cards
        
        // Compare sums and move search boundary accordingly
        if (s1 < s2) {
          l = m1;
        } else if (s1 > s2) {
          r = m2;
        } else {
          l = m1;
          r = m2;
        }
      }
      
      // Final check of remaining candidates
      best = 0;
      for (int j = l; j <= r; j++) {
        if (j <= n && (z - j) <= m) { // Valid bounds
          long current = pa[j] + pb[z - j];
          if (current > best) {
            best = current;
          }
        }
      }
      
      Console.WriteLine(best);
    }
  }
}


// https://github.com/VaHiX/CodeForces/