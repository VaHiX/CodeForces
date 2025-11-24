// Problem: CF 2148 C - Pacer
// https://codeforces.com/contest/2148/problem/C

/*
 * Problem: C. Pacer
 * 
 * Purpose: Maximize points Farmer John can gain while meeting audio requirements.
 * 
 * Algorithm: Greedily decide whether to move or stay at each step to satisfy constraints.
 *            Use parity (even/odd) logic to determine minimum required time between moves.
 *            
 * Time Complexity: O(n) per test case, where n is the number of requirements.
 * Space Complexity: O(n) for storing input arrays.
 * 
 * Techniques:
 *   - Greedy algorithm
 *   - Parity-based movement constraints
 *   - Linear scan with state tracking (last time, last parity)
 */

using System;
using System.Collections.Generic;
using System.Linq;

public class Solution {
  public static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      var nm = Console.ReadLine().Split().Select(long.Parse).ToArray(); // Read n and m
      int n = (int)nm[0];
      long m = nm[1];
      long[] a = new long[n]; // Array to store requirement times
      int[] b = new int[n];   // Array to store required sides at each time
      for (int i = 0; i < n; i++) {
        var parts = Console.ReadLine().Split().Select(long.Parse).ToArray();
        a[i] = parts[0];
        b[i] = (int)parts[1];
      }
      long total = 0;         // Total points accumulated
      long lastTime = 0;      // Time of the previous requirement
      int lastParity = 0;     // Parity (0 or 1) of the side we were on previously
      bool possible = true;   // Flag to check if requirements can be satisfied
      
      for (int i = 0; i < n; i++) {
        long delta = a[i] - lastTime;            // Time elapsed since last requirement
        int requiredParity = lastParity ^ b[i];  // XOR to determine the parity needed to move from last side to current required side
        
        if (delta < requiredParity) {            // If not enough time to make the necessary move
          possible = false;
          break;
        }
        
        // Greedily decide how many points to take:
        // - If time allows, we can take all steps in the delta
        // - Else, we must reduce by 1 step to maintain parity constraint
        if (delta % 2 == requiredParity)
          total += delta;
        else
          total += (delta - 1);
        
        lastTime = a[i];    // Update the time of last requirement reached
        lastParity = b[i];  // Update the side we're currently at (side is now b[i])
      }
      
      if (!possible) {
        Console.WriteLine("-1");
        continue;
      }
      
      // Add remaining time after last requirement to the total points
      total += (m - lastTime);
      Console.WriteLine(total);
    }
  }
}


// https://github.com/VaHiX/codeForces/