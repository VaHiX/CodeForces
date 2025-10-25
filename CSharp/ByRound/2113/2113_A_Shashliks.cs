// Problem: CF 2113 A - Shashliks
// https://codeforces.com/contest/2113/problem/A

/*
 * Problem: A. Shashliks
 * Purpose: Determine the maximum number of shashlik portions that can be cooked given initial temperature and cooking requirements.
 * 
 * Algorithms/Techniques:
 * - Greedy approach with two cases considered:
 *   1. Try cooking as many of type 1 as possible, then type 2.
 *   2. Try cooking as many of type 2 as possible, then type 1.
 * - For each case, simulate the process using a while loop and compute how many portions can be cooked in sequence.
 * 
 * Time Complexity: O(log k) per test case due to the nature of simulation where temperature decreases rapidly.
 * Space Complexity: O(1), only using constant extra space.
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split(); // Read input line and split into parts
      long k = long.Parse(input[0]); // Initial temperature
      long a = long.Parse(input[1]); // Required temp for type 1 shashlik
      long b = long.Parse(input[2]); // Required temp for type 2 shashlik
      long x = long.Parse(input[3]); // Temperature drop after type 1 cooking
      long y = long.Parse(input[4]); // Temperature drop after type 2 cooking
      
      // Try both orders: first type then second, and vice versa
      long result1 = Cook(k, a, x, b, y); // Cook first type then second
      long result2 = Cook(k, b, y, a, x); // Cook second type then first
      
      Console.WriteLine(Math.Max(result1, result2)); // Output maximum possible count
    }
  }
  
  // Simulates cooking shashliks in order: first type (a,x) followed by second type (a2,x2)
  static long Cook(long temp, long a1, long x1, long a2, long x2) {
    long count = 0; // Count of portions cooked
    
    // Try to cook as many of first type as possible
    while (temp >= a1) {
      long cnt = (temp - a1) / x1 + 1; // Number of times we can reduce temp by x1 and still have enough for one more portion
      temp -= cnt * x1; // Reduce temperature accordingly
      count += cnt; // Add to total count
    }
    
    // Try to cook as many of second type as possible with remaining temperature
    while (temp >= a2) {
      long cnt = (temp - a2) / x2 + 1; // Same logic applies for second type
      temp -= cnt * x2;
      count += cnt;
    }
    
    return count; // Return total number of portions cooked
  }
}


// https://github.com/VaHiX/codeForces/