// Problem: CF 1862 C - Flower City Fence
// https://codeforces.com/contest/1862/problem/C

/*
 * Flower City Fence Problem
 * 
 * Purpose: Determine if a fence made of planks with non-increasing heights is symmetric when laid horizontally.
 * 
 * Algorithm:
 * - The problem involves checking if the fence configuration is self-symmetric when transformed.
 * - Key idea: Compare the original height array with its horizontal counterpart.
 * - The horizontal fence is built by placing planks side by side, which changes the shape in a specific way.
 * - We simulate this transformation using a two-pointer approach.
 * 
 * Time Complexity: O(n) - Each element is visited at most once in the main loop.
 * Space Complexity: O(n) - Extra space for the array 'a' which stores the plank heights.
 */

using System;

public class FlowerCityFence {
  public static void Main() {
    short t = short.Parse(Console.ReadLine()); // Read number of test cases
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine()); // Read number of planks
      string[] parts = Console.ReadLine().Split(); // Read plank heights
      int[] a = new int[n + 1]; // Array to store heights (1-indexed)
      for (int j = 1; j <= n; j++)
        a[j] = int.Parse(parts[j - 1]); // Fill the heights array
      
      int bound = n / 2 + n % 2; // Calculate the middle point for symmetry check
      bool ans = a[1] == n; // Check if first plank height matches fence length (necessary condition)
      int xl = 2; // Left pointer starting from second plank
      int xr = n; // Right pointer starting from last plank
      int y = n; // Current height level being processed
      
      // Process the fence to check symmetry
      while (ans && xl <= n && y > bound) {
        // Skip all planks with same height as current y
        while (xl <= n && a[xl] == y)
          xl++;
        
        // Update y to the height of next plank or 1 if none left
        y = xl <= n ? a[xl] : 1;
        
        // Check planks from right side down to current y level
        while (ans && xr > y) {
          ans = ans && a[xr] == xl - 1; // Compare height with expected value based on position
          xr--; // Move right pointer left
        }
        
        xl++; // Move left pointer right
      }
      
      Console.WriteLine(ans ? "YES" : "NO"); // Output result
    }
  }
}


// https://github.com/VaHiX/CodeForces/