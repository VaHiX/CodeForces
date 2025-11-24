// Problem: CF 2037 C - Superultra's Favorite Permutation
// https://codeforces.com/contest/2037/problem/C

using System;
using System.Collections.Generic;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    Dictionary<int, List<int>> results = new Dictionary<int, List<int>>();
    for (int n = 0; n < t; n++) {
      int k = int.Parse(Console.ReadLine());
      List<int> values = new List<int>() { 4, 5 };
      if (k > 4) {
        // Insert even numbers (excluding 4) at the beginning
        for (int i = 1; i <= k; i++) {
          if (i % 2 == 0 && i != 4) {
            values.Insert(0, i);
          } else if (i % 2 != 0 && i != 5) {
            // Insert odd numbers (excluding 5) at the end
            values.Insert(values.Count, i);
          }
        }
        results[n] = new List<int>(values);
      } else {
        // For k <= 4, it's impossible to construct a valid permutation
        results[n] = new List<int>() { -1 };
      }
    }
    foreach (KeyValuePair<int, List<int>> pair in results) {
      Console.WriteLine($"{string.Join(" ", pair.Value)}");
    }
  }
}
/*
Algorithm/Technique: Greedy Construction
Time Complexity: O(n^2) in worst case due to Insert operations on List
Space Complexity: O(n) for storing the permutation and results

This solution attempts to construct a permutation such that the sum of every two adjacent elements is composite.
It uses a greedy approach:
1. For small n (n <= 4), it's impossible to avoid having two adjacent elements sum to a prime, so it returns -1.
2. For larger n, it starts with [4, 5] and builds the rest of the array by:
   - Inserting even numbers (except 4) at the beginning
   - Inserting odd numbers (except 5) at the end
This ensures that adjacent sums are less likely to be prime, as even-even and odd-odd sums tend to be composite.
*/


// https://github.com/VaHiX/CodeForces/