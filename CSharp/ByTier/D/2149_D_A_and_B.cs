// Problem: CF 2149 D - A and B
// https://codeforces.com/contest/2149/problem/D

/*
 * Problem: D. A and B
 * 
 * Purpose: Given a string of 'a' and 'b', find the minimum number of adjacent swaps
 *          to make all characters of one type form a single continuous block.
 *
 * Algorithms/Techniques:
 *   - For each character type ('a' or 'b'), collect positions of that character.
 *   - Calculate minimal cost to move them into a contiguous block around their median.
 *   - The cost is the sum of absolute differences between each position and its target position,
 *     which minimizes when aligned with the median.
 *   
 * Time Complexity: O(n) per test case, as we traverse the string once for each character type.
 * Space Complexity: O(n), for storing positions of characters.
 */

using System;
using System.Linq;
using System.Collections.Generic;

class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      string s = Console.ReadLine();
      // Try both 'a' and 'b' as the target block type, return minimum
      Console.WriteLine(Math.Min(CalcCost(s, 'a'), CalcCost(s, 'b')));
    }
  }

  // Calculates the minimal cost to form a contiguous block of character `ch`
  static long CalcCost(string s, char ch) {
    List<int> pos = new List<int>();
    // Collect all positions of character `ch`
    for (int i = 0; i < s.Length; i++)
      if (s[i] == ch)
        pos.Add(i);
    
    // If no such character exists, impossible to form a block
    if (pos.Count == 0)
      return long.MaxValue;
    
    // If all characters are of type `ch`, no swaps needed
    if (pos.Count == s.Length)
      return 0;
    
    int k = pos.Count; // Number of occurrences of `ch`
    int mid = k / 2;   // Median index (for optimal block placement)
    long cost = 0;
    
    // For each occurrence of `ch`, calculate its movement cost to the target positions
    for (int i = 0; i < k; i++) {
      // Target position for `i`-th element in sorted list: (mid - mid + i) = i
      // But we want it centered around pos[mid], so use adjusted logic:
      // The optimal block starts at (pos[mid] - mid) and ends at (pos[mid] + k - mid - 1)
      // So position `i` should ideally be at index (pos[mid] - mid + i)
      cost += Math.Abs(pos[i] - (pos[mid] - mid + i));
    }
    
    return cost;
  }
}


// https://github.com/VaHiX/CodeForces/