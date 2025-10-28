// Problem: CF 2025 C - New Game
// https://codeforces.com/contest/2025/problem/C

using System;
using System.Collections.Generic;
using System.Linq;
class Solution {
  /// <summary>
  /// Finds the maximum number of cards Monocarp can take in the game, given constraints on distinct numbers.
  /// 
  /// Algorithm:
  /// - Use a sliding window approach over unique card values.
  /// - For each valid window of at most k distinct numbers, check if the values are consecutive.
  /// - If not, adjust the window to maintain consecutive values.
  /// 
  /// Time Complexity: O(n * log(n)) due to sorting unique elements and linear traversal.
  /// Space Complexity: O(n) for storing counts and unique elements.
  /// </summary>
  public static long MaxCardsTaken(int n, int k, List<int> a) {
    var c = new Dictionary<int, long>(); // Count of each unique card value
    var u = new List<int>(); // List of unique card values
    foreach (int x in a) {
      if (!c.ContainsKey(x)) {
        c[x] = 0;
        u.Add(x);
      }
      c[x]++;
    }
    u.Sort(); // Sort unique values to process in order
    
    long m = 0; // Maximum number of cards taken
    int l = 0;  // Left pointer of sliding window
    long t = 0; // Total cards in current window
    
    for (int r = 0; r < u.Count; ++r) {
      t += c[u[r]]; // Add current element to window
      
      // Shrink window from left if more than k distinct numbers
      while (r - l + 1 > k) {
        t -= c[u[l]];
        l++;
      }
      
      // If current value is not consecutive to previous value, adjust window
      if (r > 0 && u[r] - u[r - 1] > 1) {
        int currentR = u[r];
        while (l <= r && currentR - u[l] > 1) {
          t -= c[u[l]];
          l++;
        }
      }
      
      m = Math.Max(m, t); // Update maximum
    }
    
    return m;
  }
  
  public static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var inputs = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
      int n = inputs[0];
      int k = inputs[1];
      var a = Console.ReadLine().Split(' ').Select(int.Parse).ToList();
      Console.WriteLine(MaxCardsTaken(n, k, a));
    }
  }
}


// https://github.com/VaHiX/CodeForces/