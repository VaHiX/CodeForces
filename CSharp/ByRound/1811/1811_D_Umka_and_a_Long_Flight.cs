// Problem: CF 1811 D - Umka and a Long Flight
// https://codeforces.com/contest/1811/problem/D

/*
Purpose: Determine if a Fibonacci rectangle of order n can be cut into n+1 squares such that:
- One square has side length 1 and contains the painted cell
- At most one pair of squares have equal sides
- All square side lengths are Fibonacci numbers

Algorithm: Recursive backtracking with memoization
Time Complexity: O(n) per test case, since we traverse from n down to 1
Space Complexity: O(n) for storing Fibonacci numbers and recursion stack

Techniques:
- Precompute Fibonacci numbers up to F_44
- Recursive solution with pruning based on constraints
- Backtracking approach to simulate cutting the rectangle
*/

using System;
using System.Collections.Generic;
public class Solution {
  static List<long> ewgfwoigiouwe114hjb = new List<long>(); // Stores Fibonacci numbers
  
  // Recursive function to check if valid tiling exists
  public static bool Solve(long ewgfwoigiou35we114hjb, // x coordinate of painted cell
                           long ewgfwoigiou35w3fe114hjb, // y coordinate of painted cell  
                           long ewgfwoigiouwe) {         // current Fibonacci order n
    if (ewgfwoigiouwe == 1)
      return true; // Base case: if n=1, rectangle is 1x1, so it's always possible
    
    // Pruning condition: if the painted cell is not in the region where a 1x1 square could be placed
    // (this checks for valid positioning of 1x1 square in the last step)
    if (Math.Min(ewgfwoigiou35w3fe114hjb,
                 ewgfwoigiouwe114hjb[(int)ewgfwoigiouwe + 1] -
                     ewgfwoigiou35w3fe114hjb + 1) >
        ewgfwoigiouwe114hjb[(int)ewgfwoigiouwe + 1] -
            ewgfwoigiouwe114hjb[(int)ewgfwoigiouwe]) {
      return false;
    }
    
    // Adjust coordinates to be based on the smallest possible square
    ewgfwoigiou35w3fe114hjb = Math.Min(
        ewgfwoigiou35w3fe114hjb, ewgfwoigiouwe114hjb[(int)ewgfwoigiouwe + 1] -
                                     ewgfwoigiou35w3fe114hjb + 1);
    
    // Recursively solve for n-1
    return Solve(ewgfwoigiou35w3fe114hjb, ewgfwoigiou35we114hjb,
                 ewgfwoigiouwe - 1);
  }
  
  public static void Main() {
    long ewgfwoigiouwe114, ewgfwoigiouwe, ewgfwoigiouwe1, ewgfwoigiouwe11;
    ewgfwoigiouwe114 = Convert.ToInt64(Console.ReadLine());
    
    // Precompute Fibonacci numbers: F_0 = 1, F_1 = 1, F_n = F_{n-1} + F_{n-2}
    ewgfwoigiouwe114hjb.Add(1);
    ewgfwoigiouwe114hjb.Add(1);
    for (int i = 0; i < 46; i++) {
      ewgfwoigiouwe114hjb.Add(ewgfwoigiouwe114hjb[i] +
                              ewgfwoigiouwe114hjb[i + 1]);
    }
    
    // Process each test case
    while (ewgfwoigiouwe114-- > 0) {
      string[] input = Console.ReadLine().Split();
      ewgfwoigiouwe = Convert.ToInt64(input[0]);       // n
      ewgfwoigiouwe1 = Convert.ToInt64(input[1]);      // x
      ewgfwoigiouwe11 = Convert.ToInt64(input[2]);     // y
      
      // Call Solve function with coordinates and n
      if (Solve(ewgfwoigiouwe1, ewgfwoigiouwe11, ewgfwoigiouwe)) {
        Console.WriteLine("YES");
      } else {
        Console.WriteLine("NO");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/