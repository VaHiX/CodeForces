// Problem: CF 1957 A - Stickogon
// https://codeforces.com/contest/1957/problem/A

/*
 * Problem: Stickogon
 * 
 * Purpose: 
 * This program determines the maximum number of regular polygons (equal-sided) that can be constructed 
 * using given sticks. Each side of a polygon must be formed by exactly one stick, and no stick can be used in more than one polygon.
 * 
 * Approach:
 * - For each unique stick length, count how many sticks of that length exist.
 * - A regular polygon with k sides requires k sticks of equal length.
 * - To maximize the number of polygons, we want to form as many polygons as possible using the smallest number of sticks.
 * - Since we're allowed to make multiple polygons, we focus on forming those with the smallest number of sides.
 * - Therefore, we process stick lengths in ascending order, and for each length, we see how many polygons of side length equal to this can be made.
 * - However, since we're not constrained about the number of sides, the optimal strategy is to try to form as many polygons as possible.
 * 
 * The algorithm used:
 * 1. Count frequency of each stick length.
 * 2. For each stick length, determine how many polygons (of some side length) can be made from that many sticks.
 * 3. Since the question allows any regular polygon, and we want to maximize the count of polygons, 
 *    we can form one polygon for every 3 sticks (minimum for a triangle), or more based on how many sides we decide to use.
 * 4. However, the problem is simpler: given any number of sticks, we can always make one polygon, e.g., a triangle.
 *    If we think in terms of "minimum number of sticks to form a polygon", the problem simplifies to:
 *    - Each polygon requires at least 3 sticks (minimum 3-sided polygon).
 *    - So for each group of 3 sticks, we can form one polygon.
 *    - Since we don't know the side lengths, and we are allowed to make any polygon (as long as we use the sticks optimally),
 *      we treat every group of 3 sticks as one polygon.
 * 
 * Time Complexity: O(n log n) due to use of SortedDictionary, which uses a red-black tree internally for sorting keys.
 * Space Complexity: O(n) for storing the frequency map.
 */

using System;
using System.Collections.Generic;

public class Stickogon {
  public static void Main() {
    byte t = byte.Parse(Console.ReadLine()); // Read number of test cases
    for (byte i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine()); // Read number of sticks
      string[] parts = Console.ReadLine().Split(); // Read stick lengths
      SortedDictionary<byte, byte> counters = // Keep track of stick frequencies
          new SortedDictionary<byte, byte>();
      for (byte j = 0; j < n; j++) {
        byte aj = byte.Parse(parts[j]); // Parse each stick length
        if (counters.ContainsKey(aj)) // If length already exists
          counters[aj]++; // Increment count
        else
          counters.Add(aj, 1); // Add new key with count 1
      }
      byte ans = 0; // Initialize result
      foreach (KeyValuePair<byte, byte> kvp in counters) // For each stick length and its count
        ans += Convert.ToByte(kvp.Value / 3); // Count how many groups of 3 can be formed (i.e., number of triangles that can be made from this length)
      Console.WriteLine(ans); // Output total number of polygons
    }
  }
}


// https://github.com/VaHiX/CodeForces/